#include "Color.h"
#include <math.h>

Color::Color() {
  red = 0;
  green = 0;
  blue = 0;
  alpha = 1.0f;
}

Color::Color(float pRed, float pGreen, float pBlue, float pAlpha) {
  red = pRed;
  green = pGreen;
  blue = pBlue;
  alpha = pAlpha;
  clamp();
}

void Color::clamp() {

  red = fmin(red, 1.0f);
  red = fmax(red, 0.0f);
  blue = fmin(blue, 1.0f);
  blue = fmax(blue, 0.0f);
  green = fmin(green, 1.0f);
  green = fmax(green, 0.0f);
  alpha = fmin(alpha, 1.0f);
  alpha = fmax(alpha, 0.0f);

}

Color Color::operator+(Color another) {

  Color pColor(red, green, blue, alpha);
  pColor.red += another.red;
  pColor.green += another.green;
  pColor.blue += another.blue;
	pColor.alpha += another.alpha;  
  pColor.clamp();
  return pColor;
}

Color Color::operator-(Color &another) {
  Color a = Color(red - another.red, green - another.green, blue - another.blue, alpha - another.alpha);
  a.clamp();
  return a;
}

Color Color::operator*(float another) {
  Color a = Color(red * another, green * another, blue * another, alpha * another);
  a.clamp();
  return a;
}
