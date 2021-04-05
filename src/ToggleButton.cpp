#include "ToggleButton.h"

ToggleButton::ToggleButton(const std::string& button_name, int button)
{
	this->button_name = button_name;
	this->button = button;
}

void ToggleButton::update()
{
	static bool buf_toggle = true;

	int buff = GetAsyncKeyState(button);
	if (buff == -32768 && buf_toggle)
	{
		buf_toggle = false;
		triggered = !triggered;
		if (print_when_toggled) 
		{
			if (triggered)
				std::cout << this->button_name <<" toggled  ON" << std::endl;
			else
				std::cout << this->button_name << " toggled  OFF" << std::endl;
		}
	}
	if (buff == 0)
		buf_toggle = true;
}

bool ToggleButton::is_on() const
{
	return triggered;
}

void ToggleButton::set_toggle_button(int button)
{
	this->button = button;
}
