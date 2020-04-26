#include "../component/triangle.h"
#include "../util/util.h"

void GetTriangleCenterPoint(Vector *resultVec, const Triangle *triangle) {
    resultVec->x = (triangle->p0->x + triangle->p1->x + triangle->p2->x) / 3.0f;
    resultVec->y = (triangle->p0->y + triangle->p1->y + triangle->p2->y) / 3.0f;
}

float GetTriangleArea(const Triangle *triangle) {
    return fabsf((
        (triangle->p0->x * (triangle->p1->y - triangle->p2->y) 
        + triangle->p1->x * (triangle->p2->y - triangle->p0->y) 
        + triangle->p2->x * (triangle->p0->y - triangle->p1->y))
        / 2.0f));
}

// https://mathworld.wolfram.com/BarycentricCoordinates.html
bool TriangleContainsVector(const Triangle *triangle, const Vector *vector) {
    bool result;
    Triangle *t1 = CreateTriangle(vector, triangle->p1, triangle->p2, 0, 0, NO_COLLISION, BLACK, false);
    Triangle *t2 = CreateTriangle(triangle->p0, vector, triangle->p2, 0, 0, NO_COLLISION, BLACK, false);
    Triangle *t3 = CreateTriangle(triangle->p0, triangle->p1, vector, 0, 0, NO_COLLISION, BLACK, false);
    float area = GetTriangleArea(triangle);
    // the areas of the triangles are proportional to the barycentric coordinates 
    float area1 = GetTriangleArea(t1);
    float area2 = GetTriangleArea(t2);
    float area3 = GetTriangleArea(t3);
    result = IsEqual(area, (area1 + area2 + area3));
    FreeComponent(t1, TRIANGLE);
    FreeComponent(t2, TRIANGLE);
    FreeComponent(t3, TRIANGLE);
    return result;
}

bool AreEqualTriangles(const Triangle *triangle, const Triangle *otherTriangle) {
    return (
        (AreEqualVectors(triangle->p0, otherTriangle->p0)) && 
        (AreEqualVectors(triangle->p1, otherTriangle->p1) &&
        (AreEqualVectors(triangle->p2, otherTriangle->p2)))
    );
}

Triangle * CreateTriangleFromPoints(
    float x0, float y0,
    float x1, float y1,
    float x2, float y2,
    float xv, float yv,
    int collisionLayer,
    const unsigned int color,
    bool fill) 
    {
        Vector *p0 = CreateVector(x0, y0);
        Vector *p1 = CreateVector(x1, y1);
        Vector *p2 = CreateVector(x2, y2);
        return CreateTriangle(p0, p1, p2, xv, yv, collisionLayer, color, fill);
}

Triangle * CreateTriangle(
    Vector *p0, Vector *p1, Vector *p2,
    float xv, float yv, int collisionLayer,
    const unsigned int color, bool fill) 
    {
        ShapeRules *rules = CreateNewShapeRule(xv, yv, collisionLayer);
        Triangle *triangle = (Triangle*)AllocMem(sizeof(Triangle));
        triangle->p0 = p0;
        triangle->p1 = p1;
        triangle->p2 = p2;
        triangle->rules = rules;
        triangle->color = color;
        triangle->fill = fill;
        return triangle;
}