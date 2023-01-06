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
               

//pomocna funkcija za racunanje
float fja(float xa,float ya,float xc,float yc,float x,float y) 
{
    return ((ya-yc)*x+(xc-xa)*y+xa*yc-xc*ya);
}


void draw_triangle_2d(float x0, float y0, float x1, float y1, float x2, float y2 ,TGAImage &image,TGAColor color) {   

    int maxX = ceil (max (max(x0,x1), x2));
    int minX = floor (min (min(x0,x1), x2));

    int maxY = ceil (max (max(y0,y1), y2));
    int minY = floor(min (min(y0,y1), y2));
   
    float alpha,beta,gama;

    for (int j =minY; j <= maxY ; ++j){
        for (int i = minX; i <= maxX; ++i){
            
            alpha = fja(x1,y1,x2,y2,i,j)/fja(x1,y1,x2,y2,x0,y0); 
            beta= fja(x2,y2,x0,y0,i,j)/fja(x2,y2,x0,y0,x1,y1);  
            gama= fja(x0,y0,x1,y1,i,j)/fja(x0,y0,x1,y1,x2,y2);  
             
            if (alpha >= 0 && alpha <= 1 && beta >= 0 && beta <= 1 && gama >= 0 && gama <= 1) 
            { 
                if (( alpha > 0 ||((fja(x1,y1,x2,y2,x0,y0))*(fja(x1,y1,x2,y2,-1,-1))) >= 0)
                 &&( beta > 0 || ((fja(x2,y2,x0,y0,x1,y1))*(fja(x2,y2,x0,y0,-1,-1))) >= 0)
                 &&( gama > 0 || (fja(x0,y0,x1,y1,x2,y2))*(fja(x0,y0,x1,y1,-1,-1))) >= 0)
                 {
                        image.set(j, i, color);
                }  
            }
        }
    } 
}

void draw_triangle_2d_gouraurd (float x0, float y0, float x1, float y1, float x2, float y2 ,TGAImage &image,TGAColor c0,TGAColor c1,TGAColor c2){
    
    int maxX = ceil (max (max(x0,x1), x2));
    int minX = floor (min (min(x0,x1), x2));

    int maxY = ceil (max (max(y0,y1), y2));
    int minY = floor(min (min(y0,y1), y2));
   
    float alpha,beta,gama;
    TGAColor color;

    for (int j = minY; j <= maxY; ++j){
        for (int i = minX; i <= maxX; ++i){

            float f1 = fja(x1, y1, x2, y2, x0, y0);
            float f2 = fja(x2, y2, x0, y0, x1, y1);
            float f3 = fja(x0, y0, x1, y1, x2, y2);
            
            alpha= fja(x1,y1,x2,y2,i,j)/f1; 
            beta= fja(x2,y2,x0,y0,i,j)/f2;  
            gama= fja(x0,y0,x1,y1,i,j)/f3;  
              
            if (alpha >= 0 && alpha <= 1 && beta >= 0 && beta <= 1 && gama >= 0 && gama <= 1)
            {              
                if ((alpha>0 ||(f1 * (fja(x1,y1,x2,y2,-1,-1))) >=0)
                 && (beta>0 || (f2 * (fja(x2,y2,x0,y0,-1,-1))) >=0)
                 && (gama>0 || (f3 * (fja(x0,y0,x1,y1,-1,-1))) >=0))
                 {
                        color.r=alpha*c0.r+beta*c1.r+gama*c2.r;
                        color.g=alpha*c0.g+beta*c1.g+gama*c2.g;
                        color.b=alpha*c0.b+beta*c1.b+gama*c2.b;
                        image.set(j, i, color);
                }  
            }
        }
    } 
}

int main()
{
    // definiraj sliku
    TGAImage image(width, height, TGAImage::RGB);
    
    // nacrtaj trokut 
    draw_triangle_2d(20, 40, 180, 150, 100,210,image, blue);
    draw_triangle_2d(20, 200, 180, 250, 100, 340,image, green);
    draw_triangle_2d_gouraurd(250, 250, 250, 440, 440, 440, image, green, blue, red);

    // spremi sliku 
    image.flip_vertically();
    image.write_tga_file("zadatak1_2.tga");
}
