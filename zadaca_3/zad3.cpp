#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include "tgaimage.h"
using namespace std;


// dimenzije slike
const int width  = 512;
const int height = 512;

// definirajmo boje
const TGAColor green = TGAColor(0, 255, 0, 1);
const TGAColor red   = TGAColor(255, 0, 0, 1);
const TGAColor blue  = TGAColor(0, 0, 255, 1);
               
typedef float Vec3[3]; 
typedef float Vec2[2];

//pomocna funkcija za racunanje
float fja(const Vec3 &a, const Vec3 &b, const Vec3 &c) 
{ 
    return (c[0] - a[0]) * (b[1] - a[1]) - (c[1] - a[1]) * (b[0] - a[0]); 
} 


void draw_triangle(float x0, float y0,float z0, float x1, float y1,float z1, float x2, float y2,float z2 ,TGAImage &image,TGAColor color)
{   
    Vec3 a1 = {x0,y0,z0};
    Vec3 a2 = {x1,y1,z1};
    Vec3 a3 = {x2, y2,z2};

    a1[0] /= a1[2]; 
    a1[1] /= a1[2];

    a2[0] /= a2[2]; 
    a2[1] /= a2[2];

    a3[0] /= a3[2]; 
    a3[1] /= a3[2];
    
    a1[1]= (1 + a1[1]) * 0.5 * height; 
    a1[0] = (1 + a1[0]) * 0.5 * width; 
    
    a2[1]= (1 + a2[1]) * 0.5 * height; 
    a2[0] = (1 + a2[0]) * 0.5 * width; 

    a3[1]= (1 + a3[1]) * 0.5 * height; 
    a3[0] = (1 + a3[0]) * 0.5 * width; 
    
    a1[2] = 1 / a1[2];  
    a2[2]= 1 / a2[2]; 
    a3[2] = 1 / a3[2];

    for (int j=0; j<height; ++j)
    {
        for (int i=0; i<width; ++i)
        {
            float p1 = (float)i+0.5f;
            float p2 =  height-(float)j+0.5f;
          
            Vec3 p = {p1, p2, 0};
          
            float alpha = fja(a3,a2,p); 
            float beta = fja(a1,a3,p);
            float gama = fja(a2,a1,p); 

            if(alpha >= 0 && beta >= 0 && gama >= 0)
            { 
                image.set(j,i,color);
            }
        }
    }
}


int main()
{
    // definiraj sliku
    TGAImage image(width, height, TGAImage::RGB);
    
    // nacrtaj trokut 
    draw_triangle(-48,-10,82,29,-15,44,13,34,114,image,blue);
    
    // spremi sliku 
    image.flip_vertically();
    image.write_tga_file("zadatak3.tga");
}
