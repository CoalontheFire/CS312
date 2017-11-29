#pragma once
# include <math.h>

namespace MyMath {
	using UByte = unsigned char;
	struct Int2 {
		Int2() {}
		Int2(int x, int y) : x(x), y(y) {}
		int x{ 0 };
		int y{ 0 };

		Int2 operator+(Int2 right) {
			Int2 result(x - right.x, y + right.y);
			return result;
		}
		Int2 operator-(Int2 right) {
			Int2 result(x - right.x, y - right.y);
			return result;
		}
		Int2 operator/(int right) {
			Int2 value(x / right, y / right);
			return value;
		}
		bool operator==(Int2 right) {
			if (x == right.x && y == right.y) {
				return true;
			}
			else {
				return false;
			}
		}
		bool operator!=(Int2 right) {
			if (x == right.x && y == right.y) {
				return false;
			}
			else {
				return true;
			}
		}
	};
	struct Float2 {
		Float2() {}
		Float2(float x, float y) : x(x), y(y) {}
		float x{ 0.f };
		float y{ 0.f };

		Float2 operator*(float right) {
			Float2 value(x *right, y * right);
			return value;
		}
		Float2 operator/(float right) {
			Float2 value(x / right, y / right);
			return value;
		}
		void operator+=(Float2 right) {
			x += right.x;
			y += right.y;
		}
		bool operator==(Float2 right) {
			if (x == right.x && y == right.y) {
				return true;
			}
			else {
				return false;
			}
		}
		bool operator!=(Float2 right) {
			if (x == right.x && y == right.y) {
				return false;
			}
			else {
				return true;
			}
		}
		Float2 operator+(Float2 right) {
			Float2 result(x - right.x, y + right.y);
			return result;
		}
		Float2 operator-(Float2 right) {
			Float2 result(x - right.x, y - right.y);
			return result;
		}
	};

	struct RectBoundary {
		RectBoundary() {}
		RectBoundary(float l, float r, float t, float b) : left{ l }, right{ r }, top{ t }, bottom{ b } {}
		float left{ 0 };
		float right{ 0 };
		float top{ 0 };
		float bottom{ 0 };
	};

	int Abs(int num);
	float Abs(float num);

	int Max(int leftNum, int rightNum);
	float Max(float leftNum, float rightNum);

	int Min(int leftNum, int rightNum);
	float Min(float leftNum, float rightNum);

	int Clamp(int value, int min, int max);
	float Clamp(float value, float min, float max);

	float Magnitude(MyMath::Float2 value);

	MyMath::Float2 Normalized(MyMath::Float2 value);

	float Lerp(float start, float end, float time);

}