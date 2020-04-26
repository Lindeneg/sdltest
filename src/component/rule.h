#ifndef COMPONENT_RULE_H_
#define COMPONENT_RULE_H_

struct s_shape_rules {
    float xVelocity;       // velocity on x-axis
    float yVelocity;       // velocity on y-axis
    int collisionLayer;    // collisionlayer (i.e player, enemey etc)
};
typedef struct s_shape_rules ShapeRules;

ShapeRules *CreateNewShapeRule(float xv, float yv, int collisionLayer);


#endif /* COMPONENT_RULE_H_ */
