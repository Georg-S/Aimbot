#pragma once
#include <iostream>
#include "Vec3D.h"
#include "MemoryManager.h"
#include "FileReader.h"
#include "ToggleButton.h"
#include "Offsets.h"
#include "Vec2D.h"

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
	void debug_print_memory(DWORD address, int rows, int columns);
	void print_4_byte_hex(DWORD address);

	DWORD client_dll_address;
	DWORD engine_address;
	MemoryManager mem_manager;
	static constexpr int DEC = 10;
	static constexpr int HEX = 16;

	//Will be read from the Config file
	std::string client_dll_name;
	std::string  windowname;
	int delay = 0;
	ToggleButton button;
	Offsets* offsets;
};