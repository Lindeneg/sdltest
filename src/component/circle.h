#ifndef COMPONENT_CIRCLE_H_
#define COMPONENT_CIRCLE_H_

#include <stdbool.h>

#include "../component/vector.h"

struct s_circle {
    Vector     *center;
    float       radius;
    unsigned int color;
    bool          fill;
};
typedef struct s_circle Circle;

void MoveCircleToVector(Circle *circle, const Vector *vector);

bool IntersectsCircle(const Circle *circle, const Circle *otherCircle);
bool CircleContainsVector(const Circle *circle, const Vector* vector);
bool AreEqualCircles(const Circle *circle, const Circle *otherCircle);

Circle * CreateCircle(Vector *center, float radius, const unsigned int color, bool fill);

#endif /* COMPONENT_CIRCLE_H_ */

