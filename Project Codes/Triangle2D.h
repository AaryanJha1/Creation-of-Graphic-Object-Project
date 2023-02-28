#ifndef Triangle2D_h
#define Triangle2D_h

#include "Color.h"
#include "Vector2.h"
#include "Matrix.h"

struct Triangle3D{
    Vector4 v1;
    Vector4 v2;
    Vector4 v3;    
    Color c1;
    Color c2;
    Color c3;

    bool shouldDraw;

    Triangle3D();
    Triangle3D(Vector4 newV1, Vector4 newV2, Vector4 newV3, Color newC1, Color newC2, Color newC3);
    void transform(Matrix4 newVal);    
};

struct Triangle2D {
  Vector2 v1;
  Vector2 v2;
  Vector2 v3;
  Color c1;
  Color c2;
  Color c3;
  Triangle2D();
  Triangle2D(Vector2 vector1, Vector2 vector2, Vector2 vector3, Color color1,   Color color2, Color color3);
  void calculateBarycentricCoordinates(Vector2 P, float& lambda1, float& lambda2, float& lambda3);
  Triangle2D(Triangle3D newVal);
};



#endif