#ifndef UTIL_UTIL_H_
#define UTIL_UTIL_H_

#include <stdbool.h>
#include <stddef.h>

#include "../screen/screen.h"
#include "../shape/shape.h"

// Free allocated memory from pointer
void FreeMem(void *ptr);

// Free allocated memory from entire screen struct
void FreeScreen(Screen *screen);

// Free allocated memory from entire shapearray struct
void FreeShapeArray(ShapeArray *shapes);

// Free allocated memory from entire array of a given shape
void FreeArray(void **ptr, size_t size, const unsigned int type);

// Free allocated memory from entire shape struct
void FreeComponent(void *ptr, const unsigned int type);

// Allocate memory of a given bytesize
void *AllocMem(size_t size);

// Reallocate already allocated memory to a given bytesize
void ReAllocMem(void *ptr, size_t newSize);

// Output shape information via stdout stream
void OutputComponent(void *ptr, const unsigned int type);

// Returns the index of a given shape in a shape-array. Returns non-zero if the shape is not found
size_t GetShapeIndex(ShapeArray *shapes, void *shape, const unsigned int type);

bool IsEqual(float x, float y);
bool IsGreaterThanOrEqual(float x, float y);
bool IsLesserThanOrEqual(float x, float y);


#endif /* UTIL_UTIL_H_ */
