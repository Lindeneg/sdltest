#ifndef SCREEN_DRAW_H_
#define SCREEN_DRAW_H_

#include "../screen/screen.h"
#include "../component/vector.h"
#include "../component/line.h"
#include "../component/triangle.h"
#include "../component/rectangle.h"
#include "../shape/shape.h"


void DrawShapeArray(Screen *screen, const ShapeArray *shapeArray);

void DrawVector(Screen *screen, const Vector *vec, const unsigned int color);
void DrawLine(Screen *screen, Line *line);
void DrawTriangle(Screen *screen, Triangle *triangle);
void DrawRectangle(Screen *screen, Rectangle *rectangle);


#endif /* SCREEN_DRAW_H_ */

