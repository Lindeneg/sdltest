#ifndef UTIL_COLOR_H_
#define UTIL_COLOR_H_

#include <stddef.h>
#include <SDL2/SDL.h>

struct s_color {
	uint32_t black;
	uint32_t lightBlue;
	uint32_t gray;
	uint32_t darkBlue;
	uint32_t silver;
	uint32_t darkGreen;
	uint32_t olive;
	uint32_t teal;
	uint32_t blue;
	uint32_t green;
	uint32_t purple;
	uint32_t lightRed;
	uint32_t darkRed;
	uint32_t red;
	uint32_t yellow;
	uint32_t white;
};

typedef struct s_color Color;

Color *GetScreenColors(const SDL_PixelFormat *format);

#endif /* UTIL_COLOR_H_ */
