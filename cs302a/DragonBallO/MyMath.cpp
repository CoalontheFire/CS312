#include "MyMath.h"
#include <iostream>
#include <stdio.h>
int MyMath::Abs(int num) {
	return num < 0 ? -num : num;
}

float MyMath::Abs(float num) {
	return num < 0.0f ? -num : num;
}

float MyMath::Lerp(float start, float end, float time) {
	if (time > 1) {
		return end;
	}

	float value = start + ((end - start) * time);
	return value;
}

int MyMath::Max(int leftNum, int rightNum) {
	return leftNum > rightNum ? leftNum : rightNum;
}
float MyMath::Max(float leftNum, float rightNum) {
	return leftNum > rightNum ? leftNum : rightNum;
}

int MyMath::Min(int leftNum, int rightNum) {
	return leftNum < rightNum ? leftNum : rightNum;
}
float MyMath::Min(float leftNum, float rightNum) {
	return leftNum < rightNum ? leftNum : rightNum;
}

int MyMath::Clamp(int value, int min, int max) {
	return value > max ? max :
		value < min ? min : value;
}
float MyMath::Clamp(float value, float min, float max) {
	return value > max ? max :
		value < min ? min : value;
}

float MyMath::Magnitude(Float2 value) {
	return  sqrt(pow(value.x, 2) + pow(value.y, 2));
}

MyMath::Float2 MyMath::Normalized(Float2 value) {
	return value / Magnitude(value);
}