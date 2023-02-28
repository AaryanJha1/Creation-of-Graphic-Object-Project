#ifndef Matrix_h
#define Matrix_h
#include "Vector2.h"

struct Matrix4{
  float ix, jx, kx, ox, iy, jy, ky, oy, iz, jz, kz, oz, iw, jw, kw, ow;
  Matrix4();
  Matrix4(float new_ix, float new_jx, float new_kx, float new_ox,
    float new_iy, float new_jy, float new_ky, float new_oy,
    float new_iz, float new_jz, float new_kz, float new_oz,
    float new_iw, float new_jw, float new_kw, float new_ow);
  Vector4 operator*(Vector4 newVal);
  Matrix4 operator*(Matrix4 newVal);  
  void print();
};

Matrix4 Translate3D(float tX, float tY, float tZ);  
Matrix4 Scale3D(float sX, float sY, float sZ);
Matrix4 RotateX3D(float degrees);
Matrix4 RotateY3D(float degrees);
Matrix4 RotateZ3D(float degrees);
Matrix4 Rotate3D(float degreesX, float degreesY, float degreesZ);
Matrix4 Rotate3D(float degrees, Vector4 vec);
Matrix4 LookAt(Vector4 eye, Vector4 spot, Vector4 up);
Matrix4 Orthographic(float minX, float maxX, float minY, float maxY, float minZ, float maxZ);
Matrix4 Perspective(float fovY, float aspect, float nearZ, float farZ);
Matrix4 Viewport(float x, float y, float width, float height);




#endif