#include <stdlib.h>
#include <math.h>

#include "../component/vector.h"
#include "../util/util.h"


float GetVectorMagnitudeAlt(const Vector *vec) {
	return ((vec->x * vec->x) + (vec->y * vec->y));
}

float GetVectorMagnitude(const Vector *vec) {
	return sqrt(GetVectorMagnitudeAlt(vec));
}

float GetVectorDotProduct(const Vector *vec, const Vector *otherVec) {
	return ((vec->x * otherVec->x) + (vec->y * otherVec->y));
}

float GetVectorDistance(const Vector *vec, const Vector *otherVec) {
	Vector * diffVec = CreateVector(0, 0); 
	SubtractVectors(diffVec, otherVec, vec);
	float magnitude = GetVectorMagnitude(diffVec);
	FreeMem(diffVec);
	return magnitude;
}

float GetAngleBetweenVectors(const Vector *vec, const Vector *otherVec) {
	Vector * unitVecOne = CreateVector(0, 0); 
	Vector * unitVecTwo = CreateVector(0, 0);
	GetUnitVector(unitVecOne, vec);
	GetUnitVector(unitVecTwo, otherVec);
	float result = acosf(GetVectorDotProduct(unitVecOne, unitVecTwo));
	FreeMem(unitVecOne);
	FreeMem(unitVecTwo);
	return result;
}

void NegateVector(Vector *vec) {
	vec->x *= -1;
	vec->y *= -1;
}

void AddToVector(Vector *vec, const Vector *otherVec) {
	vec->x += otherVec->x;
	vec->y += otherVec->y;
}

void SubtractFromVector(Vector *vec, const Vector *otherVec) {
	vec->x -= otherVec->x;
	vec->y -= otherVec->y;
}

void ScaleVectorUp(Vector *vec, float scale) {
	vec->x *= scale;
	vec->y *= scale;
}

void ScaleVectorDown(Vector *vec, float scale) {
	vec->x /= scale;
	vec->y /= scale;
}

void RotateVector(Vector *vec, const Vector *refVec, float angle) {
	Vector * thisVec = CreateVector(
		vec->x,
		vec->y
	);
	float cosine = cosf(angle);
	float sine = sinf(angle);
	SubtractFromVector(thisVec, refVec);
	thisVec->x = (thisVec->x * cosine) - (thisVec->y * sine);
	thisVec->y = (thisVec->x * sine) + (thisVec->y * cosine);
	AddToVector(thisVec, refVec);
	vec->x = thisVec->x;
	vec->y = thisVec->y;
	FreeMem(thisVec);
}

void AddVectors(Vector *resultVec, const Vector *vec, const Vector *otherVec) {
	resultVec->x = vec->x + otherVec->x;
	resultVec->y = vec->y + otherVec->y;
}

void SubtractVectors(Vector *resultVec, const Vector *vec, const Vector *otherVec) {
	resultVec->x = vec->x - otherVec->x;
	resultVec->y = vec->y - otherVec->y;
}

void MultiplyVector(Vector *resultVec, const Vector *vec, float scale) {
	resultVec->x = vec->x * scale;
	resultVec->y = vec->y * scale;
}

void DivideVector(Vector *resultVec, const Vector *vec, float scale) {
	resultVec->x = vec->x / scale;
	resultVec->y = vec->y / scale;
}

void GetUnitVector(Vector *resultVec, const Vector *vec) {
	float magnitude = GetVectorMagnitude(vec);
	if (magnitude > EPSILON) {
		DivideVector(resultVec, vec, magnitude);
	}
}

void GetNormalizedVector(Vector *resultVec, const Vector *vec) {
	float magnitude = GetVectorMagnitude(vec);
	if (magnitude > EPSILON) {
		resultVec->x = vec->x;
		resultVec->y = vec->y;
		ScaleVectorDown(resultVec, magnitude);
	}
}

void GetRotatedVector(Vector *resultVec, const Vector *vec, const Vector *refVec, float angle) {
	float cosine = cosf(angle);
	float sine = sinf(angle);
	SubtractFromVector(resultVec, refVec);
	resultVec->x = (vec->x * cosine) - (vec->y * sine);
	resultVec->y = (vec->x * sine) + (vec->y * cosine);
	AddToVector(resultVec, refVec);
}

void GetProjectedVector(Vector *resultVec, const Vector *vec, const Vector *otherVec) {
	GetUnitVector(resultVec, otherVec);
	float dotProduct = GetVectorDotProduct(vec, resultVec);
	ScaleVectorUp(resultVec, dotProduct);
}

void GetReflectedVec(Vector *resultVec, const Vector *vec, const Vector *otherVec) {
	Vector * projectedVec = CreateVector(0, 0);
	GetProjectedVector(projectedVec, vec, otherVec);
	resultVec->x = (vec->x - 2 * projectedVec->x);
	resultVec->y = (vec->y - 2 * projectedVec->y);
	FreeMem(projectedVec);
}

bool AreEqualVectors(const Vector *vec, const Vector *otherVec) {
	return ((IsEqual(vec->x, otherVec->x)) && (IsEqual(vec->y, otherVec->y)));
}

Vector *CreateVector(float x, float y) {
	Vector * vec = AllocMem(sizeof(Vector));
	vec->x = x;
	vec->y = y;
	vec->type = VECTOR;
	return vec;
}
