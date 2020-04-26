#include <malloc.h>
#include <stddef.h>
#include <stdio.h>

#include "../component/rule.h"

ShapeRules *CreateNewShapeRule(float xv, float yv, int collisionLayer) {
    ShapeRules * rules = NULL;
    rules = (ShapeRules*)malloc(sizeof(ShapeRules));
    if (rules == NULL) {
		printf("\nAllocMemError: Out of Memory, cannot allocate %d bytes", sizeof(ShapeRules));
		exit(-1);
    }
    rules->xVelocity = xv;
    rules->yVelocity = yv;
    rules->collisionLayer = collisionLayer;
    return rules;
}
