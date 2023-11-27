#ifndef CUBE_HPP
# define CUBE_HPP

# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include <glm/gtc/type_ptr.hpp>

class Cube
{
	private:
		float	_size;
		glm::vec3	_vectices[8];
		float	_polygons[180];
		


	public:
		Cube();
		Cube(Cube & src);
		~Cube();

		Cube & operator=(Cube & rhs);

};

#endif
