#ifndef SHAPE_SHAPE_H_
#define SHAPE_SHAPE_H_

#include "../component/line.h"


struct s_line_array {
    Line **lines;
    size_t size;
};
typedef struct s_line_array LineArray;


struct s_shape_array {
    LineArray *lineArray;
};
typedef struct s_shape_array ShapeArray;


ShapeArray *CreateEmptyShapeArray(void);

int AddShapeToArray(ShapeArray *shapes, void *ptr, const unsigned int type);
//int RemoveShapeFromArray(ShapeArray *shapes, void *shape, const unsigned int type);

#endif /* SHAPE_SHAPE_H_ */