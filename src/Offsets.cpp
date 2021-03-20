#include "Offsets.h"

std::unique_ptr<Offsets> Offsets::instance = nullptr;
bool Offsets::initialized_succesful = false;

Offsets* Offsets::get_instance()
{
	if (!instance || !initialized_succesful) 
	{
		auto buf = new Offsets();
		instance = std::unique_ptr<Offsets>(buf);
	}

	if (initialized_succesful)
		return instance.get();

	return nullptr;
}

Offsets::Offsets() 
{
	try 
	{
		initialized_succesful = load_offsets();
	}
	catch (const std::exception& e)
	{
		initialized_succesful = false;
	}
}

bool Offsets::load_offsets()
{
	local_player_offset = stol(FileReader::read_value_of_string_in_file("memoryOffsets.txt", "localPlayer"), NULL, HEX);
	crosshair_offset = stol(FileReader::read_value_of_string_in_file("memoryOffsets.txt", "crosshairOffset"), NULL, HEX);
	entity_list_start_offset = stol(FileReader::read_value_of_string_in_file("memoryOffsets.txt", "entityBase"), NULL, HEX);
	player_health_offset = stol(FileReader::read_value_of_string_in_file("memoryOffsets.txt", "PlayerHealth"), NULL, HEX);
	team_offset = stol(FileReader::read_value_of_string_in_file("memoryOffsets.txt", "teamOffset"), NULL, HEX);
	entity_listelement_size = stol(FileReader::read_value_of_string_in_file("memoryOffsets.txt", "EntLoopDist"), NULL, HEX);

	if (local_player_offset == 0 || crosshair_offset == 0 ||
		player_health_offset == 0 || team_offset == 0 || entity_listelement_size == 0)
		return false;

	return true;
}
