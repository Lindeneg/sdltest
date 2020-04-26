#include <math.h>

#include "../component/line.h"
#include "../util/util.h"

// https://en.wikipedia.org/wiki/Slope
float GetLineSlope(const Line *line) {
    float deltaX = line->p1->x - line->p0->x;
    if (fabsf(deltaX) < EPSILON) {
        return 0;
    }
    float deltaY = line->p1->y - line->p0->y;
    return deltaY / deltaX;
}

float GetLineLength(const Line *line) {
    return GetVectorDistance(line->p1, line->p0);
}

// https://en.wikipedia.org/wiki/Distance_from_a_point_to_a_line
float GetLineMinDistanceFrom(const Line *line, const Vector *point) {
    Vector *closetVec = CreateVector(0, 0);
    GetLineClosetPoint(closetVec, line, point);
    float distance = GetVectorDistance(point, closetVec);
    FreeMem(closetVec);
    return distance;
}

// https://en.wikipedia.org/wiki/Line%E2%80%93line_intersection
void GetLineClosetPoint(Vector *resultVec, const Line *line, const Vector *point) {
    Vector *p0P = CreateVector(0, 0);
    Vector *p0P1 = CreateVector(0, 0);
    SubtractVectors(p0P, point, line->p0);
    SubtractVectors(p0P1, line->p1, line->p0);
    float magnitude = GetVectorMagnitudeAlt(p0P1);
    float dotProduct = GetVectorDotProduct(p0P, p0P1);
    float t = dotProduct / magnitude;
    MultiplyVector(resultVec, p0P1, t);
    AddToVector(resultVec, line->p0);
    FreeMem(p0P);
    FreeMem(p0P1);
}

void GetLineMidPoint(Vector *resultVec, const Line *line) {
    float x = (line->p0->x + line->p1->x) / 2.0f;
    float y = (line->p0->y + line->p1->y) / 2.0f;
    resultVec->x = x;
    resultVec->y = y;
}

void RotateLine(Line *line, float angleInDegrees) {
    if (angleInDegrees <= 1) {
        float angle = angleInDegrees * PI / 180;
        RotateVector(line->p1, line->p0, angle);
    }
}

bool AreEqualLines(const Line *line, const Line *otherLine) {
    return (
        (AreEqualVectors(line->p0, otherLine->p0)) 
        && (AreEqualVectors(line->p1, otherLine->p1))
    );
}

Line * CreateLineFromPoints(
    float x0, float y0, 
    float x1, float y1, 
    float xv, float yv, 
    int collisionLayer, 
    const unsigned int color) 
    {
        Vector *p0 = CreateVector(x0, y0);
        Vector *p1 = CreateVector(x1, y1);
        return CreateLine(p0, p1, xv, yv, collisionLayer, color);
}

Line * CreateLine(
    Vector *p0, Vector *p1, 
    float xv, float yv, 
    int collisionLayer, 
    const unsigned int color) 
    {
        ShapeRules *rules = CreateNewShapeRule(xv, yv, collisionLayer);
        Line *line = (Line *)AllocMem(sizeof(Line));
        line->p0 = p0;
        line->p1 = p1;
        line->rules = rules;
        line->color = color;
        return line;
}
