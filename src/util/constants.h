#ifndef UTIL_CONSTANTS_H_
#define UTIL_CONSTANTS_H_

#define EPSILON 0.00001
#define PI 3.14159265359
#define TWO_PI 2.0 * PI
#define MAX_POLYGON_CORNERS 30
#define TRIANGLE_SIZE 3
#define RECTANGLE_SIZE 4
#define CIRCLE_SIZE 6

// Constant representation of all available colors 
typedef enum {
    BLACK,
    LIGHT_BLUE,
    GRAY,
    DARK_BLUE,
    SILVER,
    DARK_GREEN,
    OLIVE,
    TEAL,
    BLUE,
    GREEN,
    PURPLE,
    LIGHT_RED,
    DARK_RED,
    RED,
    YELLOW,
    WHITE
} colors;

// Constant representation of all available shapes 
typedef enum {
    VECTOR,
    LINE,
    TRIANGLE,
    RECTANGLE,
    CIRCLE
} shapes;

// Constant representation of all available collision layers
typedef enum {
    PLAYER_COLLISION_LAYER,
    ENEMY_COLLISION_LAYER,
    NEUTRAL_COLLISION_LAYER
} collayers;

// Constant representation of all available collision types
typedef enum {
    NO_COLLISION,
    BORDER_COLLISION,
    PLAYER_PLAYER_COLLISION,
    PLAYER_ENEMY_COLLISION,
    ENEMY_PLAYER_COLLISION,
    ENEMY_ENEMY_COLLISION,
    PLAYER_NEUTRAL_COLLISION,
    ENEMY_NEUTRAL_COLLISION,
} coltypes;


#endif /* UTIL_CONSTANTS_H_ */
