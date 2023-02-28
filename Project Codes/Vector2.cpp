#include "Vector2.h"
#include <math.h>
using namespace std;

Vector2::Vector2() {
  x = 0.0;
  y = 0.0;
}

Vector2::Vector2(float newX, float newY) {
  x = newX;
  y = newY;
}

Vector2 Vector2::operator*(float newVal) {
	Vector2 ans;
  ans.x=newVal*this->x ;
  ans.y= newVal*this->y ;
  return ans;
}

Vector2 Vector2::operator+(Vector2 &newVal) {
  Vector2 ans = Vector2(x + newVal.x, y + newVal.y);
  return ans;
}

Vector2 Vector2::operator-(Vector2 &newVal) {
  Vector2 ans = Vector2(x - newVal.x, y - newVal.y);
  return ans;
}

float determinant(Vector2 a, Vector2 b) {
  float ans = (b.x * a.y) - (a.x * b.y);
  return ans;
}

float Vector2::magnitude() {
  float ans = sqrt(pow(x, 2) + pow(y, 2));
  return ans;
}

float Vector2::dot(Vector2 newNumber) {
  float ans = (x * newNumber.x) + (y * newNumber.y);
  return ans;
}

Vector2 Vector2::normalize() {
  float newMag = 1 / magnitude();
  Vector2 ans;
  ans.x = x * newMag;
  ans.y = y * newMag;
  return ans;
}

Vector2 Vector2::perpendicular() {
  Vector2 ans;
  ans.x = -y;
  ans.y = x;
  return ans;
}

Vector4::Vector4(){
    x = 0.0;
    y = 0.0;
    z = 0.0;
    w = 0.0;
}

Vector4::Vector4(float newX, float newY, float newZ, float newW){
    x = newX;
    y = newY;
    z = newZ;
    w = newW;
}

Vector4 Vector4::operator*(float newVal){ 
  Vector4 ans;
  ans.x = newVal*this->x ;
  ans.y = newVal*this->y ;
  ans.z = newVal*this->z ;
  ans.w = newVal*this->w ;
  return ans;
}

Vector4 Vector4::operator+(Vector4& newVal){
    Vector4 ans = Vector4(x + newVal.x, y + newVal.y, z + newVal.z, w + newVal.w);
    return ans;
}

Vector4 Vector4::operator-(Vector4& newVal){
    Vector4 ans = Vector4(x - newVal.x, y - newVal.y, z - newVal.z, w - newVal.w);
    return ans;
}

float Vector4::magnitude(){
    float ans = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
    return ans;
}

Vector4 Vector4::normalize() {
    Vector4 ans;
    float newMag = 1 / magnitude();
    ans.x = newMag * x;
    ans.y = newMag * y;
    ans.z = newMag * z;
    ans.w = newMag * w;
    return ans;
}

float Vector4::dot(Vector4 newNumber) {
    float ans = (x * newNumber.x) + (y * newNumber.y) + (z * newNumber.z) + (w * newNumber.w);
    return ans;
}

Vector4 Vector4::cross(Vector4 newNumber)
{
	Vector4 cross_product = Vector4(y*newNumber.z - z*newNumber.y, 
                                 z*newNumber.x - x*newNumber.z, 
                                 x*newNumber.y - y*newNumber.x, 
                                 1);
	return cross_product;
}
