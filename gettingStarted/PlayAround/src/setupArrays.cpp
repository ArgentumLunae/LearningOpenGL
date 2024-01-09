#include <glad/glad.h>
#include <GLFW/glfw3.h>

void setupArrays(unsigned int &VAO, unsigned int &VBO, unsigned int &EBO)
{
	float triangle[] = {
		// location			// texture coords
	-0.5f, -0.5f, -0.5f,	0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,	1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,	1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,	1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,	0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,	0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,	0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,	1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,	1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,	1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,	0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,	0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,	1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,	1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,	0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,	0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,	0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,	1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,	1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,	1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,	0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,	0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,	0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,	1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,	0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,	1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,	1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,	1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,	0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,	0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,	0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,	1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,	1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,	1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,	0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,	0.0f, 1.0f
	};
	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// location attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	// texture attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}