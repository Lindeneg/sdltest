#include <stddef.h>

#include "../shape/shape.h"
#include "../util/constants.h"
#include "../util/util.h"



ShapeArray *CreateEmptyShapeArray(void) {
    ShapeArray * shapeArray = (ShapeArray*)AllocMem(sizeof(ShapeArray));
    shapeArray->lineArray = NULL;
    return shapeArray;
}


int AddShapeToArray(ShapeArray *shapes, void *shape, const unsigned int type) {
    if (shapes) {
        if (type == LINE) {
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
            return 0;
        }
    }
    return -1;
}

// int RemoveShapeFromArray(ShapeArray *shapes, void *shape, const unsigned int type) {
//     if (shapes) {
//         if (type == LINE) {
//             Line *line = (Line*)shape;
//             for (size_t i = 0; i < shapes->lineArray->size; i++) {
//                 if (AreEqualLines(shapes->lineArray->lines[i], line)) {
//                     FreeMem(shapes->lineArray->lines[i]->p0);
//                     FreeMem(shapes->lineArray->lines[i]->p1);
//                     FreeMem(shapes->lineArray->lines[i]);
//                     ReAllocMem(shapes, (shapes->lineArray->size - 1) * sizeof(Line*));
//                     shapes->lineArray->size--;
//                     return 0;
//                 }
//             }
//         }
//     }
// }