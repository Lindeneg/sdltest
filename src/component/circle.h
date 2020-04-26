#ifndef COMPONENT_CIRCLE_H_
#define COMPONENT_CIRCLE_H_

#include <stdbool.h>
#include "../component/rule.h"
#include "../component/vector.h"

// Cirlce representation. Constructed by a single vector and a radius or two floating numbers and a radius.
struct s_circle {
    Vector     *center;
    float       radius;
    ShapeRules  *rules;
    unsigned int color;
    bool          fill;
};
typedef struct s_circle Circle;

// Moves circle to a given point on the 2d plane
void MoveCircleToVector(Circle *circle, const Vector *vector);

// Returns true if the two circles intersects eachother
bool IntersectsCircle(const Circle *circle, const Circle *otherCircle);

// Returns true if the given vector is contained by the boundary of the circle
bool CircleContainsVector(const Circle *circle, const Vector* vector);

// Returns true if the two circles share center vector and radius
bool AreEqualCircles(const Circle *circle, const Circle *otherCircle);

// Creates circle from individual coordinates on a 2d plane
Circle * CreateCircleFromPoints(
    float x0, float y0,       // center point
    float radius,             // circle radius
    float xv,                 // x-velocity
    float yv,                 // y-velocity
    int collisionLayer,       // collisionType
    const unsigned int color, // circle color
    bool fill                 // fill circle area with color
);

// Creates circle from an existing vector
Circle * CreateCircle(
    Vector *center,           // center vector
    float radius,             // circle radius
    float xv,                 // x-velocity
    float yv,                 // y-velocity
    int collisionLayer,       // collisionType
    const unsigned int color, // circle color
    bool fill                 // fill circle area with color
);


#endif /* COMPONENT_CIRCLE_H_ */
