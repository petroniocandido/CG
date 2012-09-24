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
#include <string.h>

#define _USE_MATH_DEFINES

using namespace std;

Image::Image(int h, int w)
 {
     this->height = h;
     this->width = w;
     this->size = (this->height*(this->width+1))*3;
     pixels = new float[size];
}

float adaptColor(char c) {
    float orig = (float)c;
    float color =  orig / (float)127 ;
    if(color < 0)
        color = 1-color;
                     
    return color;
}

Image::Image(char * path) {
    Bitmap bmp(path);
    long size = bmp.height * (bmp.width+1) * 3;
    pixels = new float[size];
    this->height = bmp.height;
    this->width = bmp.width;

    int offset=bmp.padWidth-bmp.byteWidth;
    //count backwards so you start at the front of the image
    for(int i=0;i<bmp.dataSize;i+=3) {
        //jump over the padding at the start of a new line
        if(((i+1)%bmp.padWidth)==0) {
            i+=offset;
        }
        //transfer the data
        pixels[i] = adaptColor(bmp.data[i]);
        pixels[i+1] = adaptColor(bmp.data[i+1]);
        pixels[i+2] = adaptColor(bmp.data[i+2]);
    }
    
}

Image::~Image() {
     delete [] pixels;
}
void Image::setPixel(int px, int py ,float r,float g, float b) {
     int index = (py*(width) + px)*3;
     pixels[index] = r;
     pixels[index+1] = g;
     pixels[index+2] = b;
}

void Image::replacePixels(Image img){


}

float Image::getPixel(int px, int py, int color) {
      long index = (py*(width) + px)*3 + color;
      return pixels[index];
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
    int viewport[4]; 
    glGetIntegerv(GL_VIEWPORT, viewport); 
    glMatrixMode(GL_PROJECTION); 
    glPushMatrix(); 
    glLoadIdentity(); 
    gluOrtho2D(0, 800, 0, 600); 
    glMatrixMode(GL_MODELVIEW); 
    glLoadIdentity(); 
  
 // glPixelStorei(GL_PACK_ALIGNMENT, 8);
  
    glRasterPos2f(x, this->height);
    glDrawPixels(this->width+1,this->height,GL_RGB,GL_FLOAT,this->pixels);
}

Image Image::applyFilter(int radix, int *map){
     
     Image nova(height,width);
     
     for(int countY = 0; countY < height; countY++){
            for(int countX = 0; countX < width; countX++){
                    float avgR = 0,  avgG = 0, avgB = 0;
                    int count = 0;
                    
                    int index_map = 0;
                    for(int ry = countY - radix; ry <= countY + radix; ry++)
                            for(int rx = countX - radix; rx <= countX + radix; rx++){
                                if(rx >= 0 && rx < width && ry >= 0 && ry < height){
                                      avgR += getPixelR(rx,ry)* map[index_map];
                                      avgG += getPixelG(rx,ry)* map[index_map];
                                      avgB += getPixelB(rx,ry)* map[index_map];                                      
                                      
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
      
    //  replacePixels(nova);
      
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

Image Image::resize(int newh, int neww ) {
     // Image tmp = *this;
      if(neww > width)
           return increaseWidth(neww);               
      /*else 
           tmp = tmp.decreaseWidth(neww);        
      
      
      if(newh > height)
            tmp = tmp.increaseHeight(newh);              
      else 
            tmp = tmp.decreaseHeight(newh);       
      */      
      //return tmp;
            
}

Image Image::increaseWidth(int neww){
     
     int mod = neww % width;
     int copia = mod > 0 ? width / mod : 0;
     int repete = (neww - mod) / width;
     
     Image nova(height,neww);
     
     int newx = 0;
     for(int countX = 0; countX < width; countX++){            
            int inc = 0;
            if(copia > 0) inc = (countX % copia) == 0 ? 1 : 0;
            for(int rep = 0; rep < repete+inc; rep++){
                for(int countY = 0; countY < height; countY++){
                        
                        float r = getPixelR(countX,countY);
                        float g = getPixelG(countX,countY);
                        float b = getPixelB(countX,countY);
                        
                        nova.setPixel(newx, countY, r, g, b);
                }
                newx++;
            }
      }
      
      return nova;
}

Image Image::increaseHeight(int neww){
     
     int mod = neww % height;
     int copia = mod > 0 ? height / mod : 0;
     int repete = (neww - mod) / height;
     
     Image nova(neww,width);
     
     int newy = 0;
     for(int countY = 0; countY < height; countY++){
            int inc = 0;
            if(copia > 0) inc = (countY % copia) == 0 ? 1 : 0;
            for(int rep = 0; rep < repete+inc; rep++){
                for(int countX = 0; countX < width; countX++){
                        
                        float r = getPixelR(countX,countY);
                        float g = getPixelG(countX,countY);
                        float b = getPixelB(countX,countY);
                        
                        nova.setPixel(countX, newy, r, g, b);
                }
                newy++;
            }
      }
      
      return nova;
}

Image Image::decreaseWidth(int neww){
     int mod = width % neww ;
     int copia = mod > 0 ? width / mod : 0;               // Sempre parte do pressuposto que neww != width
     int repete = (width - mod) / neww;
     
      Image nova(height,neww);
     
     for(int countY = 0; countY < height; countY++){
            for(int countX = 0; countX < neww; countX++){
                    float avgR = 0,  avgG = 0, avgB = 0;
                    for(int count = 0; count < repete; count++){
                            avgR += getPixelR(countX*repete+count,countY);
                            avgG += getPixelG(countX*repete+count,countY);
                            avgB  += getPixelB(countX*repete+count,countY);
                                      
                    }
                    float r = avgR/repete;
                    float g = avgG/repete;
                    float b = avgB/repete;

                    nova.setPixel(countX, countY, r, g, b);
            }
            
      }
     
     return nova;
}

Image Image::decreaseHeight(int neww){
     int mod = height % neww ;
     int copia = mod > 0 ? height / mod : 0;               // Sempre parte do pressuposto que neww != width
     int repete = (height - mod) / neww;
     
     Image nova(height,neww);
     
     for(int countY = 0; countY < neww; countY++){
            for(int countX = 0; countX < width; countX++){
                    float avgR = 0,  avgG = 0, avgB = 0;
                    for(int count = 0; count < repete; count++){
                          avgR += getPixelR(countX,countY*repete+count);
                          avgG += getPixelG(countX,countY*repete+count);
                          avgB += getPixelB(countX,countY*repete+count);
                                      
                    }
                    float r = avgR/repete;
                    float g = avgG/repete;
                    float b = avgB/repete;

                    nova.setPixel(countX, countY, r, g, b);
            }
            
      }
     
    return nova;
}


Image Image::invert(){
     
     /*Image nova(height,width);
     
     for(int countY = 0; countY < height; countY++){
            for(int countX = 0; countX < width; countX++){
                    float R = 0,  G = 0, B = 0;
                    R = 1 - getPixelR(countX,countY);
                    G = 1 - getPixelG(countX,countY);
                    B = 1 - getPixelB(countX,countY);

                    nova.setPixel(countX, countY, R, G, B);
            }
            
      }
     
    return nova;
    */
    float map[] =  { -1,  0,  0, 1, 
                      0, -1,  0, 1,
                      0,  0, -1, 1
                     };
    return colorFilter(map);
}

Image Image::grayscale(){
     
     /*Image nova(height,width);
     
     for(int countY = 0; countY < height; countY++){
            for(int countX = 0; countX < width; countX++){
                    float R = 0,  G = 0, B = 0;
                    R = getPixelR(countX,countY);
                    G = getPixelG(countX,countY);
                    B = getPixelB(countX,countY);
                    
                    float color = (R + G + B) / 3;

                    nova.setPixel(countX, countY, color, color, color);
            }
            
      }
     
    return nova;
    */
    
    float map[] =  { .33, .33, .33, 0, 
                     .33, .33, .33, 0,
                     .33, .33, .33, 0
                     };
    return colorFilter(map);
}

Image Image::sepia(){
     
     /*Image nova(height,width);
     
     for(int countY = 0; countY < height; countY++){
            for(int countX = 0; countX < width; countX++){
                    float R = 0,  G = 0, B = 0;
                    R = getPixelR(countX,countY);
                    G = getPixelG(countX,countY);
                    B = getPixelB(countX,countY);
                    
                    float nR = (R * .393) + (G *.769) + (B * .189);
                    float nG = (R * .349) + (G *.686) + (B * .168);
                    float nB = (R * .272) + (G *.534) + (B * .131);
                   

                    nova.setPixel(countX, countY, nR, nG, nB);
            }
            
      }
     
    return nova;
    */
    float map[] =  { .393, .769, .189, 0, 
                     .349, .686, .168, 0,
                     .272, .534, .131, 0
                     };
    return colorFilter(map);
}

Image Image::colorFilter(float *map){
     
     Image nova(height,width);
     
     for(int countY = 0; countY < height; countY++){
            for(int countX = 0; countX < width; countX++){
                    float R = 0,  G = 0, B = 0;
                    R = getPixelR(countX,countY);
                    G = getPixelG(countX,countY);
                    B = getPixelB(countX,countY);
                    
                    float nR = (R * map[0]) + (G * map[1]) + (B * map[ 2]) + map[ 3];
                    float nG = (R * map[4]) + (G * map[5]) + (B * map[ 6]) + map[ 7];
                    float nB = (R * map[8]) + (G * map[9]) + (B * map[10]) + map[11];
                   

                    nova.setPixel(countX, countY, nR, nG, nB);
            }
            
      }
     
    return nova;
}

Image Image::swap(){
    float map[] =  { -1.1, 0, 0, 2, 
                     0, -1.1, 0, 2,
                     0, 0, -1.1, 2
                     };
    return colorFilter(map);
}

 Image Image::Degrade(float r, float g, float b, int d)
        {
            Image degrade(height,width);
            float i = 1.0/(float)d;
            for (int countY = 0; countY < height; countY++)
            {
                float count = 1.0;
                for (int countX = 0; countX < width; countX++)
                {
                    
                    float R = getPixelR(countX,countY);
                    float G = getPixelG(countX,countY);
                    float B = getPixelB(countX,countY);
                    
                    if(countX <= d) {
                              R = (count * r) + ((1-count)*R);
                              G = (count * g) + ((1-count)*G);
                              B = (count * b) + ((1-count)*B);
                    
                    }
                    degrade.setPixel(countX, countY, R, G, B);     
                    count = count - i;

                    }
                     
                    
            }
            return degrade;
        }
        
Image Image::applyRotate(float ang) {
     
     Image nova(height,width);
     
     // Converte ang para radianos
     float a = (ang * M_PI) / 180.0;
     
     for(int countY = 0; countY < height; countY++){
            for(int countX = 0; countX < width; countX++){
                    
                    float R = getPixelR(countX,countY);
                    float G = getPixelG(countX,countY);
                    float B = getPixelB(countX,countY);
                    
                    //x'= x* cos a - y* sin a
                    //y'= x* sin a + y* cos a
                    
                    int nx = (int)(((float)countX * cos(a)) - ((float)countY * sin(a)));
                    int ny = (int)(((float)countX * sin(a)) + ((float)countY * cos(a)));
                    
                    if(nx >= 0 && ny >= 0 && nx <= width && ny <= height)                
                                        nova.setPixel(nx, ny, R, G, B);
            }
      }
      
      return nova;
}
  
