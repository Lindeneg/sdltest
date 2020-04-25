#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#include <stdio.h>

#include "../screen/draw.h"
#include "../util/color.h"
#include "../util/constants.h"
#include "../util/util.h"


static bool IsWithinBounds(Screen *screen, int x, int y) {
	int w = screen->backBuffer->surface->w;
	int h = screen->backBuffer->surface->h;
	return ((x < w && x >= 0) && (y < h && y >= 0));
}

static size_t GetPixelTarget(Screen *screen, int x, int y) {
	return y * screen->backBuffer->surface->w + x;
}

static uint32_t GetSDLColor(Screen *screen, const unsigned int color) {
	if ((screen->color) && (screen->pixelFormat)) {
		if (color == BLACK) {
			return screen->color->black;
		}
		if (color == LIGHT_BLUE) {
			return screen->color->lightBlue;
		}
		if (color == GRAY) {
			return screen->color->gray;
		}
		if (color == DARK_BLUE) {
			return screen->color->darkBlue;
		}
		if (color == SILVER) {
			return screen->color->silver;
		}
		if (color == DARK_GREEN) {
			return screen->color->darkGreen;
		}
		if (color == OLIVE) {
			return screen->color->olive;
		}
		if (color == TEAL) {
			return screen->color->teal;
		}
		if (color == BLUE) {
			return screen->color->blue;
		}
		if (color == GREEN) {
			return screen->color->green;
		}
		if (color == PURPLE) {
			return screen->color->purple;
		}
		if (color == LIGHT_RED) {
			return screen->color->lightRed;
		}
		if (color == DARK_RED) {
			return screen->color->darkRed;
		}
		if (color == RED) {
			return screen->color->red;
		}
		if (color == YELLOW) {
			return screen->color->yellow;
		}
		if (color == WHITE) {
			return screen->color->white;
		}
	}
	return 0;
}

static void SetPixel(Screen *screen, int x, int y, const unsigned int color) {
	if ((screen->backBuffer->surface) && (IsWithinBounds(screen, x, y))) {
		SDL_LockSurface(screen->backBuffer->surface);
		uint32_t * pixels = (uint32_t*)screen->backBuffer->surface->pixels;
		size_t index = GetPixelTarget(screen, x, y); 
		pixels[index] = GetSDLColor(screen, color);
		SDL_UnlockSurface(screen->backBuffer->surface);
	}
}

// Using Bresenham's line algorithm
// https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
static void mDrawLine(Screen *screen, int mx0, int my0, int mx1, int my1, const unsigned int color) {
	if (screen->frontBuffer->window) {
		int x0 = roundf(mx0);
		int y0 = roundf(my0);
		int x1 = roundf(mx1);
		int y1 = roundf(my1);
		int deltaX = x1 - x0;
		int deltaY = y1 - y0;
		signed const int incrementX = ((deltaX > 0) - (deltaX < 0));
		signed const int incrementY = ((deltaY > 0) - (deltaY < 0));
		deltaX = abs(deltaX) * 2;
		deltaY = abs(deltaY) * 2;
		SetPixel(screen, x0, y0, color);
		if (deltaX >= deltaY) {
			int decision = deltaY - (deltaX / 2);
			while (x0 != x1) {
				if (decision >= 0) {
					decision -= deltaX;
					y0 += incrementY;
				}
				decision += deltaY;
				x0 += incrementX;
				SetPixel(screen, x0, y0, color);
			}
		} else {
			int decision = deltaX - (deltaY / 2);
			while (y0 != y1) {
				if (decision >= 0) {
					decision -= deltaY;
					x0 += incrementX;
				}
				decision += deltaX;
				y0 += incrementY;
				SetPixel(screen, x0, y0, color);
			}
		}
	}
}

static void mDrawCircle(Screen *screen, int centerX, int centerY, int x, int y, const unsigned int color) {
	SetPixel(screen, centerX+x, centerY+y, color);
	SetPixel(screen, centerX-x, centerY+y, color);
	SetPixel(screen, centerX+x, centerY-y, color);
	SetPixel(screen, centerX-x, centerY-y, color);
	SetPixel(screen, centerX+y, centerY+x, color);
	SetPixel(screen, centerX-y, centerY+x, color);
	SetPixel(screen, centerX+y, centerY-x, color);
	SetPixel(screen, centerX-y, centerY-x, color);
}

// https://en.wikipedia.org/wiki/Point_in_polygon
// https://en.wikipedia.org/wiki/Winding_number
static int mFillPoly(Screen *screen, const float xv[], const float yv[], const size_t shapeSize, const unsigned int color) {
	if (shapeSize <= 0 || !(xv) || !(yv)) {
		return -1;
	}
	int nodes, xNodes[MAX_POLYGON_CORNERS], pX, pY, i, j, tempSortStore;
	// set initial shape-limit values
	float top, bottom = yv[0];
	float left, right = xv[0];
	// find the actual shape-limits
	for (size_t m = 1; m < shapeSize; ++m) {
		if (yv[m] < top) {
			top = yv[m];
		}
		if (yv[m] > bottom) {
			bottom = yv[m];
		}
		if (xv[m] < left) {
			left = xv[m];
		}
		if (xv[m] > right) {
			right = xv[m];
		}
	}
	// iterate through the rows of the shape
	for (pY = top; pY < bottom; ++pY) {
		// build a list of nodes inside the shape
		nodes = 0;
		j = shapeSize - 1;
		for (i = 0; i < shapeSize; ++i) {
			if ((yv[i] < (float)pY && yv[j] >= (float)pY) || (yv[j] < (float)pY && yv[i] >= (float)pY)) {
				xNodes[nodes++] = (int)(xv[i] + (pY - yv[i]) / (yv[j] - yv[i]) * (xv[j] - xv[i]));
			}
			j = i;
		}
		// desend bubble sort nodes inside shape
		i = 0;
		while (i < nodes - 1) {
			if (xNodes[i] > xNodes[i+1]) {
				tempSortStore = xNodes[i];
				xNodes[i] = xNodes[i + 1];
				xNodes[i + 1] = tempSortStore;
				if (i) {
					i--;
				} else {
					i++;
				}
			}
		}
		// fill the shape with the appropriate color by drawing the pixels found inside the shape 
		for (i = 0; i < nodes; i+=2) {
			if (xNodes[i] >= right) {
				break;
			}
			if (xNodes[i + 1] > left) {
				if (xNodes[i] < left) {
					xNodes[i] = left;
				}
				if (xNodes[i + 1] > right) {
					xNodes[i + 1] = right;
				}
				for (pX = xNodes[i]; pX < xNodes[i + 1]; ++pX) {
					SetPixel(screen, pX, pY, color);
				}
			}
		}
	}
	return 0;
}

void DrawVector(Screen *screen, const Vector *vec, const unsigned int color) {
	SetPixel(screen, vec->x, vec->y, color);
}

void DrawLine(Screen *screen, Line *line) {
	mDrawLine(screen, line->p0->x, line->p0->y, line->p1->x, line->p1->y, line->color);
}

void DrawTriangle(Screen *screen, Triangle *triangle) {
	mDrawLine(screen, triangle->p0->x, triangle->p0->y, triangle->p1->x, triangle->p1->y, triangle->color);
	mDrawLine(screen, triangle->p1->x, triangle->p1->y, triangle->p2->x, triangle->p2->y, triangle->color);
	mDrawLine(screen, triangle->p2->x, triangle->p2->y, triangle->p0->x, triangle->p0->y, triangle->color);
	if (triangle->fill) {
		const float xv[TRIANGLE_SIZE] = { triangle->p0->x, triangle->p1->x, triangle->p2->x };
		const float yv[TRIANGLE_SIZE] = { triangle->p0->y, triangle->p1->y, triangle->p2->y };
		mFillPoly(screen, xv, yv, TRIANGLE_SIZE, triangle->color);
	}
}

void DrawRectangle(Screen *screen, Rectangle *rectangle) {
	mDrawLine(
		screen, 
		rectangle->topLeft->x, 
		rectangle->topLeft->y, 
		rectangle->bottomRight->x, 
		rectangle->topLeft->y, 
		rectangle->color
	);
	mDrawLine(
		screen, 
		rectangle->bottomRight->x, 
		rectangle->bottomRight->y, 
		rectangle->topLeft->x, 
		rectangle->bottomRight->y, 
		rectangle->color
	);
	mDrawLine(
		screen, 
		rectangle->topLeft->x, 
		rectangle->topLeft->y, 
		rectangle->topLeft->x, 
		rectangle->bottomRight->y, 
		rectangle->color
	);
	mDrawLine(
		screen, 
		rectangle->bottomRight->x, 
		rectangle->topLeft->y, 
		rectangle->bottomRight->x, 
		rectangle->bottomRight->y, 
		rectangle->color
	);
	// if (rectangle->fill) {
	// 	const float xv[RECTANGLE_SIZE] = { rectangle->topLeft->x, rectangle->bottomRight->x };
	// 	const float yv[RECTANGLE_SIZE] = { rectangle->topLeft->y, rectangle->bottomRight->y };
	// 	mFillPoly(screen, xv, yv, RECTANGLE_SIZE, rectangle->color);
	// }
}

// Using Bresenham's circle algorithm
// https://en.wikipedia.org/wiki/Midpoint_circle_algorithm
void DrawCircle(Screen *screen, Circle *circle) {
	int x = 0;
	int y = circle->radius;
	int d = 3 - 2 * circle->radius;
	mDrawCircle(screen, circle->center->x, circle->center->y, x, y, circle->color);
	while (y >= x) {
		x++;
		if (d > 0) {
			y--;
			d += 4 * (x - y) + 10;
		} else {
			d += 4 * x + 6;
		}
		mDrawCircle(screen, circle->center->x, circle->center->y, x, y, circle->color);
	}
	if (circle->fill) {
		// todo
	}
}

void DrawShapeArray(Screen *screen, const ShapeArray *shapeArray) {
	if (screen) {
		if ((shapeArray->lineArray) && (shapeArray->lineArray->size >= 1)) {
			for (size_t i = 0; i < shapeArray->lineArray->size; i++) {
				if (shapeArray->lineArray->lines[i]) {
					DrawLine(screen, shapeArray->lineArray->lines[i]);
				}
			}
		}
		if ((shapeArray->triangleArray) && (shapeArray->triangleArray->size >= 1)) {
			for (size_t i = 0; i < shapeArray->triangleArray->size; i++) {
				if (shapeArray->triangleArray->triangles[i]) {
					DrawTriangle(screen, shapeArray->triangleArray->triangles[i]);
				}
			}
		}
		if ((shapeArray->rectangleArray) && (shapeArray->rectangleArray->size >= 1)) {
			for (size_t i = 0; i < shapeArray->rectangleArray->size; i++) {
				if (shapeArray->rectangleArray->rectangles[i]) {
					DrawRectangle(screen, shapeArray->rectangleArray->rectangles[i]);
				}
			}
		}
		if ((shapeArray->circleArray) && (shapeArray->circleArray->size >= 1)) {
			for (size_t i = 0; i < shapeArray->circleArray->size; i++) {
				if (shapeArray->circleArray->circles[i]) {
					DrawCircle(screen, shapeArray->circleArray->circles[i]);
				}
			}
		}
	}
}
