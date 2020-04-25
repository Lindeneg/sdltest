#include <stddef.h>
#include <stdio.h>

#include "../shape/shape.h"
#include "../util/constants.h"
#include "../util/util.h"


static int mRemoveLine(ShapeArray *shapes, void *shape) {
    size_t targetIndex = GetShapeIndex(shapes, shape, LINE);
    if (targetIndex >= 0) {
        if (shapes->lineArray->size == 1) {
            FreeArray(shapes->lineArray->lines, shapes->lineArray->size, LINE);
            shapes->lineArray->size = 0;
        } else {
            FreeComponent(shapes->lineArray->lines[targetIndex], LINE);
            for (size_t i = targetIndex + 1; i < shapes->lineArray->size; i++) {
                shapes->lineArray->lines[i-1] = shapes->lineArray->lines[i];
            }
            if (shapes->lineArray->size > 1) {
                ReAllocMem(shapes->lineArray->lines, (shapes->lineArray->size - 1) * sizeof(Line*));
            }
            shapes->lineArray->size--;
        }
        return 0;
    }
    printf("\nRemoveLineError: could not remove %p with index %d", shape, targetIndex);
    return -1;
}

static void mAddLine(ShapeArray *shapes, void *shape) {
    Line *line = (Line*)shape;
    if (!(shapes->lineArray)) {
        shapes->lineArray = (LineArray*)AllocMem(sizeof(LineArray));
        shapes->lineArray->lines = (Line**)AllocMem(sizeof(Line*));
        shapes->lineArray->lines[0] = line;
        shapes->lineArray->size = 1;
    } else {
        ReAllocMem(shapes->lineArray->lines, (shapes->lineArray->size + 1) * sizeof(Line*));
        shapes->lineArray->size++;
        shapes->lineArray->lines[(shapes->lineArray->size - 1)] = line;
    }
}

static int mRemoveTriangle(ShapeArray *shapes, void *shape) {
    size_t targetIndex = GetShapeIndex(shapes, shape, TRIANGLE);
    if (targetIndex >= 0) {
        if (shapes->triangleArray->size == 1) {
            FreeArray(shapes->triangleArray->triangles, shapes->triangleArray->size, TRIANGLE);
            shapes->triangleArray->size = 0;
        } else {
            FreeComponent(shapes->triangleArray->triangles[targetIndex], TRIANGLE);
            for (size_t i = targetIndex + 1; i < shapes->triangleArray->size; i++) {
                shapes->triangleArray->triangles[i-1] = shapes->triangleArray->triangles[i];
            }
            if (shapes->triangleArray->size > 1) {
                ReAllocMem(shapes->triangleArray->triangles, (shapes->triangleArray->size - 1) * sizeof(Triangle*));
            }
            shapes->triangleArray->size--;
        }
        return 0;
    }
    printf("\nRemoveTriangle: could not remove %p with index %d", shape, targetIndex);
    return -1;
}

static void mAddTriangle(ShapeArray *shapes, void *shape) {
    Triangle *triangle = (Triangle*)shape;
    if (!(shapes->triangleArray)) {
        shapes->triangleArray = (TriangleArray*)AllocMem(sizeof(TriangleArray));
        shapes->triangleArray->triangles = (Triangle**)AllocMem(sizeof(Triangle*));
        shapes->triangleArray->triangles[0] = triangle;
        shapes->triangleArray->size = 1;
    } else {
        ReAllocMem(shapes->triangleArray->triangles, (shapes->triangleArray->size + 1) * sizeof(Triangle*));
        shapes->triangleArray->size++;
        shapes->triangleArray->triangles[(shapes->triangleArray->size - 1)] = triangle;
    }
}

static int mRemoveRectangle(ShapeArray *shapes, void *shape) {
    size_t targetIndex = GetShapeIndex(shapes, shape, RECTANGLE);
    if (targetIndex >= 0) {
        if (shapes->rectangleArray->size == 1) {
            FreeArray(shapes->rectangleArray->rectangles, shapes->rectangleArray->size, RECTANGLE);
            shapes->rectangleArray->size = 0;
        } else {
            FreeComponent(shapes->rectangleArray->rectangles[targetIndex], RECTANGLE);
            for (size_t i = targetIndex + 1; i < shapes->rectangleArray->size; i++) {
                shapes->rectangleArray->rectangles[i-1] = shapes->rectangleArray->rectangles[i];
            }
            if (shapes->rectangleArray->size > 1) {
                ReAllocMem(shapes->rectangleArray->rectangles, (shapes->rectangleArray->size - 1) * sizeof(Rectangle*));
            }
            shapes->rectangleArray->size--;
        }
        return 0;
    }
    printf("\nRemoveRectangle: could not remove %p with index %d", shape, targetIndex);
    return -1;
}

static void mAddRectangle(ShapeArray *shapes, void *shape) {
    Rectangle *rectangle = (Rectangle*)shape;
    if (!(shapes->rectangleArray)) {
        shapes->rectangleArray = (RectangleArray*)AllocMem(sizeof(RectangleArray));
        shapes->rectangleArray->rectangles = (Rectangle**)AllocMem(sizeof(Rectangle*));
        shapes->rectangleArray->rectangles[0] = rectangle;
        shapes->rectangleArray->size = 1;
    } else {
        ReAllocMem(shapes->rectangleArray->rectangles, (shapes->rectangleArray->size + 1) * sizeof(Rectangle*));
        shapes->rectangleArray->size++;
        shapes->rectangleArray->rectangles[(shapes->rectangleArray->size - 1)] = rectangle;
    }
}

static int mRemoveCircle(ShapeArray *shapes, void *shape) {
    size_t targetIndex = GetShapeIndex(shapes, shape, CIRCLE);
    if (targetIndex >= 0) {
        if (shapes->circleArray->size == 1) {
            FreeArray(shapes->circleArray->circles, shapes->circleArray->size, CIRCLE);
            shapes->circleArray->size = 0;
        } else {
            FreeComponent(shapes->circleArray->circles[targetIndex], CIRCLE);
            for (size_t i = targetIndex + 1; i < shapes->circleArray->size; i++) {
                shapes->circleArray->circles[i-1] = shapes->circleArray->circles[i];
            }
            if (shapes->circleArray->size > 1) {
                ReAllocMem(shapes->circleArray->circles, (shapes->circleArray->size - 1) * sizeof(Circle*));
            }
            shapes->circleArray->size--;
        }
        return 0;
    }
    printf("\nRemoveCircle: could not remove %p with index %d", shape, targetIndex);
    return -1;
}

static void mAddCircle(ShapeArray *shapes, void *shape) {
    Circle *circle = (Circle*)shape;
    if (!(shapes->circleArray)) {
        shapes->circleArray = (CircleArray*)AllocMem(sizeof(CircleArray));
        shapes->circleArray->circles = (Circle**)AllocMem(sizeof(Circle*));
        shapes->circleArray->circles[0] = circle;
        shapes->circleArray->size = 1;
    } else {
        ReAllocMem(shapes->circleArray->circles, (shapes->circleArray->size + 1) * sizeof(Circle*));
        shapes->circleArray->size++;
        shapes->circleArray->circles[(shapes->circleArray->size - 1)] = circle;
    }
}

ShapeArray *CreateEmptyShapeArray(void) {
    ShapeArray * shapeArray = (ShapeArray*)AllocMem(sizeof(ShapeArray));
    shapeArray->lineArray = NULL;
    shapeArray->triangleArray = NULL;
    shapeArray->rectangleArray = NULL;
    shapeArray->circleArray = NULL;
    return shapeArray;
}

int AddShapeToArray(ShapeArray *shapes, void *shape, const unsigned int type) {
    if (shapes) {
        switch(type) {
            case LINE:
                mAddLine(shapes, shape);
                break;
            case TRIANGLE:
                mAddTriangle(shapes, shape);
                break;
            case RECTANGLE:
                mAddRectangle(shapes, shape);
                break;
            case CIRCLE:
                mAddCircle(shapes, shape);
                break;
            default:
                return -1;
        }
        return 0;
    }
}

int RemoveShapeFromArray(ShapeArray *shapes, void *shape, const unsigned int type) {
    if (shapes) {
        if ((type == LINE) && (shapes->lineArray) && (shapes->lineArray->size > 0)) {
            return mRemoveLine(shapes, shape);
        }
        if ((type == TRIANGLE) && (shapes->triangleArray) && (shapes->triangleArray->size > 0)) {
            return mRemoveTriangle(shapes, shape);
        }
        if ((type == RECTANGLE) && (shapes->rectangleArray) && (shapes->rectangleArray->size > 0)) {
            return mRemoveRectangle(shapes, shape);
        }
        if ((type == CIRCLE) && (shapes->circleArray) && (shapes->circleArray->size > 0)) {
            return mRemoveCircle(shapes, shape);
        }
    }
    printf("\nRemoveShapeFromArrayError: could not remove shape %p as ShapeArray %p returns a falsy value", shape, shapes);
    return -1;
}
