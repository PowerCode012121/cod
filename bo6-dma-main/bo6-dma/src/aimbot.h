#pragma once

Player GetClosestPlayer()
{
    Player closest_player = Player();
    float closest_dist = FLT_MAX;

    auto temp_list = globals::players_stage_2;
    for (int i = 0; i < temp_list.size(); ++i)
    {
        auto player = temp_list[i];

        if (!player.valid) continue;
        if (player.pos.IsZero()) continue;
        if (!player.pos.Valid()) continue;
        if (player.dead_1 > 0) continue;
        if (player.dead_2 > 0) continue;
        if (player.teamid == globals::localplayer.teamid) continue;
        if (!player.bone_ptr) continue;
        if (player.health < 1) continue;

        Vector3 bone_3d = player.head3d;
        Vector2 bone_2d;

        if (bone_3d.IsZero()) continue;
        if (!bone_3d.Valid()) continue;
        if (!world_to_screen(bone_3d, bone_2d, globals::cam_pos, globals::ref_def)) continue;

        float dist_3d = globals::cam_pos.DistTo(bone_3d) * 0.0254;
        if (dist_3d > 200.f) continue;

        float dist = Vector2(globals::ref_def.width / 2.f, globals::ref_def.height / 2.f).Dist(bone_2d);
        if (dist < closest_dist && dist < cfg::fov * 3)
        {
            closest_player = player;
            closest_dist = dist;
        }
    }

    return closest_player;
}

Player closest_player = Player();

void AimbotLoop()
{
	while (!globals::done)
	{
		Sleep(1);

		if (!closest_player.ptr) closest_player = GetClosestPlayer();

		if (cfg::kmnet_connected && !kmNet_monitor_mouse_right())
		{
			closest_player = Player();
			continue;
		}
		else if (cfg::kmnet_connected && kmNet_monitor_mouse_right())
		{
            Vector3 bone_3d = closest_player.head3d;
            Vector2 bone_2d;

			if (!closest_player.UpdateFromList(globals::players_stage_2)) continue;
			if (!closest_player.ptr || !closest_player.name || !closest_player.valid || !closest_player.teamid || !closest_player.bone_ptr || !world_to_screen(bone_3d, bone_2d, globals::cam_pos, globals::ref_def))
			{
				closest_player = Player();
				continue;
			}

			if (cfg::aimbot)
            {
                if (!IsVisible(globals::visible_bits, closest_player.index) && cfg::vis_check) continue;

				Vector2 delta = bone_2d - Vector2(globals::ref_def.width / 2.f, globals::ref_def.height / 2.f);
                delta /= 2.f;

                float dist = Vector2(globals::ref_def.width / 2.f, globals::ref_def.height / 2.f).Dist(bone_2d);
                if (dist >= cfg::fov * 3.f) continue;

                float dist_3d = globals::cam_pos.DistTo(bone_3d) * 0.0254;
                if (dist_3d > 200.f) continue;

                if (cfg::smoothing_method == 0)
                {
                    delta /= cfg::smoothing;
                }
                else
                {
                    float length = delta.Length();
                    if (length > 0.01f)
                    {
                        delta /= length;

                        delta *= cfg::speed;
                    }
                }

                //printf("Aiming at %s at pixel (%.2f, %.2f)\n", closest_player.name, bone_2d.x, bone_2d.y);
				kmNet_mouse_move(delta.x, delta.y);
			}
		}
	}
}