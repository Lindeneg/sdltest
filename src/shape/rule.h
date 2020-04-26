#ifndef SHAPE_RULE_H_
#define SHAPE_RULE_H_

struct s_shape_rules {
    int xVelocity;       // velocity on x-axis
    int yVelocity;       // velocity on y-axis
    int collisionLayer;  // collisionlayer (i.e player, enemey etc)
};
typedef struct s_shape_rules ShapeRules;

ShapeRules *CreateNewShapeRule(int xv, int yv, int collisionLayer);


#endif /* SHAPE_RULE_H_ */
