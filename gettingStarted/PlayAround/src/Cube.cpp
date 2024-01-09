#include "../hdr/Cube.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

/* -------- Constructors & Destructor -------- */

Cube::Cube()
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
		 0,  1,  3,	 1,  2,  3,
		 4,  5,  7,	 5,  6,  7,
		 8,  9, 11,	 9, 10, 11,
		12, 13, 15,	13, 14, 15,
		16, 17, 19,	17, 18, 19,
		20, 21, 23,	21, 22, 23
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

Cube::~Cube() {}

/* --------  -------- */


/* --------  -------- */


/* --------  -------- */


/* --------  -------- */


/* --------  -------- */
