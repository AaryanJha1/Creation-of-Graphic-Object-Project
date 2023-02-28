#include "Matrix.h"
#include <math.h>

using namespace std;

Matrix4::Matrix4(){
    ix = 1;
    jx = 0;
    kx = 0;
    ox = 0;
    iy = 0;
    jy = 1;
    ky = 0;
    oy = 0;
    iz = 0;
    jz = 0;
    kz = 1;
    oz = 0;
    iw = 0;
    jw = 0;
    kw = 0;
    ow = 1;
}

Matrix4::Matrix4(float new_ix, float new_jx, float new_kx, float new_ox,
    float new_iy, float new_jy, float new_ky, float new_oy,
    float new_iz, float new_jz, float new_kz, float new_oz,
    float new_iw, float new_jw, float new_kw, float new_ow){
    ix = new_ix;
    jx = new_jx;
    kx = new_kx;
    ox = new_ox;
    iy = new_iy;
    jy = new_jy;
    ky = new_ky;
    oy = new_oy;
    iz = new_iz;
    jz = new_jz;
    kz = new_kz;
    oz = new_oz;
    iw = new_iw;
    jw = new_jw;
    kw = new_kw;
    ow = new_ow;
}

Vector4 Matrix4::operator*(Vector4 newVal){
  
	Vector4 ans;
  ans.x = (newVal.x * ix) + (newVal.y * jx) + (newVal.z * kx) + (newVal.w * ox);
  ans.y = (newVal.x * iy) + (newVal.y * jy) + (newVal.z * ky) + (newVal.w * oy);
  ans.z = (newVal.x * iz) + (newVal.y * jz) + (newVal.z * kz) + (newVal.w * oz);
  ans.w = (newVal.x * iw) + (newVal.y * jw) + (newVal.z * kw) + (newVal.w * ow);
  return ans;


}

Matrix4 Matrix4::operator*(Matrix4 newVal){
	  Vector4 a = Vector4(newVal.ix, newVal.iy, newVal.iz, newVal.iw);
    Vector4 b = Vector4(newVal.jx, newVal.jy, newVal.jz, newVal.jw);
    Vector4 c = Vector4(newVal.kx, newVal.ky, newVal.kz, newVal.kw);
    Vector4 d = Vector4(newVal.ox, newVal.oy, newVal.oz, newVal.ow);
    a =  *this * a;
    b = *this * b;
    c=  *this * c;
    d = *this * d;
    Matrix4 ans;
    ans.ix = a.x;
    ans.iy = a.y;
    ans.iz = a.z;
    ans.iw = a.w;
    ans.jx = b.x;
    ans.jy = b.y;
    ans.jz = b.z;
    ans.jw = b.w;
    ans.kx = c.x;
    ans.ky = c.y;
    ans.kz = c.z;
    ans.kw = c.w;
    ans.ox = d.x;
    ans.oy = d.y;
    ans.oz = d.z;
    ans.ow = d.w;
		return ans;
}

Matrix4 Translate3D(float tX, float tY, float tZ){
Matrix4 ans = Matrix4(1, 0, 0, tX,
                      0, 1, 0, tY,
                      0, 0, 1, tZ,
                      0, 0, 0, 1);
return ans;
}

Matrix4 Scale3D(float sX, float sY, float sZ){
Matrix4 ans =
Matrix4(sX, 0, 0, 0,
        0, sY, 0, 0,
        0, 0, sZ, 0,
        0, 0, 0, 1);
return ans;
}

Matrix4 RotateX3D(float degrees){
float radians = degrees * M_PI / 180.0;
Matrix4 ans =
Matrix4(1, 0, 0, 0,
        0, cosf(radians), sinf(radians), 0,
        0, -sinf(radians), cosf(radians), 0,
        0, 0, 0, 1);
return ans;
}

Matrix4 RotateY3D(float degrees){
float radians = degrees * M_PI / 180.0;
Matrix4 ans =
Matrix4(cosf(radians), 0, -sinf(radians), 0,
        0, 1, 0, 0,
        sinf(radians), 0, cosf(radians), 0,
        0, 0, 0, 1);
return ans;
}

Matrix4 RotateZ3D(float degrees){
float radians = degrees * (M_PI / 180.0);
Matrix4 ans =
Matrix4(cosf(radians), sinf(radians), 0, 0,
        -sinf(radians), cosf(radians), 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1);
return ans;
}

Matrix4 Rotate3D(float degreesX, float degreesY, float degreesZ){
  Matrix4 ans = RotateX3D(degreesX) * RotateY3D(degreesY) * RotateZ3D(degreesZ);
  return ans;
}

Matrix4 Rotate3D(float degrees, Vector4 vec){
		float alpha = atanf(vec.x/vec.z);
    float beta = acosf(vec.y/vec.magnitude());
		alpha = alpha * (180.0/ M_PI);
		beta = beta * (180.0/ M_PI);
    
    Matrix4 ans= RotateY3D(-alpha) * RotateX3D(-beta) * RotateY3D(degrees) * RotateX3D(beta) * RotateY3D(alpha);
    return ans;
}

void Matrix4::print(){
    cout << ix << " " << jx << " " << kx << " " << ox << endl;
    cout << iy << " " << jy << " " << ky << " " << oy << endl;
    cout << iz << " " << jz << " " << kz << " " << oz << endl;
    cout << iw << " " << jw << " " << kw << " " << ow << endl;

}

Matrix4 LookAt(Vector4 eye, Vector4 spot, Vector4 up)
{
	Matrix4 matrix;
	Vector4 look = (spot-eye).normalize();
	Vector4 right = look.cross(up).normalize();
	up = up.normalize();
	matrix = Translate3D(-eye.x, -eye.y, -eye.z);
	Matrix4 map = Matrix4(right.x, right.y, right.z, 0, 
                        up.x, up.y, up.z, 0, 
                        -look.x, -look.y, -look.z, 0, 
                        0, 0, 0, 1);
	return map * matrix;
  
}

Matrix4 Orthographic(float minX, float maxX, float minY, float maxY, float minZ, float maxZ)
{
	Matrix4 translate = Translate3D(-(minX + maxX)/2, 
                                  -(minY + maxY)/2, 
                                  -(minZ + maxZ)/2);
	Matrix4 scale = Scale3D(2/(maxX - minX), 
                          2/(maxY - minY), 
                          2/(maxZ - minZ));
	return scale * translate;
  
}

Matrix4 Perspective(float fovY, float aspect, float nearZ, float farZ)
{
	float F = 1/(tan((fovY* M_PI / 180.0)/2));
	float yvalue = (farZ + nearZ)/(nearZ - farZ);
	float zvalue = (2*nearZ*farZ)/(nearZ - farZ);
  
	Matrix4 final_result = Matrix4(F/aspect, 0, 0, 0,
																0, F, 0, 0,
																0, 0, yvalue, zvalue,
																0, 0, -1, 0);
	return final_result;
}

Matrix4 Viewport(float x, float y, float width, float height)
{
	Matrix4 translate = Translate3D(x, y, 0);
	Matrix4 scale = Scale3D(width, height, 1);
	Matrix4 scale1 = Scale3D(0.5, 0.5, 0.5);
	Matrix4 translate1 = Translate3D(1, 1, -1);
  return translate * scale * scale1 * translate1;
}