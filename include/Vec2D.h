#pragma once
template <typename T>
class Vec2D 
{
public:
	T x;
	T y;

	void print() 
	{
		std::cout << "X: " << x << " Y: " << y << std::endl;
	}
};