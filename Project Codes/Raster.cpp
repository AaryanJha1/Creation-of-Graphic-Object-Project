#include "Raster.h"
#include "Vector2.h"
#include <fstream>
#include <math.h>
#include <limits>

using namespace std;

Raster::Raster() {
  width = 0;
  height = 0;
  pixels = NULL;
  depthPixels = NULL;
}

Raster::Raster(int pWidth, int pHeight, Color pFillColor) {
  width = pWidth;
  height = pHeight;
  pixels = new Color[width * height];
  depthPixels = new float[width * height];
  for (int i = 0; i < width * height; i++) {
    pixels[i] = pFillColor;
    depthPixels[i] = numeric_limits<float>::max();
  }
}

Raster::~Raster() {
  delete[] pixels;
  delete[] depthPixels;
}

int Raster::getWidth() { return width; }

int Raster::getHeight() { return height; }

Color Raster::getColorPixel(int x, int y) {
  if (x < width && y < height && x >= 0 && y >= 0) {
    int calculation = ((height - y - 1) * width + x);

    return pixels[calculation];
  } else {
    return Black;
  }
}

void Raster::setColorPixel(int x, int y, Color pFillColor) {
  if (x < width && y < height && x >= 0 && y >= 0) {
    int calculation = ((height - 1 - y) * width + x);

    pixels[calculation] = pFillColor;
  }
}

float Raster::getDepthPixel(int x, int y) {
    if (x < width && y < height && x >= 0 && y >= 0) {
        int calculation = ((height - 1 - y) * width + x);

        return depthPixels[calculation];
    }
    else {
        return numeric_limits<float>::max();
    }
}

void Raster::setDepthPixel(int x, int y, float depth)
{
    if (x < width && y < height && x >= 0 && y >= 0) {
        int calculation = ((height - 1 - y) * width + x);

        depthPixels[calculation] = depth;

    }
}


void Raster::writeToPPM() {
  ofstream newfile;
  newfile.open("FRAMEBUFFER.ppm");
  newfile << "P3" << endl;
  newfile << width << " " << height << endl;
  newfile << "255" << endl;
  Color start;
  for (int i = height - 1; i >= 0; i--) {
    for (int j = 0; j < width; j++) {
      start = getColorPixel(j, i);
      newfile << (int)round(start.red * 255) << " "
              << (int)round(start.green * 255) << " "
              << (int)round(start.blue * 255) << " ";
    }
    newfile << "\n";
  }

  newfile.close();
}

void Raster::clear(Color pFillColor) {
	for (int i = 0; i < width * height; i++) {
		pixels[i] = pFillColor;
	}
}

void Raster::clear(float depth) {
    for (int i = 0; i < width * height; i++) {
        depthPixels[i] = depth;
    }
}

void Raster::drawLine_DDA(float x1, float y1, float x2, float y2, Color fillColor) {

  if (x2 == x1) {
    if (y2 < y1) {
      float temp = y1;
      y1 = y2;
      y2 = temp;
      for (int y = y1; y <= y2; y++) {
        setColorPixel(round(x1), y, fillColor);
      }
    } else {
      for (int y = y1; y <= y2; y++) {
        setColorPixel(round(x1), y, fillColor);
      }
    }
    return;
  }

  if (x2 < x1) {
    float temp = x1;
    x1 = x2;
    x2 = temp;
    temp = y1;
    y1 = y2;
    y2 = temp;
  }

  float slopeOne = (y2 - y1) / (x2 - x1);

  if (slopeOne >= -1 && slopeOne <= 1) {
    float y = y1;
    for (int x = x1; x <= x2; x++) {
      if (x < width && y < height && x >= 0 && y >= 0) {
        setColorPixel(x, round(y), fillColor);
        y += slopeOne;
      }
    }
  } else if (slopeOne <= -1) {
    if (x2 > x1) {
      float temp = x2;
      x2 = x1;
      x1 = temp;
      temp = y2;
      y2 = y1;
      y1 = temp;
    }
    float x = x2;
    float slopeTwo = (x1 - x2) / (y1 - y2);
    for (int y = y2; y >= y1; y--) {
      if (x < width && y < height && x >= 0 && y >= 0) {
        setColorPixel(round(x), y, fillColor);
        x -= slopeTwo;
      }
    }
  }

  else {
    float x = x2;
    float slopeTwo = (x1 - x2) / (y1 - y2);
    for (int y = y2; y >= y1; y--) {
      if (x < width && y < height && x >= 0 && y >= 0) {
        setColorPixel(round(x), y, fillColor);
        x -= slopeTwo;
      }
    }
  }
}

void Raster::drawLine_DDA_Interpolated(float x1, float y1, float x2, float y2, Color color1, Color color2) {

    Vector2 vector1(x1, y1);
    Vector2 vector2(x2, y2);
    Vector2 vector3 = vector2 - vector1;
    float vector3_magnitude = vector3.magnitude();
    
    if (x2 == x1) {
        if (y2 < y1) {
            float smaller = y1;
            y1 = y2;
            y2 = smaller;
            for (int y = y1; y <= y2; y++) {
                Vector2 vector4(x1, y);
                Vector2 vector5 =  vector4- vector1;
                float vector2_magnitude = vector5.magnitude();
                float ratio = vector2_magnitude / vector3_magnitude;
                setColorPixel(round(x1), y, ((color2 * ratio)+ (color1 * (1.0 - ratio))));
            }
        }
        else {
            for (int y = y1; y <= y2; y++) {   
               Vector2 vector4(x1, y);
                Vector2 vector5 = vector4 - vector1;
                float vector2_magnitude = vector5.magnitude();
                float ratio = vector2_magnitude / vector3_magnitude;
                setColorPixel(round(x1), y, ((color2 * ratio)+ (color1 * (1.0 - ratio))));
            }
        }
        return;
    }
 
    if (x2 < x1) {
        float temp = x1;
        x1 = x2;
        x2 = temp;
        temp = y1;
        y1 = y2;
        y2 = temp;
    }

    float slope = (y2 - y1) / (x2 - x1);

    if (slope >= -1 && slope <= 1)
    {
        float y = y1;
        for (int x = x1; x <= x2; x++) {
            if (x < width && y < height && x >= 0 && y >= 0) {
                Vector2 vector4(x, y);
                Vector2 vector5 = vector4 - vector1;
                float vector2_magnitude = vector5.magnitude();
                float ratio = vector2_magnitude / vector3_magnitude;
                setColorPixel(x, round(y), ((color2 * ratio)+ (color1 * (1.0 - ratio))));
                y= y+slope;
            }
        }
    }
    else if (slope <= -1)
    {
        if (x2 > x1) 
        {
            float temp = x2;
            x2 = x1;
            x1 = temp;
            temp = y2;
            y2 = y1;
            y1 = temp;
        }
        float x = x2;
        float slope = (x2 - x1) / (y2 - y1);
        for (int y = y2; y >= y1; y--) {
            if (x < width && y < height && x >= 0 && y >= 0) {
                Vector2 vector4(x, y);
                Vector2 vector5 = vector4 - vector1;
                float vector2_magnitude = vector5.magnitude();
                float ratio = vector2_magnitude / vector3_magnitude;
                setColorPixel(round(x), y, ((color2 * ratio)+ (color1 * (1.0 - ratio))));
                x = x- slope;
            }
        }
    }

    else
    {
        float x = x2;
        float slope = (x2-x1) / (y2-y1);
        for (int y = y2; y >= y1; y--) {
            if (x < width && y < height && x >= 0 && y >= 0) {
                Vector2 vector4(x, y);
                Vector2 vector5 = vector4 - vector1;
                float vector2_magnitude = vector5.magnitude();
                float ratio = vector2_magnitude / vector3_magnitude;
                setColorPixel(round(x), y, ((color2 * ratio)+ (color1 * (1.0 - ratio))));
                x= x-slope;
            }
        }
    }
}

void Raster::drawTriangle_DotProduct(Triangle2D t1) {
    float sortX[] = { t1.v1.x, t1.v2.x, t1.v3.x };
    float sortY[] = { t1.v1.y, t1.v2.y, t1.v3.y };
    float xMax = sortX[0];
    float xMin = sortX[0];
    float yMax = sortY[0];
    float yMin = sortY[0];
  
    if (t1.v1.x == t1.v2.x || t1.v2.x == t1.v3.x || t1.v1.x == t1.v3.x)
    {
        cout << "Not Valid" << endl;
    }
    for (int i = 0; i < 3; i++)
    {
        if (sortX[i] > xMax)
        {
            xMax = sortX[i];
        }
        else if (sortX[i] < xMin)
        {
            xMin = sortX[i];
        }
    }

    for (int i = 0; i < 3; i++)
    {
        if (sortY[i] > yMax)
        {
            yMax = sortY[i];
        }
        else if (sortY[i] < yMin)
        {
            yMin = sortY[i];
        }
    }

    for (int x = xMin; x <= xMax; x++) {
        for (int y = yMin; y <= yMax; y++) {
              bool value= false ;
              Vector2 edge1 = t1.v2 - t1.v1;
              Vector2 perp1 = edge1.perpendicular();
              Vector2 g1 = Vector2(x, y) - t1.v1;
              float dot1 = perp1.dot(g1);
              Vector2 edge2 = t1.v3 - t1.v2;
              Vector2 perp2 = edge2.perpendicular();
              Vector2 g2 = Vector2(x, y) - t1.v2;
              float dot2 = perp2.dot(g2);
             Vector2 edge3 = t1.v1 - t1.v3;
             Vector2 perp3= edge3.perpendicular();
             Vector2 g3 = Vector2(x, y) - t1.v3;
             float dot3= perp3.dot(g3);
            if (dot1 >= 0 && dot2 >= 0 && dot3 >= 0) 
                {
                 value= true;
                }
                 else 
                {
                value= false;
                }
            if (value==true)
            {
                setColorPixel(x, y, t1.c1); 
            }
        }
    }
} 


void Raster::drawTriangle3D_Barycentric(Triangle3D T) {
  if (T.shouldDraw == false)
  {
      return;
  }
 else{
   
  Triangle2D myTri(T);
  float x_value[] = {T.v1.x, T.v2.x, T.v3.x};
  float y_value[] = {T.v1.y, T.v2.y, T.v3.y};
  float maxX = x_value[0];
  float minX = x_value[0];
  float maxY = y_value[0];
  float minY = y_value[0];

  for (int i = 0; i < 3; i++) 
  {
    if (x_value[i] > maxX) 
    {
      maxX = x_value[i];
    } 
    else if (x_value[i] <minX) {
    minX = x_value[i];
    }
  }

  for (int i = 0; i < 3; i++) {
    if (y_value[i] > maxY) {
      maxY = y_value[i];
    } else if (y_value[i] < minY) {
      minY = y_value[i];
    }
  }

  for (int x = minX; x <=maxX; x++) {
    for (int y = minY; y <= maxY; y++) {
      
      float lambda1 = 0.0;
      float lambda2 = 0.0;
      float lambda3 = 0.0;
      
      myTri.calculateBarycentricCoordinates(Vector2(float(x), float(y)), lambda1, lambda2, lambda3);
      
      if (lambda1 >= 0.0 && lambda1 <= 1.0 && lambda2 >= 0.0 &   lambda2 <= 1.0 && lambda3 >= 0.0 && lambda3 <= 1.0)
      {
        if((T.v1.z*lambda1 + T.v2.z*lambda2 + T.v3.z*lambda3) < getDepthPixel(x, y))
        {
								setColorPixel(x, y, T.c1*lambda1 + T.c2*lambda2 + T.c3*lambda3);
                setDepthPixel(x, y, T.v1.z*lambda1 + T.v2.z*lambda2 + T.v3.z*lambda3);        
        }
      }
    }
  }
  }
  }

void Raster::drawModel(Model newModel){
    for(int i = 0; i<newModel.numTriangles(); i++)
    {
        drawTriangle3D_Barycentric(newModel[i]);
    }
}