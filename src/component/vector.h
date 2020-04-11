#ifndef COMPONENT_VECTOR_H_
#define COMPONENT_VECTOR_H_

#include <stdbool.h>

#include "../util/constants.h"

struct s_vector {
	float x;
	float y;
	unsigned int type;
};
typedef struct s_vector Vector;

float GetVectorMagnitudeAlt(const Vector *vec);
float GetVectorMagnitude(const Vector *vec);
float GetVectorDotProduct(const Vector *vec, const Vector *otherVec);
float GetVectorDistance(const Vector *vec, const Vector *otherVec);
float GetAngleBetweenVectors(const Vector *vec, const Vector *otherVec);

void NegateVector(Vector *vec);
void AddToVector(Vector *vec, const Vector *otherVec);
void SubtractFromVector(Vector *vec, const Vector *otherVec);
void ScaleVectorUp(Vector *vec, float scale);
void ScaleVectorDown(Vector *vec, float scale);
void RotateVector(Vector *vec, const Vector *refVec, float angle);

void AddVectors(Vector *resultVec, const Vector *vec, const Vector *otherVec);
void SubtractVectors(Vector *resultVec, const Vector *vec, const Vector *otherVec);
void MultiplyVector(Vector *resultVec, const Vector *vec, float scale);
void DivideVector(Vector *resultVec, const Vector *vec, float scale);
void GetUnitVector(Vector *resultVec, const Vector *vec);
void GetNormalizedVector(Vector *resultVec, const Vector *vec);
void GetRotatedVector(Vector *resultVec, const Vector *vec, const Vector *refVec, float angle);
void GetProjectedVector(Vector *resultVec, const Vector *vec, const Vector *otherVec);
void GetReflectedVec(Vector *resultVec, const Vector *vec, const Vector *otherVec);

bool AreEqualVectors(const Vector *vec, const Vector *otherVec);

Vector * CreateVector(float x, float y);


#endif /* COMPONENT_VECTOR_H_ */
