#include <stdlib.h>
#include <stdio.h>

#include "../util/color.h"
#include "../util/util.h"


Color *GetScreenColors(const SDL_PixelFormat *format) {
	Color * color = (Color*)AllocMem(sizeof(Color));
	color->black = SDL_MapRGBA(format, 0, 0, 0, 255);
	color->lightBlue = SDL_MapRGBA(format, 0, 255, 255, 255);
	color->gray = SDL_MapRGBA(format, 128, 128, 128, 255);
	color->darkBlue = SDL_MapRGBA(format, 0, 0, 128, 255);
	color->silver = SDL_MapRGBA(format, 192, 192, 192, 255);
	color->darkGreen = SDL_MapRGBA(format, 0, 128, 0, 255);
	color->olive = SDL_MapRGBA(format, 128, 128, 0, 255);
	color->teal = SDL_MapRGBA(format, 0, 128, 128, 255);
	color->blue = SDL_MapRGBA(format, 0, 0, 255, 255);
	color->green = SDL_MapRGBA(format, 0, 255, 0, 255);
	color->purple = SDL_MapRGBA(format, 128, 0, 128, 255);
	color->lightRed = SDL_MapRGBA(format, 255, 0, 255, 255);
	color->darkRed = SDL_MapRGBA(format, 128, 0, 0, 255);
	color->red = SDL_MapRGBA(format, 255, 0, 0, 255);
	color->yellow = SDL_MapRGBA(format, 255, 255, 0, 255);
	color->white = SDL_MapRGBA(format, 255, 255, 255, 255);
	return color;	
}




