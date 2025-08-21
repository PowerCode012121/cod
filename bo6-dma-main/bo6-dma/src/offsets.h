#pragma once

namespace offsets // https://github.com/c-metaphor/White-Ops-6/
{
	constexpr auto ref_def_ptr = 0xC908D60; //
	constexpr auto name_array = 0xCA7C628; // 
	constexpr auto name_array_pos = 0x3038;
	constexpr auto name_array_size = 0xC8;
	constexpr auto loot_ptr = 0xE2C1D08;
	constexpr auto camera_base = 0xC5A57A0; //
	constexpr auto local_index = 0xA8FA8; //
	constexpr auto local_index_pos = 0x394; //
	constexpr auto game_mode = 0xB544188; //
	constexpr auto weapon_definitions = 0xC7D15C0; //
	constexpr auto distribute = 0x9790328; //
	constexpr auto visible_bit = 0x447AC; //

	namespace player
	{
		constexpr auto size = 0x2560; //
		constexpr auto valid = 0x22DC; //
		constexpr auto pos = 0x248; //
		constexpr auto team = 0x130B; //
		constexpr auto stance = 0x15F4; //
		constexpr auto weapon_index = 0xC6A; //
		constexpr auto dead_1 = 0x15400; //
		constexpr auto dead_2 = 0x214; //
		constexpr auto dead_3 = 0x11C;//	
	}

	namespace bone
	{
		constexpr auto bone_base = 0x1570E8; //
		constexpr auto size = 0x1B8;
		constexpr auto offset = 0xD8;
	}
}