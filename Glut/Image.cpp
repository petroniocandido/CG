/*
 * CG - Códigos gerados para a disciplina de Computação Gráfica
 * Copyright (C) 2012 Petrônio Cândido de Lima e Silva.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "Image.h"
#include "Bitmap.h"
#include <math.h>

using namespace std;

Image::Image(int h, int w)
 {
     this->height = h;
     this->width = w;
     this->pixels = new float[h*w*3];
}

Image::~Image() {
     delete [] pixels;
}
void Image::setPixel(int px, int py,float r,float g, float b) {
     int index = (py*this->width + px)*3;
     pixels[index] = r;
     pixels[index+1] = g;
     pixels[index+2] = b;
}

void Image::replacePixels(Image img){
     float *tmp = pixels;
     pixels = img.pixels;
 //    delete tmp;
}

float Image::getPixel(int x, int y, int color) {
     return pixels[y*width + x + color];
}

float Image::getPixelR(int x, int y) {
     return getPixel(x,y,0);
}

float Image::getPixelG(int x, int y) {
     return getPixel(x,y,1);
}

float Image::getPixelB(int x, int y) {
     return getPixel(x,y,2);
}

void Image::draw() {
   draw(0,0);
}

void Image::draw(int x, int y) {
    glRasterPos2i(x,y);
    glDrawPixels(this->width,this->height,GL_RGB,GL_FLOAT,this->pixels);
}

Image::Image(char * path) {
    Bitmap bmp(path);
    long size = bmp.height * bmp.width * 3;
    pixels = new float[size];
    this->height = bmp.height;
    this->width = bmp.width+1;
    for(long i = 0; i < size; i++) {
            float orig = (float)bmp.data[i];
            float color =  orig / (float)256  ;
            if(color <= 0){
                    color = 1-color;
            }
                    
            pixels[i] = color;
    }
    
}

Image Image::applyFilter(int radix, int *map){
     
     Image nova(this->height,this->width);
     
     for(int countY = 0; countY < this->height; countY++){
            for(int countX = 0; countX < this->width; countX++){
                    float avgR = 0,  avgG = 0, avgB = 0;
                    int count = 0;
                    
                    int index_map = 0;
                    for(int ry = countY - radix; ry <= countY + radix; ry++)
                            for(int rx = countX - radix; rx <= countX + radix; rx++){
                                if(rx >= 0 && rx < width && ry >= 0 && ry < height){
                                      avgR += getPixelR(ry,rx)* map[index_map];
                                      avgG += getPixelG(ry,rx)* map[index_map];
                                      avgB += getPixelB(ry,rx)* map[index_map];                                      
                                      
                                      count += abs(map[index_map]);
                                }
                                index_map++;
                            }
                    float r = avgR/(float)count;
                    float g = avgG/(float)count;
                    float b = avgB/(float)count;

                    nova.setPixel(countX, countY, r, g, b);
            }
            
      }
      
      return nova;
}

Image Image::blur(){
     int map[] =  { 1, 1, 1, 1, 1,
                    1, 3, 3, 3, 1,
                    1, 3, 20, 3, 1,
                    1, 3, 3, 3, 1,
                    1, 1, 1, 1, 1,};
     return applyFilter(2, map );
}

Image Image::sharpen(){
      int map[] =  {-1, -1, -1, -1, 27, -1, -1, -1, -1};
      return applyFilter(1, map );
}
