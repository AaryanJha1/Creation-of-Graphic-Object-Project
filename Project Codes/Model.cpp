#include "Model.h"

Model::Model(){
    
    triangles.clear();
}

int Model::numTriangles(){
  int ans = (int) triangles.size();
  return ans;
}

Triangle3D Model::operator[](int i){
    return triangles[i];
}

void Model::transform(Matrix4 transformation){ 
    for(int i = 0; i < numTriangles(); i++)
    {
      if(triangles[i].shouldDraw)
      {
        triangles[i].transform(transformation);
      }    
    } 
}

void Model::readFromOBJFile(string filepath, Color pFillColor){
    ifstream objFile(filepath);
    if(objFile.is_open())
    {
        string path;
        vector<Vector4> points;
        while(getline(objFile, path))
        {
            vector<string> enter;
            istringstream s(path);
            string word;
            while(getline(s, word, ' '))
            {
                enter.push_back(word);
            }
            if(enter[0] == "v")
            {
                points.push_back(Vector4(atof(enter[1].c_str()), atof(enter[2].c_str()), atof(enter[3].c_str()), 1.0f));
            }
            else if(enter[0] == "f")
            {
                if(enter.size() == 4)
                {
                    Vector4 v1 = points[atoi(enter[1].c_str())-1];
                    Vector4 v2 = points[atoi(enter[2].c_str())-1];
                    Vector4 v3 = points[atoi(enter[3].c_str())-1];                    
                    triangles.push_back(Triangle3D(v1, v2, v3, pFillColor, pFillColor, pFillColor));
                }
                else if(enter.size() == 5)
                {
                    Vector4 v1 = points[atoi(enter[1].c_str())-1];
                    Vector4 v2 = points[atoi(enter[2].c_str())-1];
                    Vector4 v3 = points[atoi(enter[3].c_str())-1];
                    Vector4 v4 = points[atoi(enter[4].c_str())-1];
                    Triangle3D t1 = Triangle3D(v1, v2, v3, pFillColor, pFillColor, pFillColor);
                    Triangle3D t2 = Triangle3D(v1, v3, v4, pFillColor, pFillColor, pFillColor);                    
                    triangles.push_back(t1);
                    triangles.push_back(t2);
                }
            }
        }

        objFile.close();
    }
}

void Model::homogenize()
{
	for(int i = 0; i < triangles.size(); i++)
	{
		float clip = triangles[i].v1.w;
    triangles[i].v1.x = triangles[i].v1.x/clip;
    triangles[i].v1.y = triangles[i].v1.y/clip;
    triangles[i].v1.z = triangles[i].v1.z/clip;
    triangles[i].v1.w = 1;

    clip = triangles[i].v2.w;
    triangles[i].v2.x = triangles[i].v2.x/clip;
    triangles[i].v2.y = triangles[i].v2.y/clip;
    triangles[i].v2.z = triangles[i].v2.z/clip;
    triangles[i].v2.w = 1;

    clip = triangles[i].v3.w;
    triangles[i].v3.x = triangles[i].v3.x/clip;
    triangles[i].v3.y = triangles[i].v3.y/clip;
    triangles[i].v3.z = triangles[i].v3.z/clip;
    triangles[i].v3.w = 1;
  }
}

void Model::performBackfaceCulling(Vector4 eye, Vector4 spot){
  for (int i = 0; i < triangles.size(); i++){
    Vector4 look = spot - eye;
		Vector4 x = triangles[i].v3 - triangles[i].v2;
		Vector4 y = triangles[i].v1 - triangles[i].v2;
		Vector4 surface_normal = y.cross(x).normalize();
    
		if (surface_normal.dot(look) > 0.0){
			triangles[i].shouldDraw = true;
      triangles[i].c1 = Blue;
      triangles[i].c2 = Blue;
      triangles[i].c3 = Blue;
		}
	}
}