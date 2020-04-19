#include "../component/circle.h"
#include "../util/util.h"

void MoveCircleToVector(Circle *circle, const Vector *vector) {
    circle->center = vector;
}

bool IntersectsCircle(const Circle *circle, const Circle *otherCircle) {
    return (GetVectorDistance(circle->center, otherCircle->center)) < (circle->radius + otherCircle->radius);
}

bool CircleContainsVector(const Circle *circle, const Vector* vector) {
    return IsLesserThanOrEqual((GetVectorDistance(circle->center, vector)), circle->radius);
}

bool AreEqualCircles(const Circle *circle, const Circle *otherCircle) {
    return ((AreEqualVectors(circle->center, otherCircle->center)) && (IsEqual(circle->radius, otherCircle->radius)));
}

Circle * CreateCircle(Vector *center, float radius, const unsigned int color, bool fill) {
    Circle *circle = (Circle*)AllocMem(sizeof(Circle));
    circle->center = center;
    circle->radius = radius;
    circle->color = color;
    circle->fill = fill;
    return circle;
}
