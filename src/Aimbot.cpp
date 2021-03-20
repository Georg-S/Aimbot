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

	if (!mem_manager.attach_to_process(windowname.c_str()))
	{
		std::cout << "Couldn't find process: Quiting " << std::endl;
		std::cout << "Make Sure CS-GO is open " << std::endl;
		return false;
	}

	client_dll_address = mem_manager.get_module_address(client_dll_name.c_str());
	engine_address = mem_manager.get_module_address("engine.dll");
	return client_dll_address != NULL || engine_address != NULL;
}

bool Aimbot::load_config()
{
	windowname = FileReader::read_value_of_string_in_file("config.txt", "windowName");
	client_dll_name = FileReader::read_value_of_string_in_file("config.txt", "client Dll Name");
	delay = stol(FileReader::read_value_of_string_in_file("config.txt", "delay"), NULL, DEC);
	unsigned int trigger_button = stol(FileReader::read_value_of_string_in_file("config.txt", "triggerButton"), NULL, HEX);

	if (windowname == "" || client_dll_name == "" || trigger_button == 0)
		return false;

	button.set_toggle_button(trigger_button);

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
}

void Aimbot::update_game_data()
{
	auto player_address = mem_manager.read_memory<DWORD>(client_dll_address + Offsets::local_player_offset);
	auto player_health = mem_manager.read_memory<DWORD>(player_address + Offsets::player_health_offset);
	Vec3D<int> player_position = mem_manager.read_memory<Vec3D<int>>(player_address + Offsets::position);
	Vec2D<float> player_view_vec = mem_manager.read_memory<Vec2D<float>>(player_address + Offsets::position - 3 * sizeof(int));
}

void Aimbot::debug_print_memory(DWORD address, int rows, int columns)
{
	system("CLS");
	for (int row = 0; row < rows; row++)
	{
		for (int column = 0; column < columns; column++) 
		{
			int value = mem_manager.read_memory<int>(address);
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

