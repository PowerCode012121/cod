#pragma once
#include "offsets.h"

struct Memory;
extern Memory mem;


namespace globals
{
	bool done = false;
	int in_game = 0;
	uintptr_t
		base,
		vaPeb,
		client_info,
		client_base,
		bone_base,
		refdef_ptr,
		name_ptr,
		local_cam;
	Vector3
		cam_pos,
		bone_vec_origin;
	ref_def_t
		ref_def;
	client_bits_t
		visible_bits;
	Player
		localplayer;
	uintptr_t
		local_index_ptr;
	std::vector<Player>
		players_stage_1,
		players_stage_2;
}

namespace cfg
{
	bool debug = false;
	bool player_list = false;

	bool aimbot = false;
	bool vis_check = false;
	float fov = 30.f;
	bool show_fov = false;
	int smoothing_method = 0;
	float smoothing = 2.5f;
	float speed = 15.f;

	bool kmnet_connected = false;
	static char ip[128] = "";
	static char port[128] = "";
	static char uuid[128] = "";

	bool box_esp = true;
	bool name_esp = false;
	bool distance_esp = false;
	bool team_esp = false;
	bool drop_shadow = false;
	bool vsync = false;
	bool health = false;
	bool health_text = false;

	int max_dist = 300;
}