#include "GraphicsDef.h"

#include <string>
#include <vector>

#include "Maths.h"
#include "Utils.h"
#include "ShaderProgram.h"
#include "Mesh.h"
#include "Texture.h"

#include "TransformNode.h"
#include "MeshRenderer.h"

#include <iostream>

struct Resolution
{
	int width;
	int height;

	float aspect;
};

void APIENTRY GLDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	std::cout << "Source: " << source << std::endl
			  << "Type: " << type << std::endl
			  << "ID: " << id << std::endl
			  << "Severity: " << severity << std::endl
			  << "Message: " << message << std::endl
			  << "---" << std::endl;
}

void OnWindowResize(GLFWwindow* window, int width, int height)
{
	void* userPointer = glfwGetWindowUserPointer(window);

	Resolution* resolutionPointer = (Resolution*)userPointer;

	resolutionPointer->width = width;
	resolutionPointer->height = height;

	resolutionPointer->aspect = width / (float)height;
}

int main(void)
{
	GLFWwindow* window;

	Resolution res
	{
		1280,
		720,
		1280.0f / 720.0f
	};

	// Init GLFW
	if (!glfwInit())
	{
		// TODO: error reporting
		return -1;
	}
	
#ifdef _DEBUG
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create window
	std::string windowTitle = Utils::LoadFileToString("WindowTitles.txt");
	window = glfwCreateWindow(res.width, res.height, windowTitle.c_str(), nullptr, nullptr);
	if (!window)
	{
		// TODO: error reporting
		glfwTerminate();
		return -1;
	}

	glfwSetWindowUserPointer(window, &res);

	glfwSetFramebufferSizeCallback(window, OnWindowResize);

	glfwMakeContextCurrent(window);

	// Init GLAD
	if (!gladLoadGL())
	{
		// TODO: error reporting
		glfwTerminate();
		return -1;
	}

#ifdef _DEBUG
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(GLDebugCallback, nullptr);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);
#endif

	ShaderProgram basicShader("shaders/Basic.vert", "shaders/Basic.frag");

	basicShader.UseShaderProgram();

	glClearColor(1, 0.7f, 0.8f, 1);

	Texture coolTexture("textures/texture.png");

	Vec3 lightDirection = glm::normalize(Vec3{ 1, -1, 1 });
	basicShader.SetUniformVec3("lightDirection", lightDirection.x, lightDirection.y, lightDirection.z);
	
	Mesh cubeMesh;
	cubeMesh.ConstructCubePrimitive();
	//cubeMesh.ConstructFromFile();

	MeshRenderer cube1;
	cube1.m_mesh = &cubeMesh;
	cube1.m_texture = &coolTexture;
	cube1.SetPosition(-2, 0, 0);

	glEnable(GL_DEPTH_TEST);

	// Program loop
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Render start
		glViewport(0, 0, res.width, res.height);

		// (camera pos, target pos, up vector)
		//Mat4 viewMat = glm::lookAt(Vec3(5, ((int)(glfwGetTime() * 2) % 10) - 4, 5), Vec3(0, 0, 0), Vec3(0, 1, 0));
		Mat4 viewMat = glm::lookAt(Vec3(0, 3, 5), Vec3(0, 0, 0), Vec3(0, 1, 0));
		// (fov on the y axis, window aspect ratio, near clipping plane, far clipping plane)
		Mat4 projectionMat = glm::perspective(PI / 2.0f, res.aspect, 0.1f, 50.f);

		cube1.SetEulerRotation(0, (float)glfwGetTime(), 0);

		cube1.Draw(&basicShader, projectionMat * viewMat);

		// Render end

		glfwSwapBuffers(window);

		// Check events (input, etc.)
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}