#include "../hdr/Shader2.hpp"

/* -------- Member Functions -------- */

void	Shader2::use() {
	glUseProgram(this->ID);
}

void	Shader2::setBool(std::string const name, bool const value) const {
	glUniform1i(glGetUniformLocation(this->ID, name.c_str()), (int)value);
}

void	Shader2::setInt(std::string const name, int const value) const {
	glUniform1i(glGetUniformLocation(this->ID, name.c_str()), value);
}

void	Shader2::setFloat(std::string const name, float const value) const {
	glUniform1f(glGetUniformLocation(this->ID, name.c_str()), value);
}


/* -------- Constructors & Destructor -------- */

Shader2::Shader2(char const *vertexPath, char const *fragmentPath)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		std::stringstream vShaderStream, fShaderStream;

		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch(const std::exception& e)
	{
		std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		std::cerr << e.what() << '\n';
	}
	
	char const *vShaderCode = vertexCode.c_str();
	char const *fShaderCode = fragmentCode.c_str();
	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	this->ID = glCreateProgram();
	glAttachShader(this->ID, vertex);
	glAttachShader(this->ID, fragment);
	glLinkProgram(this->ID);
	glGetShaderiv(fragment, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(this->ID, 512, NULL, infoLog);
		std::cout << "ERROR::PROGRAM::SHADER::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

Shader2::~Shader2() {}
