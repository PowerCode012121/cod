#pragma once

#include <Winsock2.h>
#include <stdio.h>
#include "math.h"
#pragma warning(disable : 4996)

// コマンドコード
#define 	cmd_connect			0xaf3c2828 // ok ボックスに接続
#define     cmd_mouse_move		0xaede7345 // ok マウス移動
#define		cmd_mouse_left		0x9823AE8D // ok マウス左ボタン制御
#define		cmd_mouse_middle	0x97a3AE8D // ok マウス中ボタン制御
#define		cmd_mouse_right		0x238d8212 // ok マウス右ボタン制御
#define		cmd_mouse_wheel		0xffeead38 // ok マウスホイール制御
#define     cmd_mouse_automove	0xaede7346 // ok マウスの自動的な人間的移動シミュレーション制御
#define     cmd_keyboard_all    0x123c2c2f // ok キーボードの全パラメータ制御
#define		cmd_reboot			0xaa8855aa // ok ボックス再起動
#define     cmd_bazerMove       0xa238455a // ok マウスのベジェ曲線移動
#define     cmd_monitor         0x27388020 // ok ボックス上の物理的なキーボード・マウスデータを監視
#define     cmd_debug           0x27382021 // ok デバッグ情報を有効化
#define     cmd_mask_mouse      0x23234343 // ok 物理的なキーボード・マウスを無効化
#define     cmd_unmask_all      0x23344343 // ok 物理的なキーボード・マウスの無効化を解除
#define     cmd_setconfig       0x1d3d3323 // ok IP設定情報をセット
#define     cmd_showpic         0x12334883 // 画像を表示

extern SOCKET sockClientfd; // ソケット通信ハンドル

typedef struct
{
	unsigned int  mac;			// ボックスのMACアドレス（必須）
	unsigned int  rand;			// ランダム値
	unsigned int  indexpts;		// タイムスタンプ
	unsigned int  cmd;			// コマンドコード
}cmd_head_t;

typedef struct
{
	unsigned char buff[1024];	//
}cmd_data_t;
typedef struct
{
	unsigned short buff[512];	//
}cmd_u16_t;

// マウスデータ構造体
typedef struct
{
	int button;
	int x;
	int y;
	int wheel;
	int point[10]; // ベジェ曲線制御用（5次導関数用に予約）
}soft_mouse_t;

// キーボードデータ構造体
typedef struct
{
	char ctrl;
	char resvel;
	char button[10];
}soft_keyboard_t;

// 共用体
typedef struct
{
	cmd_head_t head;
	union {
		cmd_data_t      u8buff;		  // buff
		cmd_u16_t       u16buff;	  // U16
		soft_mouse_t    cmd_mouse;    // マウス送信コマンド
		soft_keyboard_t cmd_keyboard; // キーボード送信コマンド
	};
}client_tx;

enum
{
	err_creat_socket = -9000,	// ソケットの作成に失敗
	err_net_version,		    // socketバージョンエラー
	err_net_tx,		            // socket送信エラー
	err_net_rx_timeout,		    // socket受信タイムアウト
	err_net_cmd,			    // コマンドエラー
	err_net_pts,			    // タイムスタンプエラー
	success = 0,				// 正常に実行
	usb_dev_tx_timeout,		    // USB device送信失敗
};

/*
kmboxNetボックスへの接続、入力パラメータはそれぞれボックスの
ip  ：ボックスのIPアドレス（ディスプレイに表示されます）
port: 通信ポート番号（ディスプレイに表示されます）
mac : ボックスのMACアドレス（ディスプレイに表示されます）
戻り値：接続成功時は0、その他の値はエラーコードを参照
*/
int kmNet_init(char* ip, char* port, char* mac);            // ok
int kmNet_mouse_move(short x, short y);			            // ok
int kmNet_mouse_left(int isdown);				            // ok
int kmNet_mouse_right(int isdown);				            // ok
int kmNet_mouse_middle(int isdown);				            // ok
int kmNet_mouse_wheel(int wheel);				            // ok
int kmNet_mouse_all(int button, int x, int y, int wheel);   // ok
int kmNet_mouse_move_auto(int x, int y, int time_ms);	    // ok
int kmNet_mouse_move_beizer(int x, int y, int ms, int x1, int y1, int x2, int y2); // 2次曲線

// キーボード関数
int kmNet_keydown(int vkey); // ok
int kmNet_keyup(int vkey);   // ok

// 監視シリーズ
int kmNet_monitor(short port);			        // 物理キーボード・マウス監視の有効/無効化
int kmNet_monitor_mouse_left();			        // 物理マウスの左ボタンの状態を照会
int kmNet_monitor_mouse_middle();		        // マウスの中ボタンの状態を照会
int kmNet_monitor_mouse_right();		        // マウスの右ボタンの状態を照会
int kmNet_monitor_mouse_side1();		        // マウスのサイドボタン1の状態を照会
int kmNet_monitor_mouse_side2();		        // マウスのサイドボタン2の状態を照会
int kmNet_monitor_keyboard(short  vk_key);      // キーボードの指定キーの状態を照会

// 物理キーボード・マウスの無効化シリーズ
int kmNet_mask_mouse_left(int enable);	    // マウス左ボタンを無効化
int kmNet_mask_mouse_right(int enable);	    // マウス右ボタンを無効化
int kmNet_mask_mouse_middle(int enable);    // マウス中ボタンを無効化
int kmNet_mask_mouse_side1(int enable);	    // マウスサイドボタン1を無効化
int kmNet_mask_mouse_side2(int enable);	    // マウスサイドボタン2を無効化
int kmNet_mask_mouse_x(int enable);		    // マウスX軸座標を無効化
int kmNet_mask_mouse_y(int enable);		    // マウスY軸座標を無効化
int kmNet_mask_mouse_wheel(int enable);	    // マウスホイールを無効化
int kmNet_mask_keyboard(short vkey);	    // キーボードの指定キーを無効化
int kmNet_unmask_keyboard(short vkey);	    // キーボードの指定キーの無効化を解除
int kmNet_unmask_all();					    // 設定済みのすべての物理的な無効化を解除


// 設定系関数
int kmNet_reboot(void);
int kmNet_setconfig(char* ip, unsigned short port);		  // ボックスのIPアドレスを設定
int kmNet_debug(short port, char enable);				  // デバッグ有効化
int kmNet_lcd_color(unsigned short rgb565);				  // LCD画面全体を指定色で塗りつぶす。画面クリアには黒を使用可能
int kmNet_lcd_picture_bottom(unsigned char* buff_128_80); // 下半分に128x80の画像を表示
int kmNet_lcd_picture(unsigned char* buff_128_160);		  // 全画面に128x160の画像を表示


// ビデオキャプチャ系関数
#if 0
int kvm_setvideo(int width, int height, int fps); // キャプチャビデオの解像度とフレームレートを設定
int kvm_getframe(Mat* frame);					  // 最新フレームの画像データを取得
int kvm_load_yolo_module(char* path);			  // YOLOモデルのパスをロード
int kvm_run_yolo(Mat* frame, int cpu_gpu);		  // 画像推論
#endif