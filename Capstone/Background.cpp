#ifndef BACKGROUND_H
#include "Background.h"
#endif

Background::Background()
{
	setSpritePath("./sprites/debug.png");
}

Background::Background(std::string path)
{
	setSpritePath(path);
}
