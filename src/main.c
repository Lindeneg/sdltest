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
#include "./component/triangle.h"
#include "./component/rectangle.h"
#include "./component/circle.h"
#include "./shape/shape.h"


int main(void) {
	Screen * screen = InitScreen("Test", 800, 800);

	ShapeArray * shapes = CreateEmptyShapeArray();


	Line * line1 = CreateLineFromPoints(250, 250, 440, 440, 0, 0, NEUTRAL_COLLISION_LAYER, RED);
	Line * line2 = CreateLineFromPoints(0, 800, 800, 0, 0, 0, NEUTRAL_COLLISION_LAYER, BLUE);
	Line * line3 = CreateLineFromPoints(440, 440, 740, 0, 0, 0, NEUTRAL_COLLISION_LAYER, LIGHT_BLUE);

	Triangle * tri0 = CreateTriangleFromPoints(0, 0, 0, 400, 400, 400, 0, 0, NEUTRAL_COLLISION_LAYER, PURPLE, true);

	Rectangle * rect = CreateRectangleFromPoints(400, 600, 550, 550, 0, 0, NEUTRAL_COLLISION_LAYER, YELLOW, true);

	Circle * circ = CreateCircleFromPoints(700, 700, 20, 0, 0, NEUTRAL_COLLISION_LAYER, GREEN, true);

	AddShapeToArray(shapes, line1, LINE);
	AddShapeToArray(shapes, line2, LINE);
	AddShapeToArray(shapes, line3, LINE);
	AddShapeToArray(shapes, tri0, TRIANGLE);
	AddShapeToArray(shapes, rect, RECTANGLE);
	AddShapeToArray(shapes, circ, CIRCLE);


	int isRunning = 1;
	SDL_Event sdlEvent;
	while (isRunning) {
		while(SDL_PollEvent(&sdlEvent)) {
			switch(sdlEvent.type) {
				case SDL_QUIT:
				isRunning = 0;
				break;	
			}
		}
		RotateLine(shapes->lineArray->lines[0], 0.20);
		DrawShapeArray(screen, shapes);
		UpdateScreen(screen);
	}
	FreeShapeArray(shapes);
	FreeScreen(screen);
	return 0;
}

