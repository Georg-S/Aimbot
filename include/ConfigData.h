#pragma once
#include <string>

struct ConfigData 
{
	std::string client_dll_name;
	std::string engine_dll_name;
	std::string  windowname;
	int delay;
	DWORD trigger_button;
};