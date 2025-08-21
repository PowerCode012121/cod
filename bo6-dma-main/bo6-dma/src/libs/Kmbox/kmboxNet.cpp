#include "kmboxNet.h"
#include "HidTable.h"
#include <time.h>
#define monitor_ok    2
#define monitor_exit  0
SOCKET sockClientfd = 0;				// キーボード・マウス ネットワーク通信ハンドル
SOCKET sockMonitorfd = 0;				// 監視用ネットワーク通信ハンドル
client_tx tx;							// 送信する内容
client_tx rx;							// 受信する内容
SOCKADDR_IN addrSrv;
soft_mouse_t    softmouse;				// ソフトウェアマウスデータ
soft_keyboard_t softkeyboard;			// ソフトウェアキーボードデータ
static int monitor_run = 0;				// 物理キーボード・マウス監視が実行中か
static int mask_keyboard_mouse_flag = 0;// キーボード・マウスブロック状態
static short monitor_port = 0;


#pragma pack(1)
typedef struct {
	unsigned char report_id;
	unsigned char buttons;		// 利用可能な8ボタン
	short x;					// -32767 から 32767
	short y;					// -32767 から 32767
	short wheel;				// -32767 から 32767
}standard_mouse_report_t;

typedef struct {
	unsigned char report_id;
	unsigned char buttons;      // 8ボタン制御キー
	unsigned char data[10];     // 通常キー
}standard_keyboard_report_t;
#pragma pack()

standard_mouse_report_t		hw_mouse;   // ハードウェアマウス情報
standard_keyboard_report_t	hw_keyboard;// ハードウェアキーボード情報

// AからBの間のランダムな数を生成
int myrand(int a, int b)
{
	int min = a < b ? a : b;
	int max = a > b ? a : b;
	return ((rand() % (max - min)) + min);
}

unsigned int StrToHex(char* pbSrc, int nLen)
{
	char h1, h2;
	unsigned char s1, s2;
	int i;
	unsigned int pbDest[16] = { 0 };
	for (i = 0; i < nLen; i++) {
		h1 = pbSrc[2 * i];
		h2 = pbSrc[2 * i + 1];
		s1 = toupper(h1) - 0x30;
		if (s1 > 9)
			s1 -= 7;
		s2 = toupper(h2) - 0x30;
		if (s2 > 9)
			s2 -= 7;
		pbDest[i] = s1 * 16 + s2;
	}
	return pbDest[0] << 24 | pbDest[1] << 16 | pbDest[2] << 8 | pbDest[3];
}

int NetRxReturnHandle(client_tx* rx, client_tx* tx)		 // 受信内容
{
	if (rx->head.cmd != tx->head.cmd)
		return  err_net_cmd; // コマンドコードエラー
	if (rx->head.indexpts != tx->head.indexpts)
		return  err_net_pts; // タイムスタンプエラー
	return 0;				 // エラーがない場合は0を返す
}


/*
kmboxNetボックスへの接続、入力パラメータはそれぞれボックスの
ip  ：ボックスのIPアドレス（ディスプレイに表示されます、例：192.168.2.88）
port: 通信ポート番号（ディスプレイに表示されます、例：6234）
mac : ボックスのMACアドレス（ディスプレイに表示されます、例：12345）
戻り値：0は正常、0以外はエラーコードを参照してください
*/
int kmNet_init(char* ip, char* port, char* mac)
{
	WORD wVersionRequested; WSADATA wsaData;	int err;
	wVersionRequested = MAKEWORD(1, 1);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) 		return err_creat_socket;
	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1) {
		WSACleanup(); sockClientfd = -1;
		return err_net_version;
	}
	srand((unsigned)time(NULL));
	sockClientfd = socket(AF_INET, SOCK_DGRAM, 0);
	addrSrv.sin_addr.S_un.S_addr = inet_addr(ip);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(atoi(port)); // ポート UUID[1]>>16 上位16ビット
	tx.head.mac = StrToHex(mac, 4);		  // ボックスのMAC、固定 UUID[1]
	tx.head.rand = rand();				  // ランダム値。後でネットワークパケットの暗号化に使用可能。特徴を避けるため。予約済み
	tx.head.indexpts = 0;				  // コマンド統計値
	tx.head.cmd = cmd_connect;			  // コマンド
	memset(&softmouse, 0, sizeof(softmouse));	  // ソフトウェアマウスデータをゼロクリア
	memset(&softkeyboard, 0, sizeof(softkeyboard)); // ソフトウェアキーボードデータをゼロクリア
	err = sendto(sockClientfd, (const char*)&tx, sizeof(cmd_head_t), 0, (struct sockaddr*)&addrSrv, sizeof(addrSrv));
	Sleep(20); // 初回接続は時間がかかる場合がある
	int clen = sizeof(addrSrv);
	err = recvfrom(sockClientfd, (char*)&rx, 1024, 0, (struct sockaddr*)&addrSrv, &clen);
	if (err < 0)
		return err_net_rx_timeout;
	return NetRxReturnHandle(&rx, &tx);
}

/*
マウスをx,y単位で移動。一度の移動。軌道シミュレーションなし、最速。
独自の軌道移動を作成する際にこの関数を使用します。
戻り値：0は正常実行、その他は異常。
*/
int kmNet_mouse_move(short x, short y)
{
	int err;
	if (sockClientfd <= 0)		return err_creat_socket;
	tx.head.indexpts++;				// コマンド統計値
	tx.head.cmd = cmd_mouse_move;	// コマンド
	tx.head.rand = rand();			// ランダムなノイズ値
	softmouse.x = x;
	softmouse.y = y;
	memcpy(&tx.cmd_mouse, &softmouse, sizeof(soft_mouse_t));
	int length = sizeof(cmd_head_t) + sizeof(soft_mouse_t);
	sendto(sockClientfd, (const char*)&tx, length, 0, (struct sockaddr*)&addrSrv, sizeof(addrSrv));
	softmouse.x = 0;
	softmouse.y = 0;
	SOCKADDR_IN sclient;
	int clen = sizeof(sclient);
	err = recvfrom(sockClientfd, (char*)&rx, 1024, 0, (struct sockaddr*)&sclient, &clen);
	if (err < 0)
		return err_net_rx_timeout;
	return NetRxReturnHandle(&rx, &tx);
}



/*
マウス左ボタン制御
isdown : 0=リリース、1=プレス
戻り値：0は正常実行、その他は異常。
*/
int kmNet_mouse_left(int isdown)
{
	int err;
	if (sockClientfd <= 0)		return err_creat_socket;
	tx.head.indexpts++;				// コマンド統計値
	tx.head.cmd = cmd_mouse_left;	// コマンド
	tx.head.rand = rand();			// ランダムなノイズ値
	softmouse.button = (isdown ? (softmouse.button | 0x01) : (softmouse.button & (~0x01)));
	memcpy(&tx.cmd_mouse, &softmouse, sizeof(soft_mouse_t));
	int length = sizeof(cmd_head_t) + sizeof(soft_mouse_t);
	sendto(sockClientfd, (const char*)&tx, length, 0, (struct sockaddr*)&addrSrv, sizeof(addrSrv));
	SOCKADDR_IN sclient;
	int clen = sizeof(sclient);
	err = recvfrom(sockClientfd, (char*)&rx, 1024, 0, (struct sockaddr*)&sclient, &clen);
	if (err < 0)
		return err_net_rx_timeout;
	return NetRxReturnHandle(&rx, &tx);
}

/*
マウス中ボタン制御
isdown : 0=リリース、1=プレス
戻り値：0は正常実行、その他は異常。
*/
int kmNet_mouse_middle(int isdown)
{
	int err;
	if (sockClientfd <= 0)		return err_creat_socket;
	tx.head.indexpts++;				// コマンド統計値
	tx.head.cmd = cmd_mouse_middle;	// コマンド
	tx.head.rand = rand();			// ランダムなノイズ値
	softmouse.button = (isdown ? (softmouse.button | 0x04) : (softmouse.button & (~0x04)));
	memcpy(&tx.cmd_mouse, &softmouse, sizeof(soft_mouse_t));
	int length = sizeof(cmd_head_t) + sizeof(soft_mouse_t);
	sendto(sockClientfd, (const char*)&tx, length, 0, (struct sockaddr*)&addrSrv, sizeof(addrSrv));
	SOCKADDR_IN sclient;
	int clen = sizeof(sclient);
	err = recvfrom(sockClientfd, (char*)&rx, 1024, 0, (struct sockaddr*)&sclient, &clen);
	if (err < 0)
		return err_net_rx_timeout;
	return NetRxReturnHandle(&rx, &tx);
}

/*
マウス右ボタン制御
isdown : 0=リリース、1=プレス
戻り値：0は正常実行、その他は異常。
*/
int kmNet_mouse_right(int isdown)
{
	int err;
	if (sockClientfd <= 0)		return err_creat_socket;
	tx.head.indexpts++;				// コマンド統計値
	tx.head.cmd = cmd_mouse_right;	// コマンド
	tx.head.rand = rand();			// ランダムなノイズ値
	softmouse.button = (isdown ? (softmouse.button | 0x02) : (softmouse.button & (~0x02)));
	memcpy(&tx.cmd_mouse, &softmouse, sizeof(soft_mouse_t));
	int length = sizeof(cmd_head_t) + sizeof(soft_mouse_t);
	sendto(sockClientfd, (const char*)&tx, length, 0, (struct sockaddr*)&addrSrv, sizeof(addrSrv));
	SOCKADDR_IN sclient;
	int clen = sizeof(sclient);
	err = recvfrom(sockClientfd, (char*)&rx, 1024, 0, (struct sockaddr*)&sclient, &clen);
	if (err < 0)
		return err_net_rx_timeout;
	return NetRxReturnHandle(&rx, &tx);
}

// マウスホイール制御
int kmNet_mouse_wheel(int wheel)
{
	int err;
	if (sockClientfd <= 0)		return err_creat_socket;
	tx.head.indexpts++;				// コマンド統計値
	tx.head.cmd = cmd_mouse_wheel;	// コマンド
	tx.head.rand = rand();			// ランダムなノイズ値
	softmouse.wheel = wheel;
	memcpy(&tx.cmd_mouse, &softmouse, sizeof(soft_mouse_t));
	int length = sizeof(cmd_head_t) + sizeof(soft_mouse_t);
	softmouse.wheel = 0;
	sendto(sockClientfd, (const char*)&tx, length, 0, (struct sockaddr*)&addrSrv, sizeof(addrSrv));
	SOCKADDR_IN sclient;
	int clen = sizeof(sclient);
	err = recvfrom(sockClientfd, (char*)&rx, 1024, 0, (struct sockaddr*)&sclient, &clen);
	if (err < 0)
		return err_net_rx_timeout;
	return NetRxReturnHandle(&rx, &tx);
}


/*
マウス全レポート制御関数
*/
int kmNet_mouse_all(int button, int x, int y, int wheel)
{
	int err;
	if (sockClientfd <= 0)		return err_creat_socket;
	tx.head.indexpts++;				// コマンド統計値
	tx.head.cmd = cmd_mouse_wheel;	// コマンド
	tx.head.rand = rand();			// ランダムなノイズ値
	softmouse.button = button;
	softmouse.x = x;
	softmouse.y = y;
	softmouse.wheel = wheel;
	memcpy(&tx.cmd_mouse, &softmouse, sizeof(soft_mouse_t));
	int length = sizeof(cmd_head_t) + sizeof(soft_mouse_t);
	softmouse.x = 0;
	softmouse.y = 0;
	softmouse.wheel = 0;
	sendto(sockClientfd, (const char*)&tx, length, 0, (struct sockaddr*)&addrSrv, sizeof(addrSrv));
	SOCKADDR_IN sclient;
	int clen = sizeof(sclient);
	err = recvfrom(sockClientfd, (char*)&rx, 1024, 0, (struct sockaddr*)&sclient, &clen);
	if (err < 0)
		return err_net_rx_timeout;
	return NetRxReturnHandle(&rx, &tx);
}

/*
マウスをx,y単位で移動。人間的な移動をシミュレートし、キーボード・マウスの異常検出を回避します。
移動曲線を作成していない場合にこの関数の使用を推奨します。この関数は跳躍現象を起こさず、最小ステップで
目標点に近づきます。kmNet_mouse_moveよりも時間がかかります。
msは移動にかかる時間をミリ秒単位で設定します。msの値が小さすぎると、キーボード・マウスのデータ異常が発生する
可能性があるため注意してください。できるだけ人間らしい操作に近づけてください。実際の所要時間はmsより短くなります。
*/
int kmNet_mouse_move_auto(int x, int y, int ms)
{
	int err;
	if (sockClientfd <= 0)		return err_creat_socket;
	tx.head.indexpts++;				 // コマンド統計値
	tx.head.cmd = cmd_mouse_automove; // コマンド
	tx.head.rand = ms;			     // ランダムなノイズ値
	softmouse.x = x;
	softmouse.y = y;
	memcpy(&tx.cmd_mouse, &softmouse, sizeof(soft_mouse_t));
	int length = sizeof(cmd_head_t) + sizeof(soft_mouse_t);
	softmouse.x = 0;				// ゼロクリア
	softmouse.y = 0;				// ゼロクリア
	sendto(sockClientfd, (const char*)&tx, length, 0, (struct sockaddr*)&addrSrv, sizeof(addrSrv));
	SOCKADDR_IN sclient;
	int clen = sizeof(sclient);
	err = recvfrom(sockClientfd, (char*)&rx, 1024, 0, (struct sockaddr*)&sclient, &clen);
	if (err < 0)
		return err_net_rx_timeout;
	return NetRxReturnHandle(&rx, &tx);
}



/*
2次ベジェ曲線制御
x,y 	: 目標点の座標
ms		: この過程を近似するための時間（単位ms）
x1,y1	: 制御点p1の座標
x2,y2	: 制御点p2の座標
*/
int kmNet_mouse_move_beizer(int x, int y, int ms, int x1, int y1, int x2, int y2)
{
	int err;
	if (sockClientfd <= 0)		return err_creat_socket;
	tx.head.indexpts++;			 // コマンド統計値
	tx.head.cmd = cmd_bazerMove; // コマンド
	tx.head.rand = ms;			 // ランダムなノイズ値
	softmouse.x = x;
	softmouse.y = y;
	softmouse.point[0] = x1;
	softmouse.point[1] = y1;
	softmouse.point[2] = x2;
	softmouse.point[3] = y2;
	memcpy(&tx.cmd_mouse, &softmouse, sizeof(soft_mouse_t));
	int length = sizeof(cmd_head_t) + sizeof(soft_mouse_t);
	softmouse.x = 0;
	softmouse.y = 0;
	sendto(sockClientfd, (const char*)&tx, length, 0, (struct sockaddr*)&addrSrv, sizeof(addrSrv));
	SOCKADDR_IN sclient;
	int clen = sizeof(sclient);
	err = recvfrom(sockClientfd, (char*)&rx, 1024, 0, (struct sockaddr*)&sclient, &clen);
	if (err < 0)
		return err_net_rx_timeout;
	return NetRxReturnHandle(&rx, &tx);
}



int kmNet_keydown(int vk_key)
{
	int i;
	if (vk_key >= KEY_LEFTCONTROL && vk_key <= KEY_RIGHT_GUI) // 制御キー
	{
		switch (vk_key)
		{
		case KEY_LEFTCONTROL: softkeyboard.ctrl |= BIT0; break;
		case KEY_LEFTSHIFT:   softkeyboard.ctrl |= BIT1; break;
		case KEY_LEFTALT:     softkeyboard.ctrl |= BIT2; break;
		case KEY_LEFT_GUI:    softkeyboard.ctrl |= BIT3; break;
		case KEY_RIGHTCONTROL:softkeyboard.ctrl |= BIT4; break;
		case KEY_RIGHTSHIFT:  softkeyboard.ctrl |= BIT5; break;
		case KEY_RIGHTALT:    softkeyboard.ctrl |= BIT6; break;
		case KEY_RIGHT_GUI:   softkeyboard.ctrl |= BIT7; break;
		}
	}
	else
	{ // 通常キー
		for (i = 0; i < 10; i++) // まずキュー内にvk_keyが存在するか確認
		{
			if (softkeyboard.button[i] == vk_key)
				goto KM_down_send; // キューに既にvk_keyがあれば、直接送信
		}
		// キューにvk_keyがない場合
		for (i = 0; i < 10; i++) // 全データを走査し、vk_keyをキューに追加
		{
			if (softkeyboard.button[i] == 0)
			{
				softkeyboard.button[i] = vk_key;
				goto KM_down_send;
			}
		}
		// キューが満杯の場合、最初の要素を削除
		memcpy(&softkeyboard.button[0], &softkeyboard.button[1], 10);
		softkeyboard.button[9] = vk_key;
	}
KM_down_send:
	int err;
	if (sockClientfd <= 0)		return err_creat_socket;
	tx.head.indexpts++;				// コマンド統計値
	tx.head.cmd = cmd_keyboard_all;	// コマンド
	tx.head.rand = rand();			// ランダムなノイズ値
	memcpy(&tx.cmd_keyboard, &softkeyboard, sizeof(soft_keyboard_t));
	int length = sizeof(cmd_head_t) + sizeof(soft_keyboard_t);
	sendto(sockClientfd, (const char*)&tx, length, 0, (struct sockaddr*)&addrSrv, sizeof(addrSrv));
	SOCKADDR_IN sclient;
	int clen = sizeof(sclient);
	err = recvfrom(sockClientfd, (char*)&rx, 1024, 0, (struct sockaddr*)&sclient, &clen);
	if (err < 0)
		return err_net_rx_timeout;
	return NetRxReturnHandle(&rx, &tx);
}




int kmNet_keyup(int vk_key)
{
	int i;
	if (vk_key >= KEY_LEFTCONTROL && vk_key <= KEY_RIGHT_GUI) // 制御キー
	{
		switch (vk_key)
		{
		case KEY_LEFTCONTROL: softkeyboard.ctrl &= ~BIT0; break;
		case KEY_LEFTSHIFT:   softkeyboard.ctrl &= ~BIT1; break;
		case KEY_LEFTALT:     softkeyboard.ctrl &= ~BIT2; break;
		case KEY_LEFT_GUI:    softkeyboard.ctrl &= ~BIT3; break;
		case KEY_RIGHTCONTROL:softkeyboard.ctrl &= ~BIT4; break;
		case KEY_RIGHTSHIFT:  softkeyboard.ctrl &= ~BIT5; break;
		case KEY_RIGHTALT:    softkeyboard.ctrl &= ~BIT6; break;
		case KEY_RIGHT_GUI:   softkeyboard.ctrl &= ~BIT7; break;
		}
	}
	else
	{ // 通常キー
		for (i = 0; i < 10; i++) // まずキュー内にvk_keyが存在するか確認
		{
			if (softkeyboard.button[i] == vk_key) // キューにvk_keyがある場合
			{
				memcpy(&softkeyboard.button[i], &softkeyboard.button[i + 1], 10 - i);
				softkeyboard.button[9] = 0;
				goto KM_up_send;
			}
		}
	}
KM_up_send:
	int err;
	if (sockClientfd <= 0)		return err_creat_socket;
	tx.head.indexpts++;				// コマンド統計値
	tx.head.cmd = cmd_keyboard_all;	// コマンド
	tx.head.rand = rand();			// ランダムなノイズ値
	memcpy(&tx.cmd_keyboard, &softkeyboard, sizeof(soft_keyboard_t));
	int length = sizeof(cmd_head_t) + sizeof(soft_keyboard_t);
	sendto(sockClientfd, (const char*)&tx, length, 0, (struct sockaddr*)&addrSrv, sizeof(addrSrv));
	SOCKADDR_IN sclient;
	int clen = sizeof(sclient);
	err = recvfrom(sockClientfd, (char*)&rx, 1024, 0, (struct sockaddr*)&sclient, &clen);
	if (err < 0)
		return err_net_rx_timeout;
	return NetRxReturnHandle(&rx, &tx);
}


// ボックスを再起動
int kmNet_reboot(void)
{
	int err;
	if (sockClientfd <= 0)		return err_creat_socket;
	tx.head.indexpts++;				// コマンド統計値
	tx.head.cmd = cmd_reboot;		// コマンド
	tx.head.rand = rand();			// ランダムなノイズ値
	int length = sizeof(cmd_head_t);
	sendto(sockClientfd, (const char*)&tx, length, 0, (struct sockaddr*)&addrSrv, sizeof(addrSrv));
	SOCKADDR_IN sclient;
	int clen = sizeof(sclient);
	err = recvfrom(sockClientfd, (char*)&rx, 1024, 0, (struct sockaddr*)&sclient, &clen);
	WSACleanup();
	sockClientfd = -1;
	if (err < 0)
		return err_net_rx_timeout;
	return NetRxReturnHandle(&rx, &tx);

}



// 物理キーボード・マウスを監視
DWORD WINAPI ThreadListenProcess(LPVOID lpParameter)
{
	WSADATA wsaData; int ret;
	WSAStartup(MAKEWORD(1, 1), &wsaData);			// ソケット作成、SOCK_DGRAMはUDPプロトコルを使用
	sockMonitorfd = socket(AF_INET, SOCK_DGRAM, 0);	// ソケットをバインド
	sockaddr_in servAddr;
	memset(&servAddr, 0, sizeof(servAddr));			// 各バイトを0で埋める
	servAddr.sin_family = PF_INET;				// IPv4アドレスを使用
	servAddr.sin_addr.s_addr = INADDR_ANY;	        // IPアドレスを自動取得
	servAddr.sin_port = htons(monitor_port);		// 監視ポート
	ret = bind(sockMonitorfd, (SOCKADDR*)&servAddr, sizeof(SOCKADDR));
	SOCKADDR cliAddr;  // クライアントアドレス情報
	int nSize = sizeof(SOCKADDR);
	char buff[1024];  // バッファ
	monitor_run = monitor_ok;
	while (1) {
		int ret = recvfrom(sockMonitorfd, buff, 1024, 0, &cliAddr, &nSize);	// データをブロッキング読み込み
		if (ret > 0)
		{
			memcpy(&hw_mouse, buff, sizeof(hw_mouse));							// 物理マウスの状態
			memcpy(&hw_keyboard, &buff[sizeof(hw_mouse)], sizeof(hw_keyboard));	// 物理キーボードの状態
		}
		else
		{
			break;
		}
	}
	monitor_run = 0;
	sockMonitorfd = 0;
	return 0;

}

// キーボード・マウス監視を有効化 ポート番号の範囲は1024から49151
int kmNet_monitor(short port)
{
	int err;
	if (sockClientfd <= 0)		return err_creat_socket;
	tx.head.indexpts++;				// コマンド統計値
	tx.head.cmd = cmd_monitor;		// コマンド
	if (port) {
		monitor_port = port;				// 物理キーボード・マウスデータを監視するポート
		tx.head.rand = port | 0xaa55 << 16;	// ランダムなノイズ値
	}
	else
		tx.head.rand = 0;	// ランダムなノイズ値
	int length = sizeof(cmd_head_t);
	sendto(sockClientfd, (const char*)&tx, length, 0, (struct sockaddr*)&addrSrv, sizeof(addrSrv));
	SOCKADDR_IN sclient;
	int clen = sizeof(sclient);
	err = recvfrom(sockClientfd, (char*)&rx, 1024, 0, (struct sockaddr*)&sclient, &clen);
	if (sockMonitorfd > 0)	// 監視を閉じる
	{
		closesocket(sockMonitorfd);
		sockMonitorfd = 0;
	}
	if (port)
	{
		CreateThread(NULL, 0, ThreadListenProcess, NULL, 0, NULL);
	}
	Sleep(10); // スレッドが実行される時間を少し確保
	if (err < 0)
		return err_net_rx_timeout;
	return NetRxReturnHandle(&rx, &tx);
}


/*
物理マウスの左ボタンの状態を監視
戻り値
-1：監視機能がまだ有効になっていない。先にkmNet_monitor(port)を呼び出す必要があります
0 : 物理マウスの左ボタンがリリースされている
1：物理マウスの左ボタンが押されている
*/
int kmNet_monitor_mouse_left()
{
	if (monitor_run != monitor_ok) return -1;
	return (hw_mouse.buttons & 0x01) ? 1 : 0;
}


/*
物理マウスの中ボタンの状態を監視
戻り値
-1：監視機能がまだ有効になっていない。先にkmNet_monitor(port)を呼び出す必要があります
0 : 物理マウスの中ボタンがリリースされている
1：物理マウスの中ボタンが押されている
*/
int kmNet_monitor_mouse_middle()
{
	if (monitor_run != monitor_ok) return -1;
	return (hw_mouse.buttons & 0x04) ? 1 : 0;
}

/*
物理マウスの右ボタンの状態を監視
戻り値
-1：監視機能がまだ有効になっていない。先にkmNet_monitor(port)を呼び出す必要があります
0 : 物理マウスの右ボタンがリリースされている
1：物理マウスの右ボタンが押されている
*/
int kmNet_monitor_mouse_right()
{
	if (monitor_run != monitor_ok) return -1;
	return (hw_mouse.buttons & 0x02) ? 1 : 0;
}


/*
物理マウスのサイドボタン1の状態を監視
戻り値
-1：監視機能がまだ有効になっていない。先にkmNet_monitor(port)を呼び出す必要があります
0 : 物理マウスのサイドボタン1がリリースされている
1：物理マウスのサイドボタン1が押されている
*/
int kmNet_monitor_mouse_side1()
{
	if (monitor_run != monitor_ok) return -1;
	return (hw_mouse.buttons & 0x08) ? 1 : 0;
}

/*
物理マウスのサイドボタン2の状態を監視
戻り値
-1：監視機能がまだ有効になっていない。先にkmNet_monitor(port)を呼び出す必要があります
0 : 物理マウスのサイドボタン2がリリースされている
1：物理マウスのサイドボタン2が押されている
*/
int kmNet_monitor_mouse_side2()
{
	if (monitor_run != monitor_ok) return -1;
	return (hw_mouse.buttons & 0x10) ? 1 : 0;
}



// キーボードの指定キーの状態を監視
int kmNet_monitor_keyboard(short  vkey)
{
	unsigned char vk_key = vkey & 0xff;
	if (monitor_run != monitor_ok) return -1;
	if (vk_key >= KEY_LEFTCONTROL && vk_key <= KEY_RIGHT_GUI) // 制御キー
	{
		switch (vk_key)
		{
		case KEY_LEFTCONTROL: return  hw_keyboard.buttons & BIT0 ? 1 : 0;
		case KEY_LEFTSHIFT:   return  hw_keyboard.buttons & BIT1 ? 1 : 0;
		case KEY_LEFTALT:     return  hw_keyboard.buttons & BIT2 ? 1 : 0;
		case KEY_LEFT_GUI:    return  hw_keyboard.buttons & BIT3 ? 1 : 0;
		case KEY_RIGHTCONTROL:return  hw_keyboard.buttons & BIT4 ? 1 : 0;
		case KEY_RIGHTSHIFT:  return  hw_keyboard.buttons & BIT5 ? 1 : 0;
		case KEY_RIGHTALT:    return  hw_keyboard.buttons & BIT6 ? 1 : 0;
		case KEY_RIGHT_GUI:   return  hw_keyboard.buttons & BIT7 ? 1 : 0;
		}
	}
	else // 通常キー
	{
		for (int i = 0; i < 10; i++)
		{
			if (hw_keyboard.data[i] == vk_key)
			{
				return 1;
			}
		}
	}
	return 0;
}


// ボックス内部のプリント情報を有効にし、指定ポートに送信（デバッグ用）
int kmNet_debug(short port, char enable)
{
	int err;
	if (sockClientfd <= 0)		return err_creat_socket;
	tx.head.indexpts++;					// コマンド統計値
	tx.head.cmd = cmd_debug;			// コマンド
	tx.head.rand = port | enable << 16;	// ランダムなノイズ値
	int length = sizeof(cmd_head_t);
	sendto(sockClientfd, (const char*)&tx, length, 0, (struct sockaddr*)&addrSrv, sizeof(addrSrv));
	SOCKADDR_IN sclient;
	int clen = sizeof(sclient);
	err = recvfrom(sockClientfd, (char*)&rx, 1024, 0, (struct sockaddr*)&sclient, &clen);
	if (err < 0)
		return err_net_rx_timeout;
	return NetRxReturnHandle(&rx, &tx);
}

// マウス左ボタンを無効化
int kmNet_mask_mouse_left(int enable)
{
	int err;
	if (sockClientfd <= 0)		return err_creat_socket;
	tx.head.indexpts++;					// コマンド統計値
	tx.head.cmd = cmd_mask_mouse;		// コマンド
	tx.head.rand = enable ? (mask_keyboard_mouse_flag |= BIT0) : (mask_keyboard_mouse_flag &= ~BIT0);	// マウス左ボタンを無効化
	int length = sizeof(cmd_head_t);
	sendto(sockClientfd, (const char*)&tx, length, 0, (struct sockaddr*)&addrSrv, sizeof(addrSrv));
	SOCKADDR_IN sclient;
	int clen = sizeof(sclient);
	err = recvfrom(sockClientfd, (char*)&rx, 1024, 0, (struct sockaddr*)&sclient, &clen);
	if (err < 0)
		return err_net_rx_timeout;
	return NetRxReturnHandle(&rx, &tx);
}

// マウス右ボタンを無効化
int kmNet_mask_mouse_right(int enable)
{
	int err;
	if (sockClientfd <= 0)		return err_creat_socket;
	tx.head.indexpts++;					// コマンド統計値
	tx.head.cmd = cmd_mask_mouse;		// コマンド
	tx.head.rand = enable ? (mask_keyboard_mouse_flag |= BIT1) : (mask_keyboard_mouse_flag &= ~BIT1);	// マウス右ボタンを無効化
	int length = sizeof(cmd_head_t);
	sendto(sockClientfd, (const char*)&tx, length, 0, (struct sockaddr*)&addrSrv, sizeof(addrSrv));
	SOCKADDR_IN sclient;
	int clen = sizeof(sclient);
	err = recvfrom(sockClientfd, (char*)&rx, 1024, 0, (struct sockaddr*)&sclient, &clen);
	if (err < 0)
		return err_net_rx_timeout;
	return NetRxReturnHandle(&rx, &tx);
}


// マウス中ボタンを無効化
int kmNet_mask_mouse_middle(int enable)
{
	int err;
	if (sockClientfd <= 0)		return err_creat_socket;
	tx.head.indexpts++;					// コマンド統計値
	tx.head.cmd = cmd_mask_mouse;		// コマンド
	tx.head.rand = enable ? (mask_keyboard_mouse_flag |= BIT2) : (mask_keyboard_mouse_flag &= ~BIT2);	// マウス中ボタンを無効化
	int length = sizeof(cmd_head_t);
	sendto(sockClientfd, (const char*)&tx, length, 0, (struct sockaddr*)&addrSrv, sizeof(addrSrv));
	SOCKADDR_IN sclient;
	int clen = sizeof(sclient);
	err = recvfrom(sockClientfd, (char*)&rx, 1024, 0, (struct sockaddr*)&sclient, &clen);
	if (err < 0)
		return err_net_rx_timeout;
	return NetRxReturnHandle(&rx, &tx);
}


// マウスサイドボタン1を無効化
int kmNet_mask_mouse_side1(int enable)
{
	int err;
	if (sockClientfd <= 0)		return err_creat_socket;
	tx.head.indexpts++;					// コマンド統計値
	tx.head.cmd = cmd_mask_mouse;		// コマンド
	tx.head.rand = enable ? (mask_keyboard_mouse_flag |= BIT3) : (mask_keyboard_mouse_flag &= ~BIT3);	// マウスサイドボタン1を無効化
	int length = sizeof(cmd_head_t);
	sendto(sockClientfd, (const char*)&tx, length, 0, (struct sockaddr*)&addrSrv, sizeof(addrSrv));
	SOCKADDR_IN sclient;
	int clen = sizeof(sclient);
	err = recvfrom(sockClientfd, (char*)&rx, 1024, 0, (struct sockaddr*)&sclient, &clen);
	if (err < 0)
		return err_net_rx_timeout;
	return NetRxReturnHandle(&rx, &tx);
}



// マウスサイドボタン2を無効化
int kmNet_mask_mouse_side2(int enable)
{
	int err;
	if (sockClientfd <= 0)		return err_creat_socket;
	tx.head.indexpts++;					// コマンド統計値
	tx.head.cmd = cmd_mask_mouse;		// コマンド
	tx.head.rand = enable ? (mask_keyboard_mouse_flag |= BIT4) : (mask_keyboard_mouse_flag &= ~BIT4);	// マウスサイドボタン2を無効化
	int length = sizeof(cmd_head_t);
	sendto(sockClientfd, (const char*)&tx, length, 0, (struct sockaddr*)&addrSrv, sizeof(addrSrv));
	SOCKADDR_IN sclient;
	int clen = sizeof(sclient);
	err = recvfrom(sockClientfd, (char*)&rx, 1024, 0, (struct sockaddr*)&sclient, &clen);
	if (err < 0)
		return err_net_rx_timeout;
	return NetRxReturnHandle(&rx, &tx);
}


// マウスX軸座標を無効化
int kmNet_mask_mouse_x(int enable)
{
	int err;
	if (sockClientfd <= 0)		return err_creat_socket;
	tx.head.indexpts++;					// コマンド統計値
	tx.head.cmd = cmd_mask_mouse;		// コマンド
	tx.head.rand = enable ? (mask_keyboard_mouse_flag |= BIT5) : (mask_keyboard_mouse_flag &= ~BIT5);	// マウスX軸を無効化
	int length = sizeof(cmd_head_t);
	sendto(sockClientfd, (const char*)&tx, length, 0, (struct sockaddr*)&addrSrv, sizeof(addrSrv));
	SOCKADDR_IN sclient;
	int clen = sizeof(sclient);
	err = recvfrom(sockClientfd, (char*)&rx, 1024, 0, (struct sockaddr*)&sclient, &clen);
	if (err < 0)
		return err_net_rx_timeout;
	return NetRxReturnHandle(&rx, &tx);
}


// マウスY軸座標を無効化
int kmNet_mask_mouse_y(int enable)
{
	int err;
	if (sockClientfd <= 0)		return err_creat_socket;
	tx.head.indexpts++;					// コマンド統計値
	tx.head.cmd = cmd_mask_mouse;		// コマンド
	tx.head.rand = enable ? (mask_keyboard_mouse_flag |= BIT6) : (mask_keyboard_mouse_flag &= ~BIT6);	// マウスY軸を無効化
	int length = sizeof(cmd_head_t);
	sendto(sockClientfd, (const char*)&tx, length, 0, (struct sockaddr*)&addrSrv, sizeof(addrSrv));
	SOCKADDR_IN sclient;
	int clen = sizeof(sclient);
	err = recvfrom(sockClientfd, (char*)&rx, 1024, 0, (struct sockaddr*)&sclient, &clen);
	if (err < 0)
		return err_net_rx_timeout;
	return NetRxReturnHandle(&rx, &tx);
}

// マウスホイールを無効化
int kmNet_mask_mouse_wheel(int enable)
{
	int err;
	if (sockClientfd <= 0)		return err_creat_socket;
	tx.head.indexpts++;					// コマンド統計値
	tx.head.cmd = cmd_mask_mouse;		// コマンド
	tx.head.rand = enable ? (mask_keyboard_mouse_flag |= BIT7) : (mask_keyboard_mouse_flag &= ~BIT7);	// マウスホイールを無効化
	int length = sizeof(cmd_head_t);
	sendto(sockClientfd, (const char*)&tx, length, 0, (struct sockaddr*)&addrSrv, sizeof(addrSrv));
	SOCKADDR_IN sclient;
	int clen = sizeof(sclient);
	err = recvfrom(sockClientfd, (char*)&rx, 1024, 0, (struct sockaddr*)&sclient, &clen);
	if (err < 0)
		return err_net_rx_timeout;
	return NetRxReturnHandle(&rx, &tx);
}


// キーボードの指定キーを無効化
int kmNet_mask_keyboard(short vkey)
{
	int err;
	BYTE v_key = vkey & 0xff;
	if (sockClientfd <= 0)		return err_creat_socket;
	tx.head.indexpts++;					// コマンド統計値
	tx.head.cmd = cmd_mask_mouse;		// コマンド
	tx.head.rand = (mask_keyboard_mouse_flag & 0xff) | (v_key << 8);	// キーボードのvkeyを無効化
	int length = sizeof(cmd_head_t);
	sendto(sockClientfd, (const char*)&tx, length, 0, (struct sockaddr*)&addrSrv, sizeof(addrSrv));
	SOCKADDR_IN sclient;
	int clen = sizeof(sclient);
	err = recvfrom(sockClientfd, (char*)&rx, 1024, 0, (struct sockaddr*)&sclient, &clen);
	if (err < 0)
		return err_net_rx_timeout;
	return NetRxReturnHandle(&rx, &tx);
}


// キーボードの指定キーの無効化を解除
int kmNet_unmask_keyboard(short vkey)
{
	int err;
	BYTE v_key = vkey & 0xff;
	if (sockClientfd <= 0)		return err_creat_socket;
	tx.head.indexpts++;					// コマンド統計値
	tx.head.cmd = cmd_unmask_all;		// コマンド
	tx.head.rand = (mask_keyboard_mouse_flag & 0xff) | (v_key << 8);	// キーボードのvkeyの無効化を解除
	int length = sizeof(cmd_head_t);
	sendto(sockClientfd, (const char*)&tx, length, 0, (struct sockaddr*)&addrSrv, sizeof(addrSrv));
	SOCKADDR_IN sclient;
	int clen = sizeof(sclient);
	err = recvfrom(sockClientfd, (char*)&rx, 1024, 0, (struct sockaddr*)&sclient, &clen);
	if (err < 0)
		return err_net_rx_timeout;
	return NetRxReturnHandle(&rx, &tx);
}


// 設定済みのすべての物理的な無効化を解除
int kmNet_unmask_all()
{
	int err;
	if (sockClientfd <= 0)		return err_creat_socket;
	tx.head.indexpts++;					// コマンド統計値
	tx.head.cmd = cmd_unmask_all;		// コマンド
	mask_keyboard_mouse_flag = 0;
	tx.head.rand = mask_keyboard_mouse_flag;
	int length = sizeof(cmd_head_t);
	sendto(sockClientfd, (const char*)&tx, length, 0, (struct sockaddr*)&addrSrv, sizeof(addrSrv));
	SOCKADDR_IN sclient;
	int clen = sizeof(sclient);
	err = recvfrom(sockClientfd, (char*)&rx, 1024, 0, (struct sockaddr*)&sclient, &clen);
	if (err < 0)
		return err_net_rx_timeout;
	return NetRxReturnHandle(&rx, &tx);
}



// 設定情報を設定 IPとポート番号を変更
int kmNet_setconfig(char* ip, unsigned short port)
{
	int err;
	if (sockClientfd <= 0)		return err_creat_socket;
	tx.head.indexpts++;					// コマンド統計値
	tx.head.cmd = cmd_setconfig;		// コマンド
	tx.head.rand = inet_addr(ip); ;
	tx.u8buff.buff[0] = port >> 8;
	tx.u8buff.buff[1] = port >> 0;
	int length = sizeof(cmd_head_t) + 2;
	sendto(sockClientfd, (const char*)&tx, length, 0, (struct sockaddr*)&addrSrv, sizeof(addrSrv));
	SOCKADDR_IN sclient;
	int clen = sizeof(sclient);
	err = recvfrom(sockClientfd, (char*)&rx, 1024, 0, (struct sockaddr*)&sclient, &clen);
	if (err < 0)
		return err_net_rx_timeout;
	return NetRxReturnHandle(&rx, &tx);
}


// LCD画面全体を指定色で塗りつぶす。画面クリアには黒を使用可能
int kmNet_lcd_color(unsigned short rgb565)
{
	int err;
	if (sockClientfd <= 0)		return err_creat_socket;
	for (int y = 0; y < 40; y++)
	{
		tx.head.indexpts++;		    // コマンド統計値
		tx.head.cmd = cmd_showpic;	// コマンド
		tx.head.rand = 0 | y * 4;
		for (int c = 0; c < 512; c++)
			tx.u16buff.buff[c] = rgb565;
		int length = sizeof(cmd_head_t) + 1024;
		sendto(sockClientfd, (const char*)&tx, length, 0, (struct sockaddr*)&addrSrv, sizeof(addrSrv));
		SOCKADDR_IN sclient;
		int clen = sizeof(sclient);
		err = recvfrom(sockClientfd, (char*)&rx, length, 0, (struct sockaddr*)&sclient, &clen);
		if (err < 0)
			return err_net_rx_timeout;
	}
	return NetRxReturnHandle(&rx, &tx);

}

// 画面下部に128x80の画像を表示
int kmNet_lcd_picture_bottom(unsigned char* buff_128_80)
{
	int err;
	if (sockClientfd <= 0)		return err_creat_socket;
	for (int y = 0; y < 20; y++)
	{
		tx.head.indexpts++;		    // コマンド統計値
		tx.head.cmd = cmd_showpic;	// コマンド
		tx.head.rand = 80 + y * 4;
		memcpy(tx.u8buff.buff, &buff_128_80[y * 1024], 1024);
		int length = sizeof(cmd_head_t) + 1024;
		sendto(sockClientfd, (const char*)&tx, length, 0, (struct sockaddr*)&addrSrv, sizeof(addrSrv));
		SOCKADDR_IN sclient;
		int clen = sizeof(sclient);
		err = recvfrom(sockClientfd, (char*)&rx, length, 0, (struct sockaddr*)&sclient, &clen);
		if (err < 0)
			return err_net_rx_timeout;
	}
	return NetRxReturnHandle(&rx, &tx);
}

// 全画面に128x160の画像を表示
int kmNet_lcd_picture(unsigned char* buff_128_160)
{
	int err;
	if (sockClientfd <= 0)		return err_creat_socket;
	for (int y = 0; y < 40; y++)
	{
		tx.head.indexpts++;		    // コマンド統計値
		tx.head.cmd = cmd_showpic;	// コマンド
		tx.head.rand = y * 4;
		memcpy(tx.u8buff.buff, &buff_128_160[y * 1024], 1024);
		int length = sizeof(cmd_head_t) + 1024;
		sendto(sockClientfd, (const char*)&tx, length, 0, (struct sockaddr*)&addrSrv, sizeof(addrSrv));
		SOCKADDR_IN sclient;
		int clen = sizeof(sclient);
		err = recvfrom(sockClientfd, (char*)&rx, length, 0, (struct sockaddr*)&sclient, &clen);
		if (err < 0)
			return err_net_rx_timeout;
	}
	return NetRxReturnHandle(&rx, &tx);
}