#ifndef VECTOR2_H_
#define VECTOR2_H_

#include <iostream>

using namespace std;

struct Vector2 {
  float x, y;
  Vector2();
  Vector2(float newX, float newY);
  Vector2 operator*(float newVal);
  Vector2 operator+(Vector2& newVal);
  Vector2 operator-(Vector2& newVal);
  float magnitude();
  float dot(Vector2 newNumber);
  Vector2 normalize();
  Vector2 perpendicular();
};

struct Vector4{
    float x, y, z, w;
    Vector4();
    Vector4(float newX, float newY, float newZ, float newW);
    Vector4 operator+(Vector4& newVal);
    Vector4 operator-(Vector4& newVal);
    Vector4 operator*(float newVal);
    float magnitude();
    Vector4 normalize();
    float dot(Vector4 newNumber);
		Vector4 cross(Vector4 newNumber);

};

float determinant(Vector2 a, Vector2 b);

#endif 
