#ifndef TOOLS_H
#define TOOLS_H

#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include "Log.h"
typedef unsigned int GLuint;

GLuint loadShader(std::string vertex, std::string fragment);
GLuint loadShader(std::string vertex, std::string fragment, std::string geom);
std::string getFormattedTime();
#endif