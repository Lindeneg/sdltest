#ifndef SCREEN_SCREEN_H_
#define SCREEN_SCREEN_H_

#include <stddef.h>
#include <SDL2/SDL.h>

#include "../screen/buffer.h"
#include "../util/color.h"


struct s_screen {
	BackBuffer *backBuffer;
	FrontBuffer *frontBuffer;
	Color *color;
	const SDL_PixelFormat *pixelFormat;
	uint32_t width;
	uint32_t height;
};
typedef struct s_screen Screen;

Screen * InitScreen(
	const char *title, 
	unsigned int width, 
	unsigned height, 
	unsigned int scale
);
void UpdateScreen(Screen *screen);

#endif /* SCREEN_SCREEN_H_ */
