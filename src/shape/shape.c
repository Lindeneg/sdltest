#include <stddef.h>
#include <stdio.h>

#include "../shape/shape.h"
#include "../util/constants.h"
#include "../util/util.h"


static int HandleShapeMovement(void *shape, const unsigned int type) {
    if (shape) {
        if (type == LINE) {
            Line *line = (Line*)shape;
            line->p0->x += line->rules->xVelocity;
            line->p0->y += line->rules->yVelocity;
            line->p1->x += line->rules->xVelocity;
            line->p1->y += line->rules->yVelocity;
        }
        if (type == TRIANGLE) {
            Triangle *triangle = (Triangle*)shape;
            triangle->p0->x += triangle->rules->xVelocity;
            triangle->p0->y += triangle->rules->yVelocity;
            triangle->p1->x += triangle->rules->xVelocity;
            triangle->p1->y += triangle->rules->yVelocity;
            triangle->p2->x += triangle->rules->xVelocity;
            triangle->p2->y += triangle->rules->yVelocity;

        }
        if (type == RECTANGLE) {
            Rectangle *rectangle = (Rectangle*)shape;
            rectangle->topLeft->x += rectangle->rules->xVelocity;
            rectangle->topLeft->y += rectangle->rules->yVelocity;
            rectangle->bottomRight->x += rectangle->rules->xVelocity;
            rectangle->bottomRight->y += rectangle->rules->yVelocity;
        }
        if (type == CIRCLE) {
            Circle *circle = (Circle*)shape;
            circle->center->x += circle->rules->xVelocity;
            circle->center->y += circle->rules->yVelocity;
        }
        return 0;
    }
    return -1;
}

static int HandleShapeCollision(void *shape, const unsigned int shapeType, const unsigned int collisionType) {
    switch (collisionType) {
    case NO_COLLISION:
        return -1;
    // TODO: All collision cases
    default:
        return -1;
    }
    return 0;
}

static int GetCollisionType(void *shape, const unsigned int type, const ShapeArray *shapes) {
    // TODO:
    // Check Boundaries
    // Check Collision with Other Shapes
    // Return the First Collision Type (i.e boundary or another shape)
    // If no collision is detected, return NO_COLLISION
    unsigned int collisionType = NO_COLLISION;
    if (type == LINE) {
        Line *line = (Line*)shape;
    }
    if (type == TRIANGLE) {
        Triangle *triangle = (Triangle*)shape;
    }
    if (type == RECTANGLE) {
        Rectangle *rectangle = (Rectangle*)shape;
    }
    if (type == CIRCLE) {
        Circle *circle = (Circle*)shape;
    }
    return collisionType;
}


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

int HandleShapeArrayRules(ShapeArray *shapes) {
	if (shapes) {
		if ((shapes->lineArray) && (shapes->lineArray->size >= 1)) {
			for (size_t i = 0; i < shapes->lineArray->size; i++) {
				if (shapes->lineArray->lines[i]) {
                    HandleShapeCollision(
                        shapes->lineArray->lines[i], 
                        LINE, GetCollisionType(shapes->lineArray->lines[i], LINE, shapes)
                    );
				}
			}
		}
		if ((shapes->triangleArray) && (shapes->triangleArray->size >= 1)) {
			for (size_t i = 0; i < shapes->triangleArray->size; i++) {
				if (shapes->triangleArray->triangles[i]) {
                    HandleShapeCollision(shapes->triangleArray->triangles[i], TRIANGLE, GetCollisionType(shapes->triangleArray->triangles[i], TRIANGLE, shapes));
				}
			}
		}
		if ((shapes->rectangleArray) && (shapes->rectangleArray->size >= 1)) {
			for (size_t i = 0; i < shapes->rectangleArray->size; i++) {
				if (shapes->rectangleArray->rectangles[i]) {
                    HandleShapeCollision(shapes->rectangleArray->rectangles[i], RECTANGLE, GetCollisionType(shapes->rectangleArray->rectangles[i], RECTANGLE, shapes)
                    );
				}
			}
		}
		if ((shapes->circleArray) && (shapes->circleArray->size >= 1)) {
			for (size_t i = 0; i < shapes->circleArray->size; i++) {
				if (shapes->circleArray->circles[i]) {
                    HandleShapeCollision(shapes->circleArray->circles[i], CIRCLE, GetCollisionType(shapes->circleArray->circles[i], CIRCLE, shapes));
				}
			}
		}
        return 0;
	}
    return -1;
}
