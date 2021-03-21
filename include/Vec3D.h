#pragma once
#include <math.h>

template <typename T>
class Vec3D
{
public:
	T calc_abs() const
	{
		return sqrt(x * x + y * y + z * z);
	}

	void print() const
	{
		std::cout << "X: " << x << " Y: " << y << " Z: " << z << std::endl;
	}

	T x;
	T y;
	T z;
};

template <typename T>
Vec3D<T> operator+(const Vec3D<T>& left, const Vec3D<T>& right)
{
	Vec3D<T> result;
	result.x = left.x + right.x;
	result.y = left.y + right.y;
	result.z = left.z + right.z;

	return result;
}

template <typename T>
Vec3D<T> operator-(const Vec3D<T>& left, const Vec3D<T>& right)
{
	Vec3D<T> result;
	result.x = left.x - right.x;
	result.y = left.y - right.y;
	result.z = left.z - right.z;

	return result;
}