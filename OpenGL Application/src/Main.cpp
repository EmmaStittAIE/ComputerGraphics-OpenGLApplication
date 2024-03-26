#include "GraphicsDef.h"

#include <string>
#include <vector>

#include "Maths.h"
#include "Utils.h"
#include "ShaderProgram.h"
#include "Mesh.h"
#include "Texture.h"
#include "Logger.h"

#include "Nodes.h"

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
		Logger::Log({ "GLFW failed to initialise." }, LogType::Error);
		return -1;
	}
	
#ifdef _DEBUG
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create window
	std::string windowTitle = Utils::LoadFileToString("WindowTitles.txt");
	window = glfwCreateWindow(res.width, res.height, windowTitle.c_str(), nullptr, nullptr);
	if (!window)
	{
		Logger::Log({ "Window \"", glfwGetWindowTitle(window), "\" was not created successfully."}, LogType::Error);
		glfwTerminate();
		return -1;
	}

	glfwSetWindowUserPointer(window, &res);

	glfwSetFramebufferSizeCallback(window, OnWindowResize);

	glfwMakeContextCurrent(window);

	// Init GLAD
	if (!gladLoadGL())
	{
		Logger::Log({ "GLAD failed to initialise." }, LogType::Error);
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

	Texture soulSpearDiffuse("textures/Soul Spear/soulspear_diffuse.tga");
	Texture soulSpearNormal("textures/Soul Spear/soulspear_normal.tga");
	Texture soulSpearSpecular("textures/Soul Spear/soulspear_specular.tga");

	// Direction light is travelling in
	Vec3 lightDirection = glm::normalize(Vec3{ 1, 0, -1 });
	basicShader.SetUniformVec3("lightDirection", lightDirection.x, lightDirection.y, lightDirection.z);
	
	Camera camera;
	camera.SetPosition(0, 0, -5);

	Mesh cubeMesh;
	cubeMesh.ConstructCubePrimitive();

	Mesh spearMesh;
	spearMesh.ConstructFromFile("models/soulspear.obj");

	MeshRenderer cube1;
	cube1.m_mesh = &cubeMesh;
	cube1.m_diffuse = &coolTexture;
	cube1.SetPosition(0, 2, 0);

	MeshRenderer spear;
	spear.m_mesh = &spearMesh;
	spear.m_diffuse = &soulSpearDiffuse;
	spear.m_normal = &soulSpearNormal;
	spear.m_specular = &soulSpearSpecular;
	spear.SetPosition(0, 0, 0);

	glEnable(GL_DEPTH_TEST);

	// Program loop
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Render start

		glViewport(0, 0, res.width, res.height);

		// (camera pos, target pos, up vector)
		//Mat4 viewMatCamera = camera.GetViewMatrix();
		Mat4 viewMat = glm::lookAt(Vec3(0, 2, 3), Vec3(0, 2, 0), Vec3(0, 1, 0));
		// (fov on the y axis, window aspect ratio, near clipping plane, far clipping plane)
		Mat4 projectionMat = glm::perspective(PI / 2.0f, res.aspect, 0.1f, 50.f);

		cube1.SetEulerRotation(0, (float)glfwGetTime(), 0);
		spear.SetEulerRotation(0, (float)glfwGetTime(), 0);

		//cube1.Draw(&basicShader, projectionMat * viewMat);
		spear.Draw(&basicShader, projectionMat * viewMat);

		// Render end

		glfwSwapBuffers(window);

		// Check events (input, etc.)
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}