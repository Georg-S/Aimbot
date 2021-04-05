#pragma once
#include <Windows.h>
#include <iostream>
#include <string>

class ToggleButton
{
public:
	ToggleButton(const std::string& button_name = "Button", int button = o_key_code);
	void update();
	void set_toggle_button(int button);
	bool is_on() const;

private:
	std::string button_name;
	int button = 0;
	bool triggered = false;
	bool print_when_toggled = true;
	static constexpr int o_key_code = 0x4F;
};

