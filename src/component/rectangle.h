#ifndef COMPONENT_RECTANGLE_H_
#define COMPONENT_RECTANGLE_H_

#include <stdbool.h>

#include "../component/vector.h"
#include "../component/rule.h"

// Rectangle representation. Constructed from two vectors or four floating coordinates
struct s_rectangle {
    Vector *topLeft;
    Vector *bottomRight;
    ShapeRules *rules;
    unsigned int color;
    bool fill;
};
typedef struct s_rectangle Rectangle;

// Returns the rectangle width
float GetRectangleWidth(const Rectangle *rectangle);

// Returns the rectangle height
float GetRectangleHeight(const Rectangle *rectangle);

// Returns the rectangle center point
void GetRectangleCenterVector(Vector *resultVec, const Rectangle *rectangle);

// Moves rectangle to a given vector on the 2d plane
void MoveRectangleToVector(Rectangle *rectangle, const Vector *vector);

// Returns true if rectangle and otherRect intersects eachother
bool IntersectsRectangle(const Rectangle *rectangle, const Rectangle *otherRect);

// Returns true if vector is contained within the boundary of rectangle
bool ContainsVector(const Rectangle *rectangle, const Vector *vector);

// Returns true if the two vectors that define the rectangle are equal for both rectangles
bool AreEqualRectangles(const Rectangle *rectangle, const Rectangle *otherRect);

// Create rectangle from individual coordinates on a 2d plane
Rectangle * CreateRectangleFromPoints(
    float x0, float y0,       // top-left     point
    float x1, float y1,       // bottom-right point
    float xv,                 // x-velocity
    float yv,                 // y-velocity
    int collisionLayer,       // collisionType
    const unsigned int color, // rectangle color
    bool fill                 // fill rectangle area with color
);

// Create rectangle from two existing Vectors
Rectangle * CreateRectangle(
    Vector *topLeft,          // top-left     vector
    Vector *bottomRight,      // bottom-right vector
    float xv,                 // x-velocity
    float yv,                 // y-velocity
    int collisionLayer,       // collisionType
    const unsigned int color, // rectangle color
    bool fill                 // fill rectangle area with color
);


#endif /* COMPONENT_RECTANGLE_H_ */
