#ifndef SHADER_HPP
# define SHADER_HPP

# include "glad.h"

# include <fstream>
# include <sstream>
# include <iostream>

class Shader
{
	public:
		unsigned int ID;

		Shader(char const *vertexPath, char const *fragmentPath);
		~Shader();

		void use();

		void setBool(std::string const &name, bool value) const;
		void setInt(std::string const &name, int value) const;
		void setFloat(std::string const &name, float value) const;		
};

#endif
