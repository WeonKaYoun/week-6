#include <GLFW/glfw3.h>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include "math.h"
#include <iostream>
#include <vector>
using namespace std;

const int width = 900;
const int height = 600;

float* pixels = new float[width*height * 3];

void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
{
	pixels[(i + width* j) * 3 + 0] = red;
	pixels[(i + width* j) * 3 + 1] = green;
	pixels[(i + width* j) * 3 + 2] = blue;
}


void drawLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	if (i0 != i1)
	{
		for (int i = i0; i <= i1; i++)
		{
			const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

			drawPixel(i, j, red, green, blue);
		}
	}
	else
	{
		for (int k = j0; k < j1; k++)
			drawPixel(i0, k, 0.0f, 0.0f, 0.0f);
	}
}


void drawCircle(const int& i, const int& j, const int& r, const float& red, const float& green, const float& blue)
{
	for (int a = i - r; a < i + r; a++)
	{
		for (int b = j - r; b < j + r; b++)
		{
			//원의 방정식 이용
			int c = ((a - i)*(a - i) + (b - j)*(b - j) - (r - 1)*(r - 1));
			int d = ((a - i)*(a - i) + (b - j)*(b - j) - r * r);

			if (c > 0 && d < 0)
				drawPixel(a, b, red, green, blue);
		}
	}


}


void drawOnPixelBuffer()
{
	std::fill_n(pixels, width*height * 3, 1.0f);	// white background


	const int i = rand() % width, j = rand() % height;
	drawPixel(i, j, 0.0f, 0.0f, 0.0f);

}


class Box // NO PARENT
{
public:
	void draw()
	{
		drawLine(100, 450, 150, 450, 0.0f, 0.0f, 0.0f);
		drawLine(100, 500, 150, 500, 0.0f, 0.0f, 0.0f);
		drawLine(100, 450, 100, 500, 0.0f, 0.0f, 0.0f);
		drawLine(150, 450, 150, 500, 0.0f, 0.0f, 0.0f);
	}

};


class Circle // NO PARENT
{
public:
	// some variables
	void draw()
	{
		drawCircle(530, 470, 27, 0.0f, 0.0f, 0.0f);
	}
};


class GeometricObjectInterface
{
public:
	virtual void draw()
	{

	}
};


template <class T>
class GeometricObject : public GeometricObjectInterface
{
public:
	void draw()
	{
		T t;
		t.draw();
	}

};


int main()
{
	GLFWwindow* window;
	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glClearColor(1, 1, 1, 1); // while background
	drawOnPixelBuffer();

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		std::vector<GeometricObjectInterface*> obj_list;

		obj_list.push_back(new GeometricObject<Box>);
		obj_list.push_back(new GeometricObject<Circle>);
		for (auto itr : obj_list)
			itr->draw();

		glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();


	}

	glfwTerminate();

	delete[] pixels; // or you may reuse pixels array 

	return 0;
}