#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../screen/screen.h"
#include "../util/constants.h"
#include "../util/util.h"


static void ClearFrontBuffer(Screen *screen) {
	if (screen->frontBuffer->surface) {
		SDL_FillRect(
			screen->frontBuffer->surface,
			NULL,
			screen->frontBuffer->clearColor
		);
	}
}

static void ClearBackBuffer(Screen *screen) {
	if (screen->backBuffer->surface) {
		SDL_FillRect(
			screen->backBuffer->surface,
			NULL,
			screen->backBuffer->clearColor
		);
	}	
}


Screen *InitScreen(
		const char *title, 
		unsigned int width, 
		unsigned int height, 
		unsigned int scale
		) {
	BackBuffer * backBuffer = (BackBuffer*)AllocMem(sizeof(BackBuffer));
	FrontBuffer * frontBuffer = (FrontBuffer*)AllocMem(sizeof(FrontBuffer));
	Screen * screen = (Screen*)AllocMem(sizeof(Screen));

	screen->width = width;
	screen->height = height;

	// fb
	frontBuffer->window = SDL_CreateWindow(
		title,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		(screen->width * scale),
		(screen->height * scale),
		0
	);
	frontBuffer->surface = SDL_GetWindowSurface(frontBuffer->window);
	if (!(frontBuffer->window) || !(frontBuffer->surface)) {
		printf("\nAn error occured initializing frontbuffer\n");
		exit(-1);
	}

	// color format and colors
	screen->pixelFormat = frontBuffer->surface->format;
	if (!(screen->pixelFormat)) {
		printf("\nAn error occurd initialzing pixel format\n");
		exit(-1);
	}
	screen->color = GetScreenColors(screen->pixelFormat);
	if (!(screen->color)) {
		printf("\nAn error occurd initialzing screen colors\n");
		exit(-1);
	}
	
	// bb
	backBuffer->surface = SDL_CreateRGBSurfaceWithFormat(
		0,
		screen->width,
		screen->height,
		0,
		screen->pixelFormat->format
	);
	if (!(backBuffer->surface)) {
		printf("\nAn error occured initializing backbuffer\n");
		exit(-1);
	}
	frontBuffer->clearColor = BLACK;
	backBuffer->clearColor = BLACK;
	
	// screen
	screen->backBuffer = backBuffer;
	screen->frontBuffer = frontBuffer;
	return screen;
}


void UpdateScreen(Screen *screen) {
	if (screen->frontBuffer->window) {
		ClearFrontBuffer(screen);
		SDL_BlitScaled(
			screen->backBuffer->surface,
			NULL,
			screen->frontBuffer->surface,
			NULL
		);
		SDL_UpdateWindowSurface(screen->frontBuffer->window);
		ClearBackBuffer(screen);
	}
}
