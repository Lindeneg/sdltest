#ifndef COMPONENT_TRIANGLE_H_
#define COMPONENT_TRIANGLE_H_

#include <stdbool.h>
#include "../component/rule.h"
#include "../component/vector.h"

// A simple triangle representation. Constructed from three vectors or six floats.
struct s_triangle {
    Vector *p0;
    Vector *p1;
    Vector *p2;
    ShapeRules *rules;
    unsigned int color;
    bool fill;
};
typedef struct s_triangle Triangle;

// Sets resultVec to the center vector of the triangle
void GetTriangleCenterPoint(Vector *resultVec, const Triangle *triangle);

// Returns the area of the triangle
float GetTriangleArea(const Triangle *triangle);

// Returns true if the given vector is within the bounds of the triangle
bool TriangleContainsVector(const Triangle *triangle, const Vector *vector);

// Returns true if the three vectors that define the triangles are equal
bool AreEqualTriangles(const Triangle *triangle, const Triangle *otherTriangle);

// Create triangle from individual coordinates on a 2d plane
Triangle * CreateTriangleFromPoints(
    float x0, float y0,       // point one
    float x1, float y1,       // point two
    float x2, float y2,       // point three
    float xv,                 // x-velocity
    float yv,                 // y-velocity
    int collisionLayer,       // collisionType
    const unsigned int color, // triangle color
    bool fill                 // fill triangle area with color
);

// Creates triangle from existing three vectors 
Triangle * CreateTriangle(
    Vector *p0,               // vector one
    Vector *p1,               // vector two
    Vector *p2,               // vector three
    float xv,                 // x-velocity
    float yv,                 // y-velocity
    int collisionLayer,       // collisionType
    const unsigned int color, // triangle color
    bool fill                 // fill triangle area with color
);

#endif /* COMPONENT_TRIANGLE_H_ */

