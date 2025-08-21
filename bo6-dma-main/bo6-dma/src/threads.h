#pragma once

void CachePointers()
{
	while (!globals::done)
	{
		globals::in_game = mem.Read<int>(globals::base + offsets::game_mode);
		if (globals::in_game < 2) continue;

		Sleep(15000);

		globals::client_info = decrypt_client_info();
		if (!globals::client_info) continue;

		globals::client_base = decrypt_client_base(globals::client_info);
		if (!globals::client_base) continue;

		globals::bone_base = decrypt_bone_base();
		if (!globals::bone_base) continue;

		globals::refdef_ptr = retrieve_ref_def();
		if (!globals::refdef_ptr) continue;

		globals::name_ptr = mem.Read<uintptr_t>(globals::base + offsets::name_array);
		if (!globals::name_ptr) continue;
		globals::name_ptr += offsets::name_array_pos;

		globals::local_cam = mem.Read<uintptr_t>(globals::base + offsets::camera_base);
		if (!globals::local_cam) continue;

		while (globals::in_game > 1)
		{
			Sleep(200);

			globals::in_game = mem.Read<int>(globals::base + offsets::game_mode);
			globals::local_index_ptr = mem.Read<uintptr_t>(globals::client_info + offsets::local_index);

			std::vector<Player> temp_list(globals::in_game);

			auto handle = mem.CreateScatterHandle();

			for (int i = 0; i < temp_list.size(); ++i)
			{
				temp_list[i].index = i;
				temp_list[i].ptr = globals::client_base + i * offsets::player::size;

				mem.AddScatterReadRequest(handle, temp_list[i].ptr + offsets::player::valid, &temp_list[i].valid, sizeof(bool));
				mem.AddScatterReadRequest(handle, temp_list[i].ptr + offsets::player::team, &temp_list[i].teamid, sizeof(uint8_t));
				mem.AddScatterReadRequest(handle, temp_list[i].ptr + offsets::player::pos, &temp_list[i].pos_ptr, sizeof(uintptr_t));
				mem.AddScatterReadRequest(handle, temp_list[i].ptr + offsets::player::dead_1, &temp_list[i].dead_1, sizeof(uint8_t));
				mem.AddScatterReadRequest(handle, temp_list[i].ptr + offsets::player::dead_2, &temp_list[i].dead_2, sizeof(uint8_t));
				mem.AddScatterReadRequest(handle, temp_list[i].ptr + offsets::player::stance, &temp_list[i].stance, sizeof(__int16));
			}
			mem.ExecuteReadScatter(handle);

			globals::localplayer = GetLocalPlayer(temp_list, mem.Read<int>(globals::local_index_ptr + offsets::local_index_pos));

			for (int i = 0; i < temp_list.size(); ++i)
			{
				mem.AddScatterReadRequest(handle, globals::name_ptr + offsets::name_array_size * temp_list[i].index + 0x4, &temp_list[i].name, sizeof(Player::name));
				mem.AddScatterReadRequest(handle, globals::name_ptr + offsets::name_array_size * temp_list[i].index + 0x84, &temp_list[i].health, sizeof(int));
			}
			mem.ExecuteReadScatter(handle);
			globals::players_stage_1 = temp_list;
		}
	}
}

void CachePlayers()
{
	Sleep(1200);
	while (!globals::done)
	{
		globals::ref_def = mem.Read<ref_def_t>(globals::refdef_ptr);
		globals::cam_pos = GetCamera(globals::local_cam);
		globals::bone_vec_origin = mem.Read<Vector3>(globals::client_info + offsets::bone::bone_base);
		globals::visible_bits = mem.Read<client_bits_t>(globals::client_info + offsets::visible_bit);

		std::vector<Player> temp_list = globals::players_stage_1;

		auto handle = mem.CreateScatterHandle();

		for (int i = 0; i < temp_list.size(); ++i)
		{
			mem.AddScatterReadRequest(handle, temp_list[i].pos_ptr + 0x50, &temp_list[i].pos, sizeof(Vector3));
			mem.AddScatterReadRequest(handle, temp_list[i].pos_ptr + 0x68, &temp_list[i].rot, sizeof(float));
		}
		mem.ExecuteReadScatter(handle);
		
		for (int i = 0; i < temp_list.size(); ++i)
		{
			temp_list[i].bone_index = get_bone_index(temp_list[i].index);
		}


		for (int i = 0; i < temp_list.size(); ++i)
			mem.AddScatterReadRequest(handle, globals::bone_base + temp_list[i].bone_index * offsets::bone::size + offsets::bone::offset, &temp_list[i].bone_ptr, sizeof(uint64_t));
		mem.ExecuteReadScatter(handle);

		for (int i = 0; i < temp_list.size(); ++i)
			mem.AddScatterReadRequest(handle, temp_list[i].bone_ptr + 7 * 0x20 + 0x10, &temp_list[i].head_pos, sizeof(Vector3));
		mem.ExecuteReadScatter(handle);

		for (int i = 0; i < temp_list.size(); ++i)
		{
			temp_list[i].head3d = temp_list[i].head_pos + globals::bone_vec_origin;
		}

		mem.CloseScatterHandle(handle);
		globals::players_stage_2 = temp_list;
	}
}

uintptr_t decrypt_client_base(uintptr_t client_info);