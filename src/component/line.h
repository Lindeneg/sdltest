#ifndef COMPONENT_LINE_H_
#define COMPONENT_LINE_H_

#include <stdbool.h>

#include "../component/vector.h"
#include "../component/rule.h"

/*
A simple line representation. The two vectors represent the start and end, respectively.
The shape rules determine if the shape is sensitive to collision and movement.
*/
struct s_line {
    Vector *p0;
    Vector *p1;
    ShapeRules *rules;
    unsigned int color;
};
typedef struct s_line Line;

// Returns the slope of the line but returns 0 if trying to divide by zero
float GetLineSlope(const Line *line);

// Returns the length of the line, i.e the distance from p0 to p1
float GetLineLength(const Line *line);

// Returns the minimum distance from a given point on the line, to a point not on the line
float GetLineMinDistanceFrom(const Line *line, const Vector *point);

// Returns the closet point on the line to a point not on the line
void GetLineClosetPoint(Vector *resultVec, const Line *line, const Vector *point);

// Returns the center point of the line
void GetLineMidPoint(Vector *resultVec, const Line *line);

// Rotates the line in a clockwise direction
void RotateLine(Line *line, float angleInDegrees);

// Returns true if the two lines occupy the exact same area on the 2d plane
bool AreEqualLines(const Line *line, const Line *otherLine);

// Create line from individual coordinates on a 2d plane
Line * CreateLineFromPoints(
    float x0, float y0,      // start point
    float x1, float y1,      // end   point
    float xv,                // x-velocity
    float yv,                // y-velocity
    int collisionLayer,      // collisionType
    const unsigned int color // line color
);

// Create line from two existing vectors
Line * CreateLine(
    Vector *p0,              // start vector
    Vector *p1,              // end   vector
    float xv,                // x-velocity
    float yv,                // y-velocity
    int collisionLayer,      // collisionType
    const unsigned int color // line color
);


#endif /* COMPONENT_LINE_H_ */
