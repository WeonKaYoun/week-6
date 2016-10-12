#include<iostream>
#include<vector>
using namespace std;

template<class T>
class Vector2D
{
public:
	T _x, _y;

};

int main(void)
{
	Vector2D<int> my_vector;
	my_vector._x = 1;
	my_vector._y = 2;
	Vector2D<float> my_vector2;
	my_vector2._x = 3.1f;
	my_vector2._y = 4.1f;
	Vector2D<double> my_vector3;
	my_vector3._x = 1.234;
	my_vector3._y = 5.678;

	cout << my_vector._x << endl;
	cout << my_vector._y << endl;
	cout << my_vector2._x << endl;
	cout << my_vector2._y << endl;
	cout << my_vector3._x << endl;
	cout << my_vector3._y << endl;

}