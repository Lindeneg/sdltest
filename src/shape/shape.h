#ifndef SHAPE_SHAPE_H_
#define SHAPE_SHAPE_H_

#include "../component/line.h"
#include "../component/triangle.h"
#include "../component/rectangle.h"
#include "../component/circle.h"

struct s_line_array {
    Line **lines;
    size_t size;
};
typedef struct s_line_array LineArray;

struct s_triangle_array {
    Triangle **triangles;
    size_t size;
};
typedef struct s_triangle_array TriangleArray;

struct s_rectangle_array {
    Rectangle **rectangles;
    size_t size;
};
typedef struct s_rectangle_array RectangleArray;

struct s_circle_array {
    Circle **circles;
    size_t size;
};
typedef struct s_circle_array CircleArray;

struct s_shape_array {
    LineArray *lineArray;
    TriangleArray *triangleArray;
    RectangleArray *rectangleArray;
    CircleArray *circleArray;
};
typedef struct s_shape_array ShapeArray;


ShapeArray *CreateEmptyShapeArray(void);
int AddShapeToArray(ShapeArray *shapes, void *ptr, const unsigned int type);
int RemoveShapeFromArray(ShapeArray *shapes, void *shape, const unsigned int type);

#endif /* SHAPE_SHAPE_H_ */