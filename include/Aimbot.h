#pragma once
#include <iostream>
#include "MemoryManager.h"
#include "FileReader.h"
#include "ToggleButton.h"
#include "Offsets.h"

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

	DWORD client_dll_address;
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