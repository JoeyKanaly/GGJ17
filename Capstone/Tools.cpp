#ifndef TOOLS_H
#include "Tools.h"
#endif


#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>

std::string loadShaderData(std::string path)
{
	std::string line, source;
	std::ifstream file;
	file.open(path, std::ifstream::in);
	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			source.append(line + "\n");
		}
		file.close();
	}
	return source;
}

GLuint loadShader(std::string vertex, std::string fragment)
{
	GLuint shaderProgram;
	GLuint vertexShader;
	GLuint fragmentShader;
	std::string source;
	GLint success;
	GLchar infoLog[512];
	const char* sc;

	shaderProgram = glCreateProgram();
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	source = loadShaderData(vertex);

	glShaderSource(vertexShader, 1, &(sc = source.c_str()), NULL);

	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		Log::instance()->writeToLog("Vertex Shader was unable to compile (" + vertex + "): \n" + static_cast<std::string>(infoLog));
	}

	source = loadShaderData(fragment);

	glShaderSource(fragmentShader, 1, &(sc = source.c_str()), NULL);

	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		Log::instance()->writeToLog("Vertex Shader was unable to compile (" + fragment + "): \n" + static_cast<std::string>(infoLog));
	}

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		Log::instance()->writeToLog("Shader was unable to compile. (" + vertex + ") (" + fragment +")");
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}

GLuint loadShader(std::string vertex, std::string fragment, std::string geom)
{
	GLuint shaderProgram;
	GLuint vertexShader, geometryShader, fragmentShader;
	std::string source;
	GLint success;
	GLchar infoLog[512];
	const char* sc;

	shaderProgram = glCreateProgram();
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	source = loadShaderData(vertex);

	glShaderSource(vertexShader, 1, &(sc = source.c_str()), NULL);

	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		Log::instance()->writeToLog("Vertex Shader was unable to compile (" + vertex + "): \n" + static_cast<std::string>(infoLog));
	}

	source = "";

	source = loadShaderData(geom);

	glShaderSource(geometryShader, 1, &(sc = source.c_str()), NULL);
	glCompileShader(geometryShader);
	glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(geometryShader, 512, NULL, infoLog);
		Log::instance()->writeToLog("Vertex Shader was unable to compile (" + geom + "): \n" + static_cast<std::string>(infoLog));
	}

	source = "";

	source = loadShaderData(fragment);
	

	glShaderSource(fragmentShader, 1, &(sc = source.c_str()), NULL);

	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		Log::instance()->writeToLog("Vertex Shader was unable to compile (" + fragment + "): \n" + static_cast<std::string>(infoLog));
	}

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, geometryShader);
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		Log::instance()->writeToLog("Shader was unable to compile. (" + vertex + ") (" + geom + ") (" + fragment + ")");
	}

	glDeleteShader(vertexShader);
	glDeleteShader(geometryShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}

std::string getFormattedTime()
{
	time_t rawTime;
	tm timeInfo;
	char stringBuffer[26];
	time(&rawTime);
	localtime_s(&timeInfo, &rawTime);
	strftime(stringBuffer, sizeof(stringBuffer), "%m-%d-%y %H-%M-%S", &timeInfo);
	std::string returnString = stringBuffer;
	return returnString;
}
