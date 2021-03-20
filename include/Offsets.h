#pragma once
#include <memory>
#include "FileReader.h"
#include <wtypes.h>

class Offsets 
{
public:
	static bool load_offsets_from_file();

	//Will be read from the Offset file
	static DWORD local_player_offset;
	static DWORD crosshair_offset;
	static DWORD entity_list_start_offset;
	static DWORD player_health_offset;
	static DWORD team_offset;
	static DWORD entity_listelement_size;
	static DWORD view_angle_offset;
	static DWORD position;

private:
	static bool initialized_succesful;
	static constexpr int HEX = 16;
};

