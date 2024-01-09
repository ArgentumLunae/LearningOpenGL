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

#include "../hdr/Shader2.hpp"
#include "../hdr/Cameras/FreeFlightCam.hpp"
#include "../hdr/Cameras/FpsCamera.hpp"
#include "../hdr/Cube.hpp"

#define WIN_WIDTH 640
#define WIN_HEIGHT 480

#include <deque>

float	mixValue = 0.2;

float	deltaTime = 0.0f;
float	lastFrame = 0.0f;

bool		firstMouse = true;

float const		playerHeight = 1.8f;
// FreeFlightCam	cam = FreeFlightCam();
FpsCamera	cam = FpsCamera();

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
	float cameraSpeed;

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		cameraSpeed = 10.0f * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
		cameraSpeed = 5.0f * deltaTime;
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
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cam.moveForward(cameraSpeed);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cam.strafeRight(cameraSpeed);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cam.moveBack(cameraSpeed);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cam.strafeLeft(cameraSpeed);
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		cam.jump();
	// if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	// 	cam.crouch();
	// if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	// 	cam.crouch();
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
	if (glfwGetKey(window, GLFW_KEY_HOME) == GLFW_PRESS)
		cam.setPos(glm::vec3(0.0f, playerHeight, 0.0f));
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
	cam.updateFOV((float)yoffset * -1.0f);
}

// void player_gravity(glm::vec3 const *ground, int const nrOfObjects)
// {
// 	float			fallSpeed = cam.getVertSpeed();
// 	float			gravity = -0.1 * deltaTime;	//gravitational acceleration
// 	glm::vec3		playerPos = cam.getPos();

// 	for (int i = 0; i < nrOfObjects; i++)
// 	{
// 		if (fallSpeed > 0.0f)
// 			break;
// 		glm::vec3 relativePos = playerPos - ground[i];
// 		if (!(relativePos.x > -0.55 && relativePos.x < 0.55 && relativePos.z > -0.55 && relativePos.z < 0.55))
// 			continue ;
// 		if ((playerPos.y - ground[i].y) < (playerHeight) && (playerPos.y - ground[i].y) > (playerHeight - 0.5))
// 		{
// 			fallSpeed = 0;
// 			playerPos.y = ground[i].y + playerHeight;
// 			cam.setPos(playerPos);
// 			cam.setGrounded(true);
// 			cam.setVertSpeed(fallSpeed);
// 			return ;
// 		}
// 	}
// 	cam.setGrounded(false);
// 	fallSpeed += gravity;
// 	if (fallSpeed > (10 * deltaTime))
// 		fallSpeed == 10 * deltaTime;
// 	playerPos.y += fallSpeed;
// 	cam.setPos(playerPos);
// 	cam.setVertSpeed(fallSpeed);
// }

unsigned int importPNG(char const *texturePath)
{
	float borderColour[] = { 0.0f, 1.0f, 1.0f, 1.0f };
	unsigned int texture;
	int width, height, nrChannels;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColour);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);

	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(texturePath, &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cerr << "Failed to load texture: " << texturePath << std::endl;
	stbi_image_free(data);

	return texture;	
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

	Shader2 myShader("../shaders/vertex/3Dbasics.vs", "../shaders/fragment/basic.fs");
	Cube	cube;		// contains VAO VBO and EBO describing a cube.

	// setup texture
	unsigned int texture1 = importPNG("../textures/grass.png");
	unsigned int texture2 = importPNG("../textures/awesomeface.png");

	myShader.use();
	std::cout << "texture IDs: " << texture1 << ", " << texture2 << std::endl;
	myShader.setInt("texture1", 0);
	myShader.setInt("texture2", 1);

	int modelLoc = glGetUniformLocation(myShader.ID, "model");
	int viewLoc = glGetUniformLocation(myShader.ID, "view");
	int projectionLoc = glGetUniformLocation(myShader.ID, "projection");

	std::deque<glm::vec3> cubePositions;
	for (int i = -4; i < 5; i++)
	{
		for (int j = -4; j < 5; j++)
		{
			if (i == -4 || i == 4 || j == -4 || j == 4)
				cubePositions.push_back(glm::vec3((float)i, 1.0f, (float)j));
			else
				cubePositions.push_back(glm::vec3((float)i, 0.0f, (float)j));
		}
	}

	// render loop
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		processInput(window);

		glClearColor(0.75, 0.25, 0.15, 1.0);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		myShader.use();

		glm::mat4 projection = glm::mat4(1.0f);
		glm::mat4 view = glm::lookAt(cam.getPos(), cam.getPos() + cam.getFront(), cam.getUp());

		projection = glm::perspective(glm::radians(cam.getFOV()), 800.0f / 600.0f, 0.1f, 100.0f);
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		for (int i = 0; i < cubePositions.size(); i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			float angle = 20.0f * i;

			model = glm::translate(model, cubePositions[i]);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		cam.isGrounded(cubePositions);
		cam.fall(deltaTime);
		// std::cout << cam.getGrounded() << std::endl;
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &cube.VAO);
	glDeleteBuffers(1, &cube.VBO);
	glDeleteBuffers(1, &cube.EBO);

	glfwTerminate();
	return 0;
}
