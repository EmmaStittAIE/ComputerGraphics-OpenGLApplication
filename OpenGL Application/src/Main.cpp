#include "GraphicsDef.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <string>
#include <vector>

#include "Maths.h"
#include "Utils.h"
#include "ShaderProgram.h"
#include "Mesh.h"

struct Resolution
{
	int width;
	int height;

	float aspect;
};

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

	ShaderProgram basicShader("shaders/Basic.vert", "shaders/Basic.frag");

	basicShader.UseShaderProgram();

	glClearColor(1, 0.7f, 0.8f, 1);

	// ew texture loading
	GLuint textureID;
	int width, height, n;

	unsigned char* imageData = stbi_load("textures/texture.png", &width, &height, &n, 0);

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(imageData);

	

	Mesh cubeMesh
	{
		{  // Position					 Normal						Colour						  UV
			{ Vec3(-1.0f, -1.0f,  1.0f), Vec3( 0.0f,  0.0f,  1.0f), Vec4(1.0f, 0.0f, 0.0f, 1.0f), Vec2( 0.0f,  0.0f) },		// Front
			{ Vec3(-1.0f,  1.0f,  1.0f), Vec3( 0.0f,  0.0f,  1.0f), Vec4(0.0f, 1.0f, 0.0f, 1.0f), Vec2( 0.0f,  1.0f) },
			{ Vec3( 1.0f, -1.0f,  1.0f), Vec3( 0.0f,  0.0f,  1.0f), Vec4(0.0f, 0.0f, 1.0f, 1.0f), Vec2( 1.0f,  0.0f) },
			{ Vec3( 1.0f,  1.0f,  1.0f), Vec3( 0.0f,  0.0f,  1.0f), Vec4(1.0f, 0.0f, 0.0f, 1.0f), Vec2( 1.0f,  1.0f) },
			{ Vec3(-1.0f,  1.0f,  1.0f), Vec3( 0.0f,  0.0f,  1.0f), Vec4(0.0f, 1.0f, 0.0f, 1.0f), Vec2( 0.0f,  1.0f) },
			{ Vec3( 1.0f, -1.0f,  1.0f), Vec3( 0.0f,  0.0f,  1.0f), Vec4(0.0f, 0.0f, 1.0f, 1.0f), Vec2( 1.0f,  0.0f) },

			{ Vec3(-1.0f, -1.0f, -1.0f), Vec3( 0.0f,  0.0f, -1.0f), Vec4(0.0f, 1.0f, 1.0f, 1.0f), Vec2( 0.0f,  0.0f) },		// Back
			{ Vec3(-1.0f,  1.0f, -1.0f), Vec3( 0.0f,  0.0f, -1.0f), Vec4(0.0f, 1.0f, 1.0f, 1.0f), Vec2( 0.0f,  1.0f) },
			{ Vec3( 1.0f, -1.0f, -1.0f), Vec3( 0.0f,  0.0f, -1.0f), Vec4(0.0f, 1.0f, 1.0f, 1.0f), Vec2( 1.0f,  0.0f) },
			{ Vec3( 1.0f,  1.0f, -1.0f), Vec3( 0.0f,  0.0f, -1.0f), Vec4(0.0f, 1.0f, 1.0f, 1.0f), Vec2( 1.0f,  1.0f) },
			{ Vec3(-1.0f,  1.0f, -1.0f), Vec3( 0.0f,  0.0f, -1.0f), Vec4(0.0f, 1.0f, 1.0f, 1.0f), Vec2( 0.0f,  1.0f) },
			{ Vec3( 1.0f, -1.0f, -1.0f), Vec3( 0.0f,  0.0f, -1.0f), Vec4(0.0f, 1.0f, 1.0f, 1.0f), Vec2( 1.0f,  0.0f) },

			{ Vec3( 1.0f, -1.0f, -1.0f), Vec3( 1.0f,  0.0f,  0.0f), Vec4(0.0f, 1.0f, 0.0f, 1.0f), Vec2( 0.0f,  0.0f) },		// Right
			{ Vec3( 1.0f,  1.0f, -1.0f), Vec3( 1.0f,  0.0f,  0.0f), Vec4(0.0f, 1.0f, 0.0f, 1.0f), Vec2( 0.0f,  1.0f) },
			{ Vec3( 1.0f, -1.0f,  1.0f), Vec3( 1.0f,  0.0f,  0.0f), Vec4(0.0f, 1.0f, 0.0f, 1.0f), Vec2( 1.0f,  0.0f) },
			{ Vec3( 1.0f,  1.0f,  1.0f), Vec3( 1.0f,  0.0f,  0.0f), Vec4(0.0f, 1.0f, 0.0f, 1.0f), Vec2( 1.0f,  1.0f) },
			{ Vec3( 1.0f,  1.0f, -1.0f), Vec3( 1.0f,  0.0f,  0.0f), Vec4(0.0f, 1.0f, 0.0f, 1.0f), Vec2( 0.0f,  1.0f) },
			{ Vec3( 1.0f, -1.0f,  1.0f), Vec3( 1.0f,  0.0f,  0.0f), Vec4(0.0f, 1.0f, 0.0f, 1.0f), Vec2( 1.0f,  0.0f) },

			{ Vec3(-1.0f, -1.0f, -1.0f), Vec3(-1.0f,  0.0f,  0.0f), Vec4(1.0f, 0.0f, 1.0f, 1.0f), Vec2( 0.0f,  0.0f) },		// Left
			{ Vec3(-1.0f,  1.0f, -1.0f), Vec3(-1.0f,  0.0f,  0.0f), Vec4(1.0f, 0.0f, 1.0f, 1.0f), Vec2( 0.0f,  1.0f) },
			{ Vec3(-1.0f, -1.0f,  1.0f), Vec3(-1.0f,  0.0f,  0.0f), Vec4(1.0f, 0.0f, 1.0f, 1.0f), Vec2( 1.0f,  0.0f) },
			{ Vec3(-1.0f,  1.0f,  1.0f), Vec3(-1.0f,  0.0f,  0.0f), Vec4(1.0f, 0.0f, 1.0f, 1.0f), Vec2( 1.0f,  1.0f) },
			{ Vec3(-1.0f,  1.0f, -1.0f), Vec3(-1.0f,  0.0f,  0.0f), Vec4(1.0f, 0.0f, 1.0f, 1.0f), Vec2( 0.0f,  1.0f) },
			{ Vec3(-1.0f, -1.0f,  1.0f), Vec3(-1.0f,  0.0f,  0.0f), Vec4(1.0f, 0.0f, 1.0f, 1.0f), Vec2( 1.0f,  0.0f) },

			{ Vec3(-1.0f,  1.0f, -1.0f), Vec3( 0.0f,  1.0f,  0.0f), Vec4(0.0f, 0.0f, 1.0f, 1.0f), Vec2( 0.0f,  0.0f) },		// Top
			{ Vec3(-1.0f,  1.0f,  1.0f), Vec3( 0.0f,  1.0f,  0.0f), Vec4(0.0f, 0.0f, 1.0f, 1.0f), Vec2( 0.0f,  1.0f) },
			{ Vec3( 1.0f,  1.0f, -1.0f), Vec3( 0.0f,  1.0f,  0.0f), Vec4(0.0f, 0.0f, 1.0f, 1.0f), Vec2( 1.0f,  0.0f) },
			{ Vec3( 1.0f,  1.0f,  1.0f), Vec3( 0.0f,  1.0f,  0.0f), Vec4(0.0f, 0.0f, 1.0f, 1.0f), Vec2( 1.0f,  1.0f) },
			{ Vec3(-1.0f,  1.0f,  1.0f), Vec3( 0.0f,  1.0f,  0.0f), Vec4(0.0f, 0.0f, 1.0f, 1.0f), Vec2( 0.0f,  1.0f) },
			{ Vec3( 1.0f,  1.0f, -1.0f), Vec3( 0.0f,  1.0f,  0.0f), Vec4(0.0f, 0.0f, 1.0f, 1.0f), Vec2( 1.0f,  0.0f) },

			{ Vec3(-1.0f, -1.0f, -1.0f), Vec3( 0.0f, -1.0f,  0.0f), Vec4(1.0f, 1.0f, 0.0f, 1.0f), Vec2( 0.0f,  0.0f) },		// Bottom
			{ Vec3(-1.0f, -1.0f,  1.0f), Vec3( 0.0f, -1.0f,  0.0f), Vec4(1.0f, 1.0f, 0.0f, 1.0f), Vec2( 0.0f,  1.0f) },
			{ Vec3( 1.0f, -1.0f, -1.0f), Vec3( 0.0f, -1.0f,  0.0f), Vec4(1.0f, 1.0f, 0.0f, 1.0f), Vec2( 1.0f,  0.0f) },
			{ Vec3( 1.0f, -1.0f,  1.0f), Vec3( 0.0f, -1.0f,  0.0f), Vec4(1.0f, 1.0f, 0.0f, 1.0f), Vec2( 1.0f,  1.0f) },
			{ Vec3(-1.0f, -1.0f,  1.0f), Vec3( 0.0f, -1.0f,  0.0f), Vec4(1.0f, 1.0f, 0.0f, 1.0f), Vec2( 0.0f,  1.0f) },
			{ Vec3( 1.0f, -1.0f, -1.0f), Vec3( 0.0f, -1.0f,  0.0f), Vec4(1.0f, 1.0f, 0.0f, 1.0f), Vec2( 1.0f,  0.0f) }
		}
	};

	Vec3 lightDirection = glm::normalize(Vec3{ 1, -1, 1 });
	basicShader.SetUniformVec3("lightDirection", lightDirection.x, lightDirection.y, lightDirection.z);
	
	GLuint vertexBufferID = 0;
	glGenBuffers(1, &vertexBufferID);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * cubeMesh.vertices.size(), cubeMesh.vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	glEnable(GL_DEPTH_TEST);

	// Program loop
	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Render start
		glViewport(0, 0, res.width, res.height);

		// (original matrix, angle to rotate by, axis to rotate around)
		Mat4 modelMat = glm::rotate(Mat4(1.0f), (float)glfwGetTime(), { 0.0f, 1.0f, 0.0f });
		// (camera pos, target pos, up vector)
		//Mat4 viewMat = glm::lookAt(Vec3(5, ((int)(glfwGetTime() * 2) % 10) - 4, 5), Vec3(0, 0, 0), Vec3(0, 1, 0));
		Mat4 viewMat = glm::lookAt(Vec3(0, 3, 5), Vec3(0, 0, 0), Vec3(0, 1, 0));
		// (fov on the y axis, window aspect ratio, near clipping plane, far clipping plane)
		Mat4 projectionMat = glm::perspective(PI / 2.0f, res.aspect, 0.1f, 50.f);

		Mat4 mvpMat = projectionMat * viewMat * modelMat;
		basicShader.SetUniformMat4("mvpMat", &mvpMat[0][0]);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureID);
		basicShader.SetUniformInt("textureSampler", 0);

		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, sizeof(float) * 12, 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, sizeof(float) * 12, (void*)(3 * sizeof(float)));
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_TRUE, sizeof(float) * 12, (void*)(6 * sizeof(float)));
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_TRUE, sizeof(float) * 12, (void*)(10 * sizeof(float)));

		glDrawArrays(GL_TRIANGLES, 0, cubeMesh.vertices.size());

		// Render end

		glfwSwapBuffers(window);

		// Check events (input, etc.)
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}