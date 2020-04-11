#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

#include "./screen/screen.h"
#include "./screen/draw.h"
#include "./util/constants.h"
#include "./util/util.h"

#include "./component/vector.h"
#include "./component/line.h"

#include "./shape/shape.h"


int main(void) {
	Screen * screen = InitScreen("Test", 800, 800, 1);

	ShapeArray * shapes = CreateEmptyShapeArray();


	Line * line1 = CreateLine(CreateVector(0, 0), CreateVector(800, 800), RED);
	Line * line2 = CreateLine(CreateVector(0, 800), CreateVector(800, 0), BLUE);

	AddShapeToArray(shapes, line1, LINE);
	AddShapeToArray(shapes, line2, LINE);

	int isRunning = 1;
	SDL_Event sdlEvent;

	//RemoveShapeFromArray(shapes, line2, LINE);

	while (isRunning) {

		while(SDL_PollEvent(&sdlEvent)) {
			switch(sdlEvent.type) {
				case SDL_QUIT:
				isRunning = 0;
				break;	
			}
		}
		DrawShapeArray(screen, shapes);
		UpdateScreen(screen);

	}
	FreeComponent(line1, LINE);
	FreeComponent(line2, LINE);
	FreeScreen(screen);
	return 0;
}

