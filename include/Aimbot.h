#pragma once
#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <cmath>
#include "Vec3D.h"
#include "MemoryManager.h"
#include "FileReader.h"
#include "ToggleButton.h"
#include "Offsets.h"
#include "Vec2D.h"
#include "ConfigData.h"
#include "Entity.h"

class Aimbot 
{
public:
	Aimbot();
	bool init();
	void run();

private:
	bool load_config();
	void update_aim_logic();
	void update_game_data();
	void update_controlled_player(DWORD player_address, DWORD engine_client_state_address);
	void update_other_players(DWORD player_address, DWORD engine_client_state_address);
	void debug_print_memory(DWORD address, int rows, int columns);
	void print_4_byte_hex(DWORD address);
	Vec3D<float> get_head_bone(DWORD entity);
	Vec3D<float> get_closest_enemy_head_bone();
	Vec2D<float> calc_view_vec_aim_to_head(const Vec3D<float>& enemy_head);
	void set_view_vec(DWORD engine_client_state_address, const Vec2D<float>& vec);

	DWORD client_dll_address;
	DWORD engine_address;
	MemoryManager mem_manager;
	ToggleButton button;
	Offsets* offsets;
	ConfigData config;
	Vec3D<float> player_head_bone;
	Vec2D<float> player_view_vec;
	int player_health;
	int player_team;
	std::vector<Entity> other_players;
};