#pragma once
#include <iostream>
#include <Aimbot.h>

int main()
{
    Aimbot aimbot = Aimbot();

    if (aimbot.init())
        aimbot.run();

    return 0;
}
