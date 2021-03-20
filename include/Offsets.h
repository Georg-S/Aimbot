#pragma once
#include <memory>
#include "FileReader.h"
#include <wtypes.h>

class Offsets 
{
public:
	~Offsets() {};

	static Offsets* get_instance();

	//Will be read from the Offset file
	DWORD client_dll_address;
	DWORD local_player_offset;
	DWORD crosshair_offset;
	DWORD entity_list_start_offset;
	DWORD player_health_offset;
	DWORD team_offset;
	DWORD entity_listelement_size;

private:
	Offsets();
	Offsets(const Offsets&);

	bool load_offsets();
	static std::unique_ptr<Offsets> instance;
	static bool initialized_succesful;
	static constexpr int HEX = 16;
};

