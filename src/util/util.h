#ifndef UTIL_UTIL_H_
#define UTIL_UTIL_H_

#include <stdbool.h>
#include <stddef.h>

#include "../screen/screen.h"
#include "../shape/shape.h"
#include "../component/line.h"

void FreeMem(void *ptr);
void FreeScreen(Screen *screen);
void FreeShapeArray(ShapeArray *shapes);
void FreeComponent(void *ptr, const unsigned int type);
void *AllocMem(size_t size);
void ReAllocMem(void *ptr, size_t newSize);
bool IsEqual(float x, float y);
bool IsGreaterThanOrEqual(float x, float y);
bool IsLesserThanOrEqual(float x, float y);


#endif /* UTIL_UTIL_H_ */

