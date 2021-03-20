#pragma once
#include <iostream>
#include <Aimbot.h>

int main()
{
    Aimbot aimbot = Aimbot();

    if (aimbot.init())
        std::cout << "Init sucessful" << std::endl;

    return 0;
}
