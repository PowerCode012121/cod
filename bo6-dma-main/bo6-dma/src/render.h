#pragma once

bool open = true;
bool page = 0;
const char* smoothing_methods[2] = { "Exponential", "Constant" };

void DrawMenu()
{
	if (GetAsyncKeyState(VK_INSERT) & 1)
		open = !open;

	if (!open)
		return;

	ImGui::SetNextWindowPos(ImVec2(100, 100), ImGuiCond_Once);
	ImGui::SetNextWindowSize(ImVec2(500, 800), ImGuiCond_Once);
	ImGui::Begin("Cheat", nullptr);

	ImGui::BeginTabBar("#1");

	if (ImGui::BeginTabItem("Aim"))
	{
		ImGui::Checkbox("Enable", &cfg::aimbot);
		ImGui::Checkbox("Visible Check", &cfg::vis_check);
		ImGui::SliderFloat("FOV", &cfg::fov, 1.f, 300.f, "%.1fpx");
		ImGui::Checkbox("Show FOV", &cfg::show_fov);
		ImGui::Combo("Smoothing Mode", &cfg::smoothing_method, smoothing_methods, IM_ARRAYSIZE(smoothing_methods));
		if (cfg::smoothing_method == 0)
			ImGui::SliderFloat("Smooth", &cfg::smoothing, 1.f, 20.f, "%.1f%%");
		else
			ImGui::SliderFloat("Speed", &cfg::speed, 1.f, 20.f, "%.1fpx");

		ImGui::EndTabItem();
	}
	
	//ImGui::End();

	/*ImGui::SetNextWindowPos(ImVec2(320, 100));
	ImGui::SetNextWindowSize(ImVec2(200, 400));
	ImGui::Begin("ESP", nullptr);*/
	if (ImGui::BeginTabItem("ESP"))
	{
		ImGui::Checkbox("Box", &cfg::box_esp);
		ImGui::Checkbox("Name", &cfg::name_esp);
		ImGui::Checkbox("Distance", &cfg::distance_esp);
		ImGui::Checkbox("Team", &cfg::team_esp);
		ImGui::SliderInt("Max Distance", &cfg::max_dist, 1, 2000, "%im");
		ImGui::Checkbox("Health", &cfg::health);
		ImGui::Checkbox("Health Text", &cfg::health_text);

		ImGui::EndTabItem();
	}
	
	// ImGui::End();

	/*ImGui::SetNextWindowPos(ImVec2(540, 100));
	ImGui::SetNextWindowSize(ImVec2(200, 400));
	ImGui::Begin("Misc", nullptr);*/
	if (ImGui::BeginTabItem("Misc"))
	{
		ImGui::Checkbox("Text Drop Shadow", &cfg::drop_shadow);
		ImGui::Checkbox("VSync", &cfg::vsync);
		ImGui::Separator();
		ImGui::Text("Kmbox NET:");
		ImGui::InputText("IP", cfg::ip, sizeof(cfg::ip));
		ImGui::InputText("Port", cfg::port, sizeof(cfg::port));
		ImGui::InputText("UUID", cfg::uuid, sizeof(cfg::uuid));
		if (ImGui::Button("Initalise"))
		{
			cfg::kmnet_connected = kmNet_init(cfg::ip, cfg::port, cfg::uuid) == 0;
			if (cfg::kmnet_connected)
			{
				std::ofstream cfg_file("kmbox.txt");
				if (cfg_file.is_open())
				{
					cfg_file << cfg::ip << std::endl;
					cfg_file << cfg::port << std::endl;
					cfg_file << cfg::uuid << std::endl;
					cfg_file.close();
				}
				printf("Monitoring Status: %s\n", kmNet_monitor(5356) ? "True" : "False");
			}
		}
		if (cfg::kmnet_connected)
		{
			ImGui::Text("Kmbox NET Connected.");
		}
		if (ImGui::Button("Test Move Mouse"))
			kmNet_mouse_move(10, 10);

		ImGui::Checkbox("Debug", &cfg::debug);
		ImGui::Checkbox("Player List", &cfg::player_list);

		if (cfg::debug)
		{
			ImGui::Separator();

			ImGui::Text("globals::base -> %llx", globals::base);
			ImGui::Text("globals::vaPeb -> %llx", globals::vaPeb);
			ImGui::Text("globals::in_game -> %i", globals::in_game);
			ImGui::Text("globals::client_info -> %llx", globals::client_info);
			ImGui::Text("globals::client_base -> %llx", globals::client_base);
			ImGui::Text("globals::bone_base -> %llx", globals::bone_base);
			ImGui::Text("globals::refdef_ptr -> %llx", globals::refdef_ptr);
			ImGui::Text("globals::name_ptr -> %llx", globals::name_ptr);
			ImGui::Text("globals::local_cam -> %llx", globals::local_cam);

			ImGui::Separator();

			ImGui::Text("globals::cam_pos -> (%.2f, %.2f, %.2f)", globals::cam_pos.x, globals::cam_pos.y, globals::cam_pos.z);
			ImGui::Text("globals::bone_vec_origin -> (%.2f, %.2f, %.2f)", globals::bone_vec_origin.x, globals::bone_vec_origin.y, globals::bone_vec_origin.z);

			ImGui::Separator();

			ImGui::Text("globals::localplayer.ptr -> %llx", globals::localplayer.ptr);
			ImGui::Text("globals::localplayer.valid -> %s", globals::localplayer.valid ? "True" : "False");
			ImGui::Text("globals::localplayer.teamid -> %i", globals::localplayer.teamid);
		}

		ImGui::EndTabItem();
	}
	
	ImGui::EndTabBar();

	ImGui::End();

	if (!cfg::player_list) return;

	ImGui::SetNextWindowPos(ImVec2(700, 100), ImGuiCond_Once);
	ImGui::SetNextWindowSize(ImVec2(800, 800), ImGuiCond_Once);
	ImGui::Begin("Player List");
	auto temp_list = globals::players_stage_2;
	for (int i = 0; i < temp_list.size(); ++i)
	{
		ImGui::Text("%s #%i |", temp_list[i].name, temp_list[i].index);
		ImGui::SameLine();
		ImGui::Text("bone_ptr -> %llx |", temp_list[i].bone_ptr);
		ImGui::SameLine();
		ImGui::Text("bone_index -> %i |", temp_list[i].bone_index);
		ImGui::SameLine();
		ImGui::Text("bone_index_cache -> %i", temp_list[i].bone_index_cache);
	}
	ImGui::End();
}

void DrawCheat()
{
	Text(Vector2(10, 10), ImColor(255, 255, 255), "Zytec COD DMA");

	if (globals::ref_def.width == 0 || globals::ref_def.height == 0) return;

	if (cfg::show_fov)
		ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(globals::ref_def.width / 2.f, globals::ref_def.height / 2.f), cfg::fov * 3.f, ImColor(255, 255, 255));

	auto temp_list = globals::players_stage_2;
	for (int i = 0; i < temp_list.size(); ++i)
	{
		auto player = temp_list[i];

		if (!player.valid) continue;
		if (!player.pos.Valid()) continue;
		if (player.dead_1 > 0) continue;
		if (player.dead_2 > 0) continue;
		if (player.health < 1) continue;
		if (player.teamid == globals::localplayer.teamid) continue;

		Vector3 head_3d = player.pos;
		if (player.stance == EEntityStance::STAND)
			head_3d.z += 60;
		else if (player.stance == EEntityStance::CROUCH)
			head_3d.z += 40;
		else
			head_3d.z += 20;
		Vector3 feet_3d = player.pos;

		if (globals::cam_pos.DistTo(head_3d) * 0.0254 > cfg::max_dist) continue;

		Vector2 head_2d, feet_2d;

		bool head_in_screen = world_to_screen(head_3d, head_2d, globals::cam_pos, globals::ref_def);
		bool feet_in_screen = world_to_screen(feet_3d, feet_2d, globals::cam_pos, globals::ref_def);

		if (!head_in_screen && !feet_in_screen) continue;

		if (player.ptr == closest_player.ptr)
			ImGui::GetBackgroundDrawList()->AddLine(ImVec2(globals::ref_def.width / 2.f, globals::ref_def.height / 2.f), ImVec2(head_2d.x, head_2d.y), ImColor(255, 255, 255));

		float height = feet_2d.y - head_2d.y;
		float width = height / 3.f;

		int top_offset = 15, bottom_offset = 4, side_offset = 0;

		ImColor colour;
		if (IsVisible(globals::visible_bits, player.index) && player.bone_ptr && player.bone_index)
			colour = ImColor(0, 255, 0);
		else
			colour = ImColor(255, 0, 0);

		if (cfg::name_esp)
		{
			Text(Vector2(head_2d.x - ImGui::CalcTextSize(player.name).x / 2, head_2d.y - top_offset), ImColor(255, 255, 255), player.name);
			top_offset += 12;
		}

		if (cfg::box_esp)
			Box(Vector2(head_2d.x - width / 2.f, head_2d.y), Vector2(width, height), colour);

		if (cfg::distance_esp)
		{
			int distance = static_cast<int>(globals::cam_pos.DistTo(head_3d) * 0.0254);
			std::string text = "[" + std::to_string(distance) + "m]";
			Text(Vector2(head_2d.x - ImGui::CalcTextSize(text.c_str()).x / 2, feet_2d.y + bottom_offset), ImColor(255, 255, 255), text.c_str());
			bottom_offset += 12;
		}

		if (cfg::health_text)
		{
			std::string text = std::to_string(player.health) + " HP";
			Text(Vector2(head_2d.x + width / 2 + 3, head_2d.y + side_offset), ImColor(255, 255, 255), text.c_str());
			side_offset += 10;
		}

		if (player.stance == EEntityStance::DOWNED)
		{
			std::string text = "KNOCKED";
			Text(Vector2(head_2d.x + width / 2 + 3, head_2d.y + side_offset), ImColor(255, 255, 255), text.c_str());
			side_offset += 10;
		}

		if (cfg::team_esp)
		{
			int team_id = static_cast<int>(player.teamid);
			std::string text = "Team " + std::to_string(team_id);
			Text(Vector2(head_2d.x + width / 2 + 3, head_2d.y + side_offset), ImColor(255, 255, 255), text.c_str());
			side_offset += 10;
		}

		if (cfg::health)
		{
			int health = player.health;
			ImColor col = ImColor(255 - health * (255 / 127), health * (255 / 127), 0);

			float height_adjusted = height * health / 127;

			Vector2 pos = Vector2(head_2d.x - width / 2 - 4, feet_2d.y - height_adjusted);
			Vector2 size = Vector2(2, height_adjusted);

			FilledBox(pos, size, col);
		}
	}
}