#ifndef CUBE_HPP
# define CUBE_HPP

# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include <glm/gtc/type_ptr.hpp>

class Cube
{
	public:
		unsigned int VAO;
		unsigned int VBO;
		unsigned int EBO;

		Cube();
		// Cube(Cube & src);
		~Cube();

		// Cube & operator=(Cube & rhs);

};

#endif
