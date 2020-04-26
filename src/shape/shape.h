#ifndef SHAPE_SHAPE_H_
#define SHAPE_SHAPE_H_

#include "../component/line.h"
#include "../component/triangle.h"
#include "../component/rectangle.h"
#include "../component/circle.h"

// Array of Line shapes
struct s_line_array {
    Line **lines;
    size_t size;
};
typedef struct s_line_array LineArray;

// Array of Triangle shapes
struct s_triangle_array {
    Triangle **triangles;
    size_t size;
};
typedef struct s_triangle_array TriangleArray;

// Array of Rectangle shapes
struct s_rectangle_array {
    Rectangle **rectangles;
    size_t size;
};
typedef struct s_rectangle_array RectangleArray;

// Array of Circle shapes
struct s_circle_array {
    Circle **circles;
    size_t size;
};
typedef struct s_circle_array CircleArray;

// Structure to contain all shape arrays
struct s_shape_array {
    LineArray *lineArray;
    TriangleArray *triangleArray;
    RectangleArray *rectangleArray;
    CircleArray *circleArray;
};
typedef struct s_shape_array ShapeArray;

// Create an empty ShapeArray 
ShapeArray *CreateEmptyShapeArray(void);

// Add a given shape to a given ShapeArray
int AddShapeToArray(ShapeArray *shapes, void *ptr, const unsigned int type);

// Remove a given shape from a given ShapeArray
int RemoveShapeFromArray(ShapeArray *shapes, void *shape, const unsigned int type);

// Handle Rules assosiated with each shape in the ShapeArrays
int HandleShapeArrayRules(ShapeArray *shapes);

#endif /* SHAPE_SHAPE_H_ */
