#include "../component/rectangle.h"
#include "../util/util.h"

float GetRectangleWidth(const Rectangle *rectangle) {
    return (rectangle->bottomRight->x - rectangle->topLeft->x + 1);
}

float GetRectangleHeight(const Rectangle *rectangle) {
    return (rectangle->bottomRight->y - rectangle->topLeft->y + 1);
}

void GetRectangleCenterVector(Vector *resultVec, const Rectangle *rectangle) {
    float width = GetRectangleWidth(rectangle);
    float height = GetRectangleHeight(rectangle);
    resultVec->x = rectangle->topLeft->x + width / 2.0f;
    resultVec->y = rectangle->topLeft->y + height / 2.0f;
}

void MoveRectangleToVector(Rectangle *rectangle, const Vector *vector) {
    float width = GetRectangleWidth(rectangle);
    float height = GetRectangleHeight(rectangle);
    rectangle->topLeft = vector;
    rectangle->bottomRight->x = vector->x + width - 1;
    rectangle->bottomRight->y = vector->y + height - 1;
}

bool IntersectsRectangle(const Rectangle *rectangle, const Rectangle *otherRect) {
    return !(otherRect->bottomRight->x < rectangle->topLeft->x     || 
             otherRect->topLeft->x     > rectangle->bottomRight->x ||
             otherRect->bottomRight->y < rectangle->topLeft->y     ||
             otherRect->topLeft->y     > rectangle->bottomRight->y);
}

bool ContainsVector(const Rectangle *rectangle, const Vector *vector) {
    return (
        ((vector->x >= rectangle->topLeft->x) && (vector->x <= rectangle->bottomRight->x)) &&
        ((vector->y >= rectangle->topLeft->y) && (vector->y <= rectangle->bottomRight->y))
    );
}

bool AreEqualRectangles(const Rectangle *rectangle, const Rectangle *otherRect) {
    return (
        (AreEqualVectors(rectangle->topLeft, otherRect->topLeft)) && 
        (AreEqualVectors(rectangle->bottomRight, otherRect->bottomRight))
    );
}

Rectangle * CreateRectangleFromPoints(
    float x0, float y0, 
    float x1, float y1,
    int xv, int yv,
    int collisionLayer,
    const unsigned int color, 
    bool fill) 
    {
        Vector *topLeft = CreateVector(x0, y0);
        Vector *bottomRight = CreateVector(x1, y1);
        return CreateRectangle(topLeft, bottomRight, xv, yv, collisionLayer, color, fill);
}

Rectangle * CreateRectangle(
    Vector *topLeft, Vector *bottomRight,
    int xv, int yv, int collisionLayer,
    const unsigned int color, 
    bool fill) 
    {
        ShapeRules *rules = CreateNewShapeRule(xv, yv, collisionLayer);
        Rectangle *rectangle = (Rectangle*)AllocMem(sizeof(Rectangle));
        rectangle->topLeft = topLeft;
        rectangle->bottomRight = bottomRight;
        rectangle->rules = rules;
        rectangle->color = color;
        rectangle->fill = fill;
        return rectangle;
}
