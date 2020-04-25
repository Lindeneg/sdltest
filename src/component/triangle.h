#ifndef COMPONENT_TRIANGLE_H_
#define COMPONENT_TRIANGLE_H_

#include <stdbool.h>

#include "../component/vector.h"

struct s_triangle {
    Vector *p0;
    Vector *p1;
    Vector *p2;
    unsigned int color;
    bool fill;
};
typedef struct s_triangle Triangle;


void GetTriangleCenterPoint(Vector *resultVec, const Triangle *triangle);
float GetTriangleArea(const Triangle *triangle);
bool TriangleContainsVector(const Triangle *triangle, const Vector *vector);
bool AreEqualTriangles(const Triangle *triangle, const Triangle *otherTriangle);
Triangle * CreateTriangleFromPoints(float x0, float y0, float x1, float y1, float x2, float y2, const unsigned int color, bool fill);
Triangle * CreateTriangle(Vector *p0, Vector *p1, Vector *p2, const unsigned int color, bool fill);

#endif /* COMPONENT_TRIANGLE_H_ */

