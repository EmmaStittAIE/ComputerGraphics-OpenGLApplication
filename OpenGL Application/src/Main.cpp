#define GLFW_INCLUDE_NONE

#include <string>
#include <vector>

#include "glfw3.h"
#include "glad.h"
#include "Maths.h"
#include "Utility.h"

int main(void)
{
	GLFWwindow* window;

	// Init GLFW
	if (!glfwInit())
	{
		// TODO: error reporting
		return -1;
	}

	// Create window
	std::string windowTitle = Utils::LoadFileToString("WindowTitles.txt");

	window = glfwCreateWindow(800, 600, windowTitle.c_str(), nullptr, nullptr);
	if (!window)
	{
		// TODO: error reporting
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	// Init GLAD
	if (!gladLoadGL())
	{
		// TODO: error reporting
		glfwTerminate();
		return -1;
	}

	glClearColor(1, 0.7f, 0.8f, 1);

	std::vector<float> verts
	{
		0.5, 1, 0,
		0.5, -1, 0,
		1, 0, 0,

		-0.5, 1, 0,
		-0.5, -1, 0,
		-1, 0, 0
	};
	
	GLuint vertexBufferID = 0;
	glGenBuffers(1, &vertexBufferID);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * verts.size(), verts.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glEnableVertexAttribArray(0);

	// Program loop
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		// Render start
		


		// Render end

		glfwSwapBuffers(window);

		// Check events (input, etc.)
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}