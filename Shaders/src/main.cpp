#include <iostream>
#include "../hdr/glad.h"
#include <GLFW/glfw3.h>
#include <cmath>

#include "../hdr/Shader.hpp"

#define WIN_WIDTH 640
#define WIN_HEIGHT 360

const char	*g_vertexShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"layout (location = 1) in vec3 aColor;\n"
	"out vec4 ourColor;\n"
	"void main()\n"
	"{\n"
	"gl_Position = vec4(aPos, 1.0);\n"
	"ourColor = vec4(aColor, 1.0);\n"
	"}\n";

const char *g_fragmentShaderSource = "#version 330 core\n"
	"out vec4 fragColor;\n"
	"in vec4 ourColor;\n"
	// "uniform vec4 ourColor;\n"
	"void main()\n"
	"{\n"
	// "fragColor = vertexColor;\n"
	"fragColor = ourColor;\n"
	"}\n";

GLFWwindow *setUpWindow(void)
{
	GLFWwindow *window;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "Window1", NULL, NULL);
	if (!window)
		return (NULL);
	
	glfwMakeContextCurrent(window);
	return window;
}

int 	setUpGlad(void)
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Couldn't Load OpenGL." << std::endl;
		glfwTerminate();
		return -1;
	}
	return 0;
}

void framebufferSizeCallback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// unsigned int setupShaderProgram(void)
// {
// 	unsigned int	vertexShader, fragmentShader, shaderProgram;
// 	int 			success;
// 	char			infoLog[512];

// 	// setting up the vertexShader
// 	vertexShader = glCreateShader(GL_VERTEX_SHADER);
// 	glShaderSource(vertexShader, 1, &g_vertexShaderSource, NULL);
// 	glCompileShader(vertexShader);
// 	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
// 	if (!success)
// 	{
// 		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
// 		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
// 	}

// 	// setting up the fragmentShader
// 	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
// 	glShaderSource(fragmentShader, 1, &g_fragmentShaderSource, NULL);
// 	glCompileShader(fragmentShader);
// 	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
// 	if (!success)
// 	{
// 		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
// 		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILURE\n" << infoLog << std::endl;
// 	}

// 	// setting up the shader profile
// 	shaderProgram = glCreateProgram();
// 	glAttachShader(shaderProgram, vertexShader);
// 	glAttachShader(shaderProgram, fragmentShader);
// 	glLinkProgram(shaderProgram);
// 	glGetShaderiv(fragmentShader, GL_LINK_STATUS, &success);
// 	if (!success)
// 	{
// 		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
// 		std::cerr << "ERROR::PROGRAM::SHADER::LINKING_FAILED\n" << infoLog << std::endl;
// 	}
// 	glUseProgram(shaderProgram);
// 	return shaderProgram;
// }

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int main(int, char**)
{
	GLFWwindow *window;

	if (!glfwInit())
		return -1;
	window = setUpWindow();
	if (!window)
	{
		std::cerr << "Failed to create GLFE window." << std::endl;
		glfwTerminate();
		return -1;
	}
	if (setUpGlad())
		return -1;
	
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	// shaderProgram = setupShaderProgram();

	// Setup Triangle
	Shader 		myShader("../shaders/vertex/basic.vs", "../shaders/fragment/basic.fs");	// formerly "unsigned int shaderProgram;"
	float triangle[] = {
		// location			// colour
		 0.0f,  0.5f, 0.0f,	1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.0f,	0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f, 0.0f,	0.0f, 0.0f, 1.0f
	};
	unsigned int indices[] = {
		0, 1, 2
	};
	unsigned int VBO, VAO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);

	// location attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// render loop
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.25, 0.15, 0.75, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
	
		myShader.use();
		myShader.setFloat("horizontalOffset", 0.3f);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return 0;
}
