#ifndef SCREEN_DRAW_H_
#define SCREEN_DRAW_H_

#include "../screen/screen.h"
#include "../component/vector.h"
#include "../component/line.h"
#include "../shape/shape.h"

void DrawVector(Screen *screen, const Vector *vec, const unsigned int color);
void DrawShapeArray(Screen *screen, const ShapeArray *shapeArray);

void DrawLine(Screen *screen, Line *line);

/*
void DrawLine(Screen * screen, char * line);
void DrawRectangle(Screen * screen, char * rectangle);
void DrawTriangle(Screen * screen, char * triangle);
void DrawCircle(Screen * screen, char * circle);
*/

#endif /* SCREEN_DRAW_H_ */

