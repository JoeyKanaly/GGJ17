#ifndef TOOLS_H
#define TOOLS_H

#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include "Log.h"
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <fmod\fmod_errors.h>
typedef unsigned int GLuint;

GLuint loadShader(std::string vertex, std::string fragment);
GLuint loadShader(std::string vertex, std::string fragment, std::string geom);
std::string getFormattedTime();
void handleFMODError(FMOD_RESULT result);
#endif