#ifndef SCREEN_BUFFER_H_
#define SCREEN_BUFFER_H_

#include <stddef.h>
#include <SDL2/SDL.h>


struct s_back_buffer {
	SDL_Surface *surface;
	uint8_t clearColor;
};

struct s_front_buffer {
	SDL_Window *window;
	SDL_Surface *surface;
	uint8_t clearColor;
};

typedef struct s_back_buffer BackBuffer;
typedef struct s_front_buffer FrontBuffer;

#endif /* SCREEN_BUFFER_H_ */
