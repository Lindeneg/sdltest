#include <stdlib.h>
#include <math.h>

#include <SDL2/SDL.h>

#include "../util/util.h"
#include "../util/constants.h"
#include "../component/vector.h"

#include <stdio.h>


void FreeMem(void *ptr) {
	free(ptr);
	ptr = NULL;
}

void FreeScreen(Screen *screen) {
	SDL_FreeSurface(screen->frontBuffer->surface);
	SDL_DestroyWindow(screen->frontBuffer->window);
	SDL_FreeSurface(screen->backBuffer->surface);
	screen->backBuffer->surface = NULL;
	screen->frontBuffer->surface = NULL;
	screen->frontBuffer->window = NULL;
	FreeMem(screen->backBuffer);
	FreeMem(screen->frontBuffer);
	FreeMem(screen->color);
	FreeMem(screen);
}

void FreeShapeArray(ShapeArray *shapes) {

}

void FreeComponent(void *ptr, const unsigned int type) {
	if (type == LINE) {
		Line *line = (Line*)ptr;
		FreeMem(line->p0);
		FreeMem(line->p1);
		FreeMem(line);
	}
}

void *AllocMem(size_t size) {
	void * ptr = NULL;
	ptr = malloc(size);
	if (ptr == NULL) {
		printf("\nMemAlloc failed");
		exit(-1);
	}
	return ptr;
}

void ReAllocMem(void *ptr, size_t newSize) {
	if (realloc(ptr, newSize) == NULL) {
		printf("\nMemAlloc failed");
		exit(-1);
	}
}

bool IsEqual(float x, float y) {
	return (fabsf(x - y) < EPSILON);	
}

bool IsGreaterThanOrEqual(float x, float y) {
	return ((x > y) || (IsEqual(x, y)));
}

bool IsLesserThanOrEqual(float x, float y) {
	return ((x < y) || (IsEqual(x, y)));	
}

