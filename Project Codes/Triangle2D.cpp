#include "Triangle2D.h"
#include "Color.h"
#include "Raster.h"
#include "Vector2.h"
#include "Matrix.h"

using namespace std;

Triangle2D::Triangle2D() {
  v1 = Vector2(0.0, 0.0);
  v2 = Vector2(0.0, 0.0);
  v3 = Vector2(0.0, 0.0);
  c1 = Black;
  c2 = Black;
  c3 = Black;
}

Triangle2D::Triangle2D(Vector2 vector1, Vector2 vector2, Vector2 vector3,
                       Color color1, Color color2, Color color3) {
  v1 = vector1;
  v2 = vector2;
  v3 = vector3;
  c1 = color1;
  c2 = color2;
  c3 = color3;
}

void Triangle2D::calculateBarycentricCoordinates(Vector2 P, float &lambda1,
                                                 float &lambda2,
                                                 float &lambda3) {

  lambda1 = determinant(v1 - v2, P - v2) / determinant(v1 - v2, v3 - v2);
  lambda2 = determinant(P - v2, v3 - v2) / determinant(v1 - v2, v3 - v2);
  lambda3 = 1.0 - lambda1 - lambda2;
}

Triangle3D::Triangle3D(){
    v1 = Vector4(0.0, 0.0, 0.0, 1.0);
    v2 = Vector4(0.0, 0.0, 0.0, 1.0);
    v3 = Vector4(0.0, 0.0, 0.0, 1.0);
    
    c1 = White;
		c2 = White;
		c3 = White;

    shouldDraw = true;

}

Triangle3D::Triangle3D(Vector4 newV1, Vector4 newV2, Vector4 newV3, Color newC1, Color newC2, Color newC3){
    v1 = newV1;
    v2 = newV2;
    v3 = newV3;
    
    c1 = newC1;
    c2 = newC2;
    c3 = newC3;
    shouldDraw = true;

}

void Triangle3D::transform(Matrix4 newVal){
     v1 = newVal * v1;
     v2 = newVal * v2;
     v3 = newVal * v3;
}

Triangle2D::Triangle2D(Triangle3D newVal){
		v1 = Vector2(newVal.v1.x, newVal.v1.y);
		v2 = Vector2(newVal.v2.x, newVal.v2.y);
		v3 = Vector2(newVal.v3.x, newVal.v3.y);

    c1 = newVal.c1;
    c2 = newVal.c2;
    c3 = newVal.c3;
}