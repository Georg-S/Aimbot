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

	offsets = Offsets::get_instance();
	if (!offsets) 
	{
		std::cout << "Loading offsets failed, check offsets file" << std::endl;
	}

	if (!mem_manager.attach_to_process(windowname.c_str()))
	{
		std::cout << "Couldn't find process: Quiting " << std::endl;
		std::cout << "Make Sure CS-GO is open " << std::endl;
		return false;
	}

	client_dll_address = mem_manager.get_module_address(client_dll_name.c_str());
	return client_dll_address != NULL;
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
}

