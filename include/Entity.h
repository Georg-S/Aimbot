#pragma once
#include "Vec3D.h"

struct Entity 
{
	Vec3D<float> head_bone_pos;
	int health;
	int team;
};