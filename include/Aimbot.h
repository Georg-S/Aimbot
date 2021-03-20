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
private:
	bool load_config();

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