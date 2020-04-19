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

bool TriangleContainsVector(const Triangle *triangle, const Vector *vector) {
    bool result;
    Triangle *t1 = CreateTriangle(vector, triangle->p1, triangle->p2, BLACK, false);
    Triangle *t2 = CreateTriangle(triangle->p0, vector, triangle->p2, BLACK, false);
    Triangle *t3 = CreateTriangle(triangle->p0, triangle->p1, vector, BLACK, false);
    float area = GetTriangleArea(triangle);
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

Triangle * CreateTriangle(Vector *p0, Vector *p1, Vector *p2, const unsigned int color, bool fill) {
    Triangle *triangle = (Triangle*)AllocMem(sizeof(Triangle));
    triangle->p0 = p0;
    triangle->p1 = p1;
    triangle->p2 = p2;
    triangle->color = color;
    triangle->fill = fill;
    return triangle;
}