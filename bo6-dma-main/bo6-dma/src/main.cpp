#include "includes.h"

int main()
{
	if (!mem.Init("cod.exe", false, false, false))
	{
		printf("Failed To Init DMA.\n");
		std::cin.get();
		return 0;
	}

	if (!mem.GetKeyboard()->InitKeyboard())
	{
		printf("Failed To Initialise Keybinds.\n");
		std::cin.get();
	}

	std::ifstream cfg_file("kmbox.txt");
	if (cfg_file.is_open())
	{
		cfg_file.getline(cfg::ip, sizeof(cfg::ip));
		cfg_file.getline(cfg::port, sizeof(cfg::port));
		cfg_file.getline(cfg::uuid, sizeof(cfg::uuid));
		cfg_file.close();

		if (cfg::ip && cfg::port && cfg::uuid)
		{
			cfg::kmnet_connected = kmNet_init(cfg::ip, cfg::port, cfg::uuid) == 0;

			if (cfg::kmnet_connected)
			{
				printf("Kmbox NET Found.\n");
				printf("Monitoring Status: %s\n", kmNet_monitor(5356) ? "True" : "False");
			}
			else
			{
				printf("Failed To Initialise Kmbox NET.\n");
			}
		}
		else
		{
			printf("Kmbox NET Config File Not Valid.\n");
		}
	}
	else
	{
		printf("Kmbox NET Config File Not Found.\n");
	}

	globals::vaPeb = mem.GetProcessInformation().win.vaPEB;
	globals::base = mem.GetBaseDaddy("cod.exe");

	std::thread(CachePointers).detach();
	std::thread(CachePlayers).detach();
	std::thread(AimbotLoop).detach();

	CreateOverlay();

	while (!GetAsyncKeyState(VK_END))
	{
		StartOverlay();

		DrawMenu();
		DrawCheat();

		EndOverlay();
	}

	if (cfg::kmnet_connected) kmNet_monitor(0);
	globals::done = true;

	return 0;
}