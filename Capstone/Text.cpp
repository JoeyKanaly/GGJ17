#ifndef TEXT_H
#include "Text.h"
#endif

Text::Text()
{
	if (FT_Init_FreeType(&ft))
	{
		Log::instance()->writeToLog("Unable to initalize FreeType.");
	}

	if (FT_New_Face(ft,"./fonts/arial.ttf", 0, &font))
	{
		Log::instance()->writeToLog("Unable to load font (./fonts/arial.ttf)");
	}
}
