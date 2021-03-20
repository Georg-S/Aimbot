
template <typename T>
class Vec3D 
{
public:
	void print() 
	{
		std::cout << "X: " << x << " Y: " << y << " Z: " << z << std::endl;
	}

	T x;
	T y;
	T z;
};