#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

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

Screen *InitScreen(const char *title, unsigned int width, unsigned int height) {
	unsigned int scale = 1;
	BackBuffer * backBuffer = (BackBuffer*)AllocMem(sizeof(BackBuffer));
	FrontBuffer * frontBuffer = (FrontBuffer*)AllocMem(sizeof(FrontBuffer));
	Screen * screen = (Screen*)AllocMem(sizeof(Screen));
	screen->width = width;
	screen->height = height;
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
		printf("\nAn error occured initializing frontbuffer");
		exit(-1);
	}
	screen->pixelFormat = frontBuffer->surface->format;
	if (!(screen->pixelFormat)) {
		printf("\nAn error occured fetching pixel format from SDL_WindowSurface");
		exit(-1);
	}
	screen->color = GetScreenColors(screen->pixelFormat);
	if (!(screen->color)) {
		printf("\nAn error occured initializing screen colors");
		exit(-1);
	}
	backBuffer->surface = SDL_CreateRGBSurfaceWithFormat(
		0,
		screen->width,
		screen->height,
		0,
		screen->pixelFormat->format
	);
	if (!(backBuffer->surface)) {
		printf("\nAn error occured initializing backbuffer");
		exit(-1);
	}
	frontBuffer->clearColor = BLACK;
	backBuffer->clearColor = BLACK;
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
