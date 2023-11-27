#include <iostream>
#include "../hdr/glad.h"
#include "../hdr/stb_image.h"
#include <GLFW/glfw3.h>
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"

#include "../hdr/Shader.hpp"
#include "../hdr/Camera.hpp"

#define WIN_WIDTH 640
#define WIN_HEIGHT 480

float	mixValue = 0.2;
// float	fov = 45.0f;

float	deltaTime = 0.0f;
float	lastFrame = 0.0f;

// glm::vec3	cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
// glm::vec3	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
// glm::vec3	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
// glm::vec3	cameraRight = glm::normalize(glm::cross(cameraUp, cameraFront));
// float		yaw = -90.0f;
// float		pitch = 0.0f;

bool		firstMouse = true;

float const		playerHeight = 1.8f;
Camera cam = Camera(glm::vec3(0.0f, playerHeight, 0.0f));

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
		cam.moveForward(cameraSpeed);
		// cameraPos += glm::vec3(cameraSpeed * cameraFront.x, 0.0, cameraSpeed * cameraFront.z); // for anf FPS like camera, remove translation along the y axis in forward and backward movement
	if (glfwGetKey(window, GLFW_KEY_A))
		cam.strafeRight(cameraSpeed);
		// cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_S))
		cam.moveBack(cameraSpeed);
		// cameraPos -= glm::vec3(cameraSpeed * cameraFront.x, 0.0, cameraSpeed * cameraFront.z);
	if (glfwGetKey(window, GLFW_KEY_D))
		cam.strafeLeft(cameraSpeed);
		// cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_SPACE) && cam.getGrounded())
		cam.jump();
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
	static float lastX = xpos;
	static float lastY = ypos;

	float	xoffset = xpos - lastX;
	float	yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	const float	sensistivity = 0.01f;

	cam.updateYaw(xoffset * sensistivity);
	cam.updatePitch(yoffset * sensistivity);
	cam.updateDirection();
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	cam.updateFOV((float)yoffset);
}

void player_gravity(glm::vec3 const *ground, int const nrOfObjects)
{
	float			fallSpeed = cam.getVertSpeed();
	float			gravity = -0.1 * deltaTime;	//gravitational acceleration
	glm::vec3		playerPos = cam.getPos();

	std::cout << fallSpeed << std::endl;
	for (int i = 0; i < nrOfObjects; i++)
	{
		if (fallSpeed > 0.0f)
			break;
		glm::vec3 relativePos = playerPos - ground[i];
		if (!(relativePos.x > -0.55 && relativePos.x < 0.55 && relativePos.z > -0.55 && relativePos.z < 0.55))
			continue ;
		if ((playerPos.y - ground[i].y) < (playerHeight + 0.5) && (playerPos.y - ground[i].y) > (playerHeight - 0.5))
		{
			fallSpeed = 0;
			playerPos.y = ground[i].y + playerHeight;
			cam.setPos(playerPos);
			cam.setGrounded(true);
			cam.setVertSpeed(fallSpeed);
			return ;
		}
	}
	cam.setGrounded(false);
	fallSpeed += gravity;
	if (fallSpeed > (10 * deltaTime))
		fallSpeed == 10 * deltaTime;
	playerPos.y += fallSpeed;
	cam.setPos(playerPos);
	cam.setVertSpeed(fallSpeed);
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
	Shader 		myShader("../shaders/vertex/3Dbasics.vs", "../shaders/fragment/basic.fs");

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
	unsigned char *data = stbi_load("../textures/grass.png", &width, &height, &nrChannels, 0);
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
		glm::vec3( -4.0f,  0.0f, -4.0f ),
		glm::vec3( -4.0f,  0.0f, -3.0f ),
		glm::vec3( -4.0f,  0.0f, -2.0f ),
		glm::vec3( -4.0f,  0.0f, -1.0f ),
		glm::vec3( -4.0f,  0.0f,  0.0f ),
		glm::vec3( -4.0f,  0.0f,  1.0f ),
		glm::vec3( -4.0f,  0.0f,  2.0f ),
		glm::vec3( -4.0f,  0.0f,  3.0f ),
		glm::vec3( -4.0f,  0.0f,  4.0f ),

		glm::vec3( -3.0f,  0.0f, -4.0f ),
		glm::vec3( -3.0f,  0.0f, -3.0f ),
		glm::vec3( -3.0f,  0.0f, -2.0f ),
		glm::vec3( -3.0f,  0.0f, -1.0f ),
		glm::vec3( -3.0f,  0.0f,  0.0f ),
		glm::vec3( -3.0f,  0.0f,  1.0f ),
		glm::vec3( -3.0f,  0.0f,  2.0f ),
		glm::vec3( -3.0f,  0.0f,  3.0f ),
		glm::vec3( -3.0f,  0.0f,  4.0f ),

		glm::vec3( -2.0f,  0.0f, -4.0f ),
		glm::vec3( -2.0f,  0.0f, -3.0f ),
		glm::vec3( -2.0f,  0.0f, -2.0f ),
		glm::vec3( -2.0f,  0.0f, -1.0f ),
		glm::vec3( -2.0f,  0.0f,  0.0f ),
		glm::vec3( -2.0f,  0.0f,  1.0f ),
		glm::vec3( -2.0f,  0.0f,  2.0f ),
		glm::vec3( -2.0f,  0.0f,  3.0f ),
		glm::vec3( -2.0f,  0.0f,  4.0f ),

		glm::vec3( -1.0f,  0.0f, -4.0f ),
		glm::vec3( -1.0f,  0.0f, -3.0f ),
		glm::vec3( -1.0f,  0.0f, -2.0f ),
		glm::vec3( -1.0f,  0.0f, -1.0f ),
		glm::vec3( -1.0f,  0.0f,  0.0f ),
		glm::vec3( -1.0f,  0.0f,  1.0f ),
		glm::vec3( -1.0f,  0.0f,  2.0f ),
		glm::vec3( -1.0f,  0.0f,  3.0f ),
		glm::vec3( -1.0f,  0.0f,  4.0f ),

		glm::vec3(  0.0f,  0.0f, -4.0f ),
		glm::vec3(  0.0f,  0.0f, -3.0f ),
		glm::vec3(  0.0f,  0.0f, -2.0f ),
		glm::vec3(  0.0f,  0.0f, -1.0f ),
		glm::vec3(  0.0f,  0.0f,  0.0f ),
		glm::vec3(  0.0f,  0.0f,  1.0f ),
		glm::vec3(  0.0f,  0.0f,  2.0f ),
		glm::vec3(  0.0f,  0.0f,  3.0f ),
		glm::vec3(  0.0f,  0.0f,  4.0f ),

		glm::vec3(  1.0f,  0.0f, -4.0f ),
		glm::vec3(  1.0f,  0.0f, -3.0f ),
		glm::vec3(  1.0f,  0.0f, -2.0f ),
		glm::vec3(  1.0f,  0.0f, -1.0f ),
		glm::vec3(  1.0f,  0.0f,  0.0f ),
		glm::vec3(  1.0f,  0.0f,  1.0f ),
		glm::vec3(  1.0f,  0.0f,  2.0f ),
		glm::vec3(  1.0f,  0.0f,  3.0f ),
		glm::vec3(  1.0f,  0.0f,  4.0f ),

		glm::vec3(  2.0f,  0.0f, -4.0f ),
		glm::vec3(  2.0f,  0.0f, -3.0f ),
		glm::vec3(  2.0f,  0.0f, -2.0f ),
		glm::vec3(  2.0f,  1.0f, -1.0f ),
		glm::vec3(  2.0f,  0.0f,  0.0f ),
		glm::vec3(  2.0f,  0.0f,  1.0f ),
		glm::vec3(  2.0f,  0.0f,  2.0f ),
		glm::vec3(  2.0f,  0.0f,  3.0f ),
		glm::vec3(  2.0f,  0.0f,  4.0f ),

		glm::vec3(  3.0f,  0.0f, -4.0f ),
		glm::vec3(  3.0f,  0.0f, -3.0f ),
		glm::vec3(  3.0f,  0.0f, -2.0f ),
		glm::vec3(  3.0f,  0.0f, -1.0f ),
		glm::vec3(  3.0f,  0.0f,  0.0f ),
		glm::vec3(  3.0f,  0.0f,  1.0f ),
		glm::vec3(  3.0f,  0.0f,  2.0f ),
		glm::vec3(  3.0f,  0.0f,  3.0f ),
		glm::vec3(  3.0f,  0.0f,  4.0f ),

		glm::vec3(  4.0f,  0.0f, -4.0f ),
		glm::vec3(  4.0f,  0.0f, -3.0f ),
		glm::vec3(  4.0f,  0.0f, -2.0f ),
		glm::vec3(  4.0f,  0.0f, -1.0f ),
		glm::vec3(  4.0f,  0.0f,  0.0f ),
		glm::vec3(  4.0f,  0.0f,  1.0f ),
		glm::vec3(  4.0f,  0.0f,  2.0f ),
		glm::vec3(  4.0f,  0.0f,  3.0f ),
		glm::vec3(  4.0f,  0.0f,  4.0f )
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
		// glm::mat4 view = cam.lookAt();
		glm::mat4 view = glm::lookAt(cam.getPos(), cam.getPos() + cam.getFront(), cam.getUp());

		projection = glm::perspective(glm::radians(cam.getFOV()), 800.0f / 600.0f, 0.1f, 100.0f);

		// std::cout << "View:\t\t" << glm::to_string(view) << std::endl;
		// std::cout << "glm::lookAt\t" << glm::to_string(glm::lookAt(cam.getPos(), cam.getPos() + cam.getFront(), cam.getUp())) << std::endl << std::endl;
		// std::cout << "MylookAt\t" << glm::to_string(cam.lookAt()) << std::endl << std::endl;

		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		for (int i = 0; i < 81; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			float angle = 20.0f * i;

			model = glm::translate(model, cubePositions[i]);
			// model = glm::rotate(model, glm::radians(angle), glm::vec3(0.5f, 1.0f, 0.0f));
			// if (!(i % 3))
			// 	model = glm::rotate(model, glm::radians((float)glfwGetTime() * 50.0f), glm::vec3(0.5f, 1.0f, 0.5f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		player_gravity(cubePositions, 81);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;
}
