#ifndef TEXT_H
#define TEXT_H

#include <ft2build.h>
#include FT_FREETYPE_H
#include "Drawable.h"
#include "Log.h"

class Text : public Drawable
{
public:
	Text();
private:
	FT_Library ft;
	FT_Face font;
};

#endif