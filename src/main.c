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
	Screen * screen = InitScreen("Test", 800, 800, 1);

	ShapeArray * shapes = CreateEmptyShapeArray();


	Line * line1 = CreateLine(CreateVector(250, 250), CreateVector(440, 440), RED);
	Line * line2 = CreateLine(CreateVector(0, 800), CreateVector(800, 0), BLUE);
	Line * line3 = CreateLine(CreateVector(440, 440), CreateVector(740, 0), LIGHT_BLUE);

	Triangle * tri0 = CreateTriangle(CreateVector(0, 0), CreateVector(0, 400), CreateVector(400, 400), PURPLE, true);

	Rectangle * rect = CreateRectangle(CreateVector(400, 600), CreateVector(550, 550), YELLOW, false);

	Circle * circ = CreateCircle(CreateVector(700, 700), 20, GREEN, false);

	AddShapeToArray(shapes, line1, LINE);
	AddShapeToArray(shapes, line2, LINE);
	AddShapeToArray(shapes, line3, LINE);
	AddShapeToArray(shapes, tri0, TRIANGLE);
	AddShapeToArray(shapes, rect, RECTANGLE);
	AddShapeToArray(shapes, circ, CIRCLE);

	RemoveShapeFromArray(shapes, line2, LINE);
	//RemoveShapeFromArray(shapes, tri0, TRIANGLE);
	//RemoveShapeFromArray(shapes, rect, RECTANGLE);


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

