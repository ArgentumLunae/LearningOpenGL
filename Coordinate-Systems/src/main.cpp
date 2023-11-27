#include <iostream>
#include "../hdr/glad.h"
#include "../hdr/stb_image.h"
#include <GLFW/glfw3.h>
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../hdr/Shader.hpp"

#define WIN_WIDTH 640
#define WIN_HEIGHT 480

float	mixValue = 0.2;
float	fov = 45.0f;

float	deltaTime = 0.0f;
float	lastFrame = 0.0f;

glm::vec3	cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
float		yaw = -90.0f;
float		pitch = 0.0f;

bool		firstMouse = true;
float	lastX = WIN_WIDTH / 2;
float	lastY = WIN_HEIGHT / 2;

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

void processInput(GLFWwindow *window)
{
	const float cameraSpeed = 5.0f * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
		return ;
	}
	if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
	{
		GLint polyMode;

		glGetIntegerv(GL_POLYGON_MODE, &polyMode);
		if (polyMode == GL_FILL)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	if (glfwGetKey(window, GLFW_KEY_W))
		cameraPos += glm::vec3(cameraSpeed * cameraFront.x, 0.0, cameraSpeed * cameraFront.z); // for anf FPS like camera, remove translation along the y axis in forward and backward movement
	if (glfwGetKey(window, GLFW_KEY_A))
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_S))
		cameraPos -= glm::vec3(cameraSpeed * cameraFront.x, 0.0, cameraSpeed * cameraFront.z);
	if (glfwGetKey(window, GLFW_KEY_D))
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		mixValue += 0.01f;
		if (mixValue >= 1.0f)
			mixValue = 1.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		mixValue -= 0.01f;
		if (mixValue <= 0.0f)
			mixValue = 0.0f;
	}
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float	xoffset = xpos - lastX;
	float	yoffset = ypos - lastY;
	lastX = xpos;
	lastY = ypos;

	const float	sensistivity = 0.01f;
	xoffset *= sensistivity;
	yoffset *= sensistivity;

	yaw	+= xoffset;
	pitch -= yoffset;
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3	direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(direction);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	fov -= (float)yoffset;
	if (fov < 1.0f)
		fov = 1.0f;
	if (fov > 45.0f)
		fov = 45.0f;
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
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// Setup Triangle
	Shader 		myShader("../shaders/vertex/3Dbasics.vs", "../shaders/fragment/basic.fs");	// formerly "unsigned int shaderProgram;"

	float triangle[] = {
		// location			// colour			// texture coords
	-0.5f, -0.5f, -0.5f,	1.0f, 0.0f, 0.0f,	0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,	0.0f, 1.0f, 0.0f,	1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,	1.0f, 1.0f, 0.0f,	0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,	1.0f, 0.0f, 0.0f,	0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,	1.0f, 0.0f, 0.0f,	0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,	0.0f, 1.0f, 0.0f,	1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,	0.0f, 0.0f, 1.0f,	1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,	0.0f, 0.0f, 1.0f,	1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 0.0f,	0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,	1.0f, 0.0f, 0.0f,	0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,	1.0f, 0.0f, 0.0f,	1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,	0.0f, 1.0f, 0.0f,	1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,	1.0f, 1.0f, 0.0f,	0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,	1.0f, 0.0f, 0.0f,	1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,	1.0f, 0.0f, 0.0f,	1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,	0.0f, 1.0f, 0.0f,	1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,	0.0f, 0.0f, 1.0f,	0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,	1.0f, 1.0f, 0.0f,	0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,	1.0f, 0.0f, 0.0f,	1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,	1.0f, 0.0f, 0.0f,	0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,	0.0f, 1.0f, 0.0f,	1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 1.0f,	1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,	0.0f, 0.0f, 1.0f,	1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,	1.0f, 1.0f, 0.0f,	0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,	1.0f, 0.0f, 0.0f,	0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,	1.0f, 0.0f, 0.0f,	0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,	0.0f, 1.0f, 0.0f,	1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,	0.0f, 0.0f, 1.0f,	1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,	0.0f, 0.0f, 1.0f,	1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 0.0f,	0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,	1.0f, 0.0f, 0.0f,	0.0f, 1.0f
	};
	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};
	unsigned int VBO, VAO, EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// location attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// setup texture
	float borderColor[] = { 0.0f, 1.0f, 1.0f, 1.0f };
	unsigned int texture1, texture2;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	stbi_set_flip_vertically_on_load(true);

	int width, height, nrChannels;
	unsigned char *data = stbi_load("../textures/container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cerr << "Failed to load texture." << std::endl;
	stbi_image_free(data);
	
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(true);
	data = stbi_load("../textures/awesomeface.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cerr << "Failed to load texture." << std::endl;
	stbi_image_free(data);

	myShader.use();
	myShader.setInt("texture1", 0);
	myShader.setInt("texture2", 1);

	int modelLoc = glGetUniformLocation(myShader.ID, "model");
	int viewLoc = glGetUniformLocation(myShader.ID, "view");
	int projectionLoc = glGetUniformLocation(myShader.ID, "projection");


	glm::vec3 cubePositions[] = {
		glm::vec3(  0.0f,  0.0f,  0.0f ),
		glm::vec3(  2.0f,  5.0f, -15.0f ),
		glm::vec3( -1.5f, -2.2f, -2.5f ),
		glm::vec3( -3.8f, -2.0f, -12.3f ),
		glm::vec3(  2.4f, -0.4f, -3.5f ),
		glm::vec3( -1.7f,  3.0f, -7.5f ),
		glm::vec3(  1.3f, -2.0f, -2.5f ),
		glm::vec3(  1.5f,  2.0f, -2.5f ),
		glm::vec3(  1.5f,  0.2f, -1.5f ),
		glm::vec3( -1.3f,  1.0f, -1.5f )
	};

	// render loop

	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		processInput(window);

		glClearColor(0.25, 0.15, 0.75, 1.0);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		myShader.setFloat("mixValue", mixValue);

		myShader.use();

		glBindVertexArray(VAO);

		glm::mat4 projection = glm::mat4(1.0f);
		glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

		projection = glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 100.0f);

		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		for (int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			float angle = 20.0f * i;

			model = glm::translate(model, cubePositions[i]);
			model = glm::rotate(model, glm::radians(angle), glm::vec3(0.5f, 1.0f, 0.0f));
			if (!(i % 3))
				model = glm::rotate(model, glm::radians((float)glfwGetTime() * 50.0f), glm::vec3(0.5f, 1.0f, 0.5f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;
}
