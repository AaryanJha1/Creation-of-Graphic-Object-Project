#include "Color.h"
#include "Raster.h"
#include "Triangle2D.h"
#include "Vector2.h"
#include "Matrix.h"
#include <iostream>

using namespace std;

#define WIDTH 100
#define HEIGHT 100

int main() {
  Raster myRaster(WIDTH, HEIGHT, White);
  
  Model teapot= Model();
  //Model bunny = Model();
  teapot.readFromOBJFile("./teapot.obj", Red);
  //bunny.readFromOBJFile("./bunny.obj", Blue);
  
  Matrix4 modelMatrixTeapot = Translate3D(50, 50, -30) * RotateZ3D(45.0) * Scale3D(0.5, 0.5, 0.5);
  //Matrix4 modelMatrixBunny = Translate3D(70, 30, -60) * RotateZ3D(-20.0) * Scale3D(500, 500, 500);

  Vector4 eye(50,50,30,1);
  Vector4 spot(50,50,-30,1);
  teapot.performBackfaceCulling(eye, spot);

  //Matrix4 viewMatrix = LookAt(Vector4(50, 50, 30, 1), Vector4(50, 50, -40, 1), Vector4(0, 1, 0, 0));
  Matrix4 viewMatrix = LookAt(eye, spot, Vector4(0, 1, 0, 0));
  
  Matrix4 perspectiveMatrix = Perspective(70.0, myRaster.getWidth() / myRaster.getHeight(), 0.01, 88.5);

  Matrix4 viewportMatrix = Viewport(0, 0, myRaster.getWidth(), myRaster.getHeight());

  teapot.transform(perspectiveMatrix * viewMatrix * modelMatrixTeapot);
  //bunny.transform(perspectiveMatrix * viewMatrix * modelMatrixBunny);


  teapot.homogenize();
  //bunny.homogenize();

  teapot.transform(viewportMatrix);
  //bunny.transform(viewportMatrix);
  
  myRaster.drawModel(teapot);
  //myRaster.drawModel(bunny);
  
  myRaster.writeToPPM();

  //cin.get();
  //return 0;
}
