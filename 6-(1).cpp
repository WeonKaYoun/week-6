#include<iostream>
#include<string>
using namespace std;

template <typename T>
void print(const T& i)
{
	std::cout << i << std::endl;
}


int main(void)
{
	print(1);
	print(2.345f);
	print("Hello World");
}