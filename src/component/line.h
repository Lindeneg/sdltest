#ifndef COMPONENT_LINE_H_
#define COMPONENT_LINE_H_

#include <stdbool.h>

#include "../component/vector.h"

struct s_line {
    Vector *p0;
    Vector *p1;
    unsigned int color;
};
typedef struct s_line Line;

float GetLineSlope(const Line *line);
float GetLineLength(const Line *line);
float GetLineMinDistanceFrom(const Line *line, const Vector *point);
void GetLineClosetPoint(Vector *resultVec, const Line *line, const Vector *point);
void GetLineMidPoint(Vector *resultVec, const Line *line);
void RotateLine(Line *line, float angleInDegrees);
bool AreEqualLines(const Line *line, const Line *otherLine);
Line * CreateLineFromPoints(float x0, float y0, float x1, float y1, const unsigned int color);
Line * CreateLine(Vector *p0, Vector *p1, const unsigned int color);

#endif /* COMPONENT_LINE_H_ */
