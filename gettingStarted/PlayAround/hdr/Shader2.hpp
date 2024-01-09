#ifndef SHADER2_HPP
# define SHADER2_HPP

#include "glad.h"

# include <fstream>
# include <sstream>
# include <iostream>

class Shader2
{
	public:
		unsigned int ID;

		Shader2(char const *vertexPath, char const *fragmentPath);
		~Shader2();

		void use();

		void setBool(std::string const name, bool const value) const;
		void setInt(std::string const name, int const value) const;
		void setFloat(std::string const name, float const value) const;
};

#endif
