#ifndef COMPONENT_RECTANGLE_H_
#define COMPONENT_RECTANGLE_H_

#include <stdbool.h>

#include "../component/vector.h"

struct s_rectangle {
    Vector *topLeft;
    Vector *bottomRight;
    unsigned int color;
    bool fill;
};
typedef struct s_rectangle Rectangle;

float GetRectangleWidth(const Rectangle *rectangle);
float GetRectangleHeight(const Rectangle *rectangle);
void GetRectangleCenterVector(Vector *resultVec, const Rectangle *rectangle);
void MoveRectangleToVector(Rectangle *rectangle, const Vector *vector);
bool IntersectsRectangle(const Rectangle *rectangle, const Rectangle *otherRect);
bool ContainsVector(const Rectangle *rectangle, const Vector *vector);
bool AreEqualRectangles(const Rectangle *rectangle, const Rectangle *otherRect);
Rectangle * CreateRectangle(Vector *topLeft, Vector *bottomRight, const unsigned int color, bool fill);

#endif /* COMPONENT_RECTANGLE_H_ */

