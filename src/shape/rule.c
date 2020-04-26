#include "../shape/rule.h"
#include "../util/util.h"

ShapeRules *CreateNewShapeRule(int xv, int yv, int collisionLayer) {
    ShapeRules * rules = (ShapeRules*)AllocMem(sizeof(ShapeRules));
    rules->xVelocity = xv;
    rules->yVelocity = yv;
    rules->collisionLayer = collisionLayer;
    return rules;
}
