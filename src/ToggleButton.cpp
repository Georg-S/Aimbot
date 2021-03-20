#include "ToggleButton.h"

ToggleButton::ToggleButton(int button)
{
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
				std::cout << "Triggerbot toggled  ON" << std::endl;
			else
				std::cout << "Triggerbot toggled  OFF" << std::endl;
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
