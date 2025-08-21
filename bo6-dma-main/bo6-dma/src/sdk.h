#pragma once

enum EEntityType : __int16
{
    PLAYER = 0x01,                          // Player entity
    NPC = 0x10,                             // Non-player character (NPC)
    ZOMBIE = NPC,                           // Zombie entity , also NPC but renamed for clarity
};

enum EEntityStance : __int16
{
    STAND = 0,                           // Standing stance
    CROUCH = 1,                          // Crouching stance
    PRONE = 2,                           // Prone position
    DOWNED = 3
};

struct Player
{
	uintptr_t
		ptr,
		refdef_ptr,
		pos_ptr,
		cam_ptr,
		bone_ptr;

	Vector3
		pos,
		cam,
        head_pos,
        head3d;

	Vector2
		w2s;

    uint16_t
        bone_index_cache,
        bone_index;

	int index;
    int health;
	uint8_t teamid;
    uint8_t dead_1;
	uint8_t dead_2;
    __int16 stance;
	bool valid; 
    bool visible;
	int distance;
	float rot;
	char name[0x24];

    bool UpdateFromList(std::vector<Player> list)
    {
        for (int i = 0; i < list.size(); ++i)
        {
            if (list[i].index == index)
            {
                *this = list[i];
                return true;
            }
        }

        return false;
    }
};

struct ref_def_t {
    int32_t x;
    int32_t y;
    int32_t width;
    int32_t height;
    Vector2 tan_half_fov;
    char pad1[8];  // 8-byte padding
    char pad2[4];  // 4-byte padding
    Vector3 axis[3];
};

struct client_bits_t
{
    uint32_t data[7];
};

Vector3 GetCamera(uintptr_t camera_base)
{
    if (!camera_base) return Vector3();

    struct Matrix4x4 {
        float _11, _12, _13, _14;
        float _21, _22, _23, _24;
        float _31, _32, _33, _34;
        float _41, _42, _43, _44;
    };

    auto vm = mem.Read<Matrix4x4>(camera_base + 0x10C);

    return Vector3{ vm._14, vm._24, vm._34 }; // or read matrix 0x10C
}

bool world_to_screen(Vector3 world_loc, Vector2& out, Vector3 camera_pos, ref_def_t ref_def)
{
    auto local = world_loc - camera_pos;

    auto matricies = ref_def.axis;

    auto trans = Vector3{
        local.Dot(matricies[1]),
        local.Dot(matricies[2]),
        local.Dot(matricies[0])
    };

    // Check trans.z
    if (trans.z < 0.01f) 
        return false;

    // Screen Coordinates Calculation
    out.x = ((float)ref_def.width / 2.0) * (1.0 - (trans.x / ref_def.tan_half_fov.x / trans.z));
    out.y = ((float)ref_def.height / 2.0) * (1.0 - (trans.y / ref_def.tan_half_fov.y / trans.z));

    // Bounds Check
    if (out.x < 1 || out.y < 1 || (out.x > ref_def.width) || (out.y > ref_def.height)) 
        return false;

    return true;
}

Player GetLocalPlayer(std::vector<Player> players, int index)
{
    for (int i = 0; i < players.size(); ++i)
    {
        if (players[i].index == index)
            return players[i];
    }
    
    return Player();
}

bool IsVisible(client_bits_t visible_bits, uint32_t index) // visible_ptr = client_info + visible_bit
{
    auto bitmask = 0x80000000 >> (index & 0x1F);
    return visible_bits.data[index >> 5] & bitmask;
}

bool InScreen(ref_def_t ref_def, Vector2 pixel)
{
    return pixel.x > 0 && pixel.x < ref_def.width && pixel.y > 0 && pixel.y < ref_def.height;
}