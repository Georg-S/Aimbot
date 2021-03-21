#include "Aimbot.h"

Aimbot::Aimbot() 
{
	mem_manager = MemoryManager();
	button = ToggleButton();
}

bool Aimbot::init() 
{
	if (!load_config())
	{
		std::cout << "Loading config failed, check config file" << std::endl;
		return false;
	}

	if (!Offsets::load_offsets_from_file()) 
	{
		std::cout << "Loading offsets failed, check offsets file" << std::endl;
		return false;
	}

	if (!mem_manager.attach_to_process(config.windowname.c_str()))
	{
		std::cout << "Couldn't find process: Quiting " << std::endl;
		std::cout << "Make Sure CS-GO is open " << std::endl;
		return false;
	}

	client_dll_address = mem_manager.get_module_address(config.client_dll_name.c_str());
	engine_address = mem_manager.get_module_address(config.engine_dll_name.c_str());
	return client_dll_address != NULL || engine_address != NULL;
}

bool Aimbot::load_config()
{
	static constexpr int DEC = 10;
	static constexpr int HEX = 16;
	
	config.windowname = FileReader::read_value_of_string_in_file("config.txt", "windowName");
	config.client_dll_name = FileReader::read_value_of_string_in_file("config.txt", "client Dll Name");
	config.engine_dll_name = FileReader::read_value_of_string_in_file("config.txt", "engine Dll Name");
	config.delay = stol(FileReader::read_value_of_string_in_file("config.txt", "delay"), NULL, DEC);
	config.trigger_button = stol(FileReader::read_value_of_string_in_file("config.txt", "triggerButton"), NULL, HEX);

	if (config.windowname == "" || config.client_dll_name == "" || config.trigger_button == 0)
		return false;

	button.set_toggle_button(config.trigger_button);

	return true;
}

void Aimbot::run()
{
	while (true) 
	{
		button.update();
		if (button.is_on()) 
		{
			update_aim_logic();
		}
	}
}


void Aimbot::update_aim_logic()
{
	update_game_data();
}

void Aimbot::update_game_data()
{
	DWORD player_address = mem_manager.read_memory<DWORD>(client_dll_address + Offsets::local_player_offset);
	DWORD engine_client_state = mem_manager.read_memory<DWORD>(engine_address + Offsets::clientState);

	update_controlled_player(player_address, engine_client_state);
	update_other_players(player_address, engine_client_state);
	Vec3D<float> closest_enemy_head_bone = get_closest_enemy_head_bone();
	Vec2D<float> new_view_vec = calc_vec_aim_to_head(closest_enemy_head_bone);
	set_view_vec(engine_client_state, new_view_vec);
}

void Aimbot::update_controlled_player(DWORD player_address, DWORD engine_client_state_address)
{
	this->player_view_vec = mem_manager.read_memory<Vec2D<float>>(engine_client_state_address + Offsets::client_state_view_angle);
	this->player_health = mem_manager.read_memory<int>(player_address + Offsets::player_health_offset);
	this->player_team = mem_manager.read_memory<int>(player_address + Offsets::team_offset);
	this->player_head_bone = get_head_bone(player_address);
}

void Aimbot::update_other_players(DWORD player_address, DWORD engine_client_state_address)
{
	int max_players = mem_manager.read_memory<int>(engine_client_state_address + Offsets::client_state_max_players);

	other_players.clear();
	for (int i = 0; i < max_players; i++) 
	{
		DWORD entity_address = mem_manager.read_memory<DWORD>(client_dll_address + Offsets::entity_list_start_offset 
			+ Offsets::entity_listelement_size * i);

		if (!entity_address || entity_address == player_address)
			continue;

		Entity ent;
		ent.head_bone_pos = get_head_bone(entity_address);
		ent.health = mem_manager.read_memory<DWORD>(entity_address + Offsets::player_health_offset);
		ent.team = mem_manager.read_memory<int>(entity_address + Offsets::team_offset);
		other_players.push_back(ent);
	}
}

void Aimbot::debug_print_memory(DWORD address, int rows, int columns)
{
	system("CLS");
	for (int row = 0; row < rows; row++)
	{
		for (int column = 0; column < columns; column++) 
		{
			DWORD value = mem_manager.read_memory<int>(address);
			address += sizeof(int);
			print_4_byte_hex(value);
			std::cout << " ";
		}
		std::cout << std::endl;
	}
}

void Aimbot::print_4_byte_hex(DWORD address)
{
	printf_s("0x%08x", address);
}

Vec3D<float> Aimbot::get_head_bone(DWORD entity)
{
	//Bone matrix is a 3 row 4 column matrix  3 * 4 * 4 = hex 30
	constexpr DWORD head_bone_index = 0x8;
	constexpr DWORD matrix_size = 0x30;
	Vec3D<float> pos;

	DWORD bones_address = mem_manager.read_memory<DWORD>(entity + Offsets::bone_matrix);
	pos.x = mem_manager.read_memory<float>(bones_address + matrix_size * head_bone_index + 0x0C); //0C,1c,2c because we want the right column of the matrix
	pos.y = mem_manager.read_memory<float>(bones_address + matrix_size * head_bone_index + 0x1C);
	pos.z = mem_manager.read_memory<float>(bones_address + matrix_size * head_bone_index + 0x2C);

	return pos;
}

Vec3D<float> Aimbot::get_closest_enemy_head_bone()
{
	Vec3D<float> closest_vec;
	float closest_distance = FLT_MAX;
	for (int i = 0; i < this->other_players.size(); i++) 
	{
		Vec3D<float> buf = this->player_head_bone - other_players[i].head_bone_pos;
		float distance = buf.calc_abs();

		if (distance <= closest_distance) 
		{
			closest_distance = distance;
			closest_vec = other_players[i].head_bone_pos;
		}
	}

	return closest_vec;
}

Vec2D<float> Aimbot::calc_vec_aim_to_head(const Vec3D<float>& enemy_head)
{
	return Vec2D<float>();
}

void Aimbot::set_view_vec(DWORD engine_client_state_address, const Vec2D<float>& vec)
{
	mem_manager.write_memory<Vec2D<float>>(engine_client_state_address + Offsets::client_state_view_angle, vec);
}

