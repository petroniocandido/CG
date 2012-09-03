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
#include <graphics.h>
#include <queue>
#include <iostream>
#include <math.h>

using namespace std;

// http://www.gidforums.com/t-15568.html
// http://www.gidforums.com/t-15789.html
// http://www.cplusplus.com/forum/general/24936/

Image::Image(int h, int w)
 {
     this->height = h;
     this->width = w;
     this->pixels = new int[h*w];
     this->usingPalette = false;
     this->paletteMaxColors = 0;
}

Image::~Image() {
     delete [] pixels;
     delete &histogram;  
     delete [] palette;
}

int Image::getHeight() {
     return height;
}

int Image::getWidth() {
     return width;
}

void Image::setPixel(int x, int y, int color) {
     pixels[y*width + x] = color;
}

int Image::getPixel(int x, int y) {
     return pixels[y*width + x];
}

void Image::draw() {
     for(int countY = 0; countY < height; countY++)
            for(int countX = 0; countX < width; countX++){
                    int index_pixel = countY*width+countX;
                    int color = (usingPalette)? palette[pixels[index_pixel]] : pixels[index_pixel];
                    putpixel(countX, countY, color);
            }
}
void Image::dump() {
     for(int count = 0; count < height*width; count++){
                    int color = (usingPalette)? palette[pixels[count]] : pixels[count];
                    cout << color << ",";
            }
}

void Image::load(int *bmp) {
     for(int countY = 0; countY < height; countY++)
            for(int countX = 0; countX < width; countX++)
                    setPixel(countX, countY, bmp[countY*width+countX]);
}


void Image::createHistogram() {
       
     int colorCount = 0;
     int size = width*height;
     int *tmp_histogram = new int[size*2];
     int last_color = 0;
     int last_palette = 0;
     
     // Percorrer todos os pixels da imagem
     for(int count = 0; count < size; count++){
             if(last_color == pixels[count]){
                 tmp_histogram[last_palette*2 + 1]++;
             }
             else {
                 int color = pixels[count];
                 bool newc = true;
                 for(int p = 0; p < colorCount; p++){
                         if(color == tmp_histogram[p*2]){
                             tmp_histogram[p*2+1]++;
                             newc = false;
                             last_palette = p;
                         }
                 }
                 if(newc){
                          tmp_histogram[colorCount*2] = color;
                          tmp_histogram[colorCount*2 + 1] = 1;
                          last_palette = colorCount;
                          colorCount++;
                 }
                 last_color = color;
                 
             }
     }
     
     // Ordena
     
     for(int p = 0; p < colorCount; p++){
             histogram_entry entry = { tmp_histogram[p*2], tmp_histogram[p*2+1] };
             histogram.push(entry);
     }
}

void Image::showHistogram() {
     while (! histogram.empty()) {
       histogram_entry entry = histogram.top();
       cout << entry.color << " " << entry.frequency << " " << endl;
       histogram.pop();
    }
}

void Image::setPaletteMaxColors(int m) {
     paletteMaxColors = m;
}

void Image::createPalette() {
     paletteMaxColors = (paletteMaxColors != 0)? paletteMaxColors : histogram.size();
     
     palette = new int[paletteMaxColors];
     
     for(int p = 0; p < paletteMaxColors; p++){
             histogram_entry entry = histogram.top();
             palette[p] = entry.color;
             histogram.pop();
     }
}

int Image::findPalette(int color) {
    
    // Verifica se a cor já existe na paleta
    
    for(int p = 0; p < paletteMaxColors; p++)
              if(palette[p] == color) return p;
      
    // Se não foi encontrada na paleta, é necessário buscar pela cor mais próxima
    
    int min = 0, cmin = 0;
    for(int p = 0; p < paletteMaxColors; p++){
              int tmp = (int)sqrt(pow( color - palette[p], 2));
              if(tmp < min){
                     min = tmp;
                     cmin = p;
              }              
    }
    return cmin;
}

void Image::applyPalette() {
      for(int countY = 0; countY < height; countY++){
            for(int countX = 0; countX < width; countX++){
                    int index_pixel = countY*width+countX;
                    int color = pixels[index_pixel];
                    pixels[index_pixel] = findPalette(color);
            }
      }
      usingPalette = true;
}

void Image::resize(int newh, int neww ) {
      if(neww > width)
           increaseWidth(neww);              
      else 
           decreaseWidth(neww);        
      
      
      if(newh > height)
            increaseHeight(newh);              
      else 
            decreaseHeight(newh);       
            
}

void Image::replacePixels(int *tmppixels){
     int *tmp = pixels;
     pixels = tmppixels;
     delete tmp;
}

void Image::increaseWidth(int neww){
     
     int mod = neww % width;
     int copia = mod > 0 ? width / mod : 0;
     int repete = (neww - mod) / width;
     
     int *tmppixels = new int[neww*height]; // Novo buffer para conter os pixels da imagem
     int newx = 0;
     for(int countX = 0; countX < width; countX++){
            int inc = 0;
            if(copia > 0) inc = (countX % copia) == 0 ? 1 : 0;
            for(int rep = 0; rep < repete+inc; rep++){
                for(int countY = 0; countY < height; countY++){
                        int index_pixel = countY*width+countX;
                        int color = pixels[index_pixel];
                        int newindex = countY*neww+newx;
                        tmppixels[newindex] = color;
                }
                newx++;
            }
      }
      replacePixels(tmppixels);
      width = neww;
}

void Image::increaseHeight(int neww){
     
     int mod = neww % height;
     int copia = mod > 0 ? height / mod : 0;
     int repete = (neww - mod) / height;
     
     int *tmppixels = new int[neww*width]; // Novo buffer para conter os pixels da imagem
     int newy = 0;
     for(int countY = 0; countY < height; countY++){
            int inc = 0;
            if(copia > 0) inc = (countY % copia) == 0 ? 1 : 0;
            for(int rep = 0; rep < repete+inc; rep++){
                for(int countX = 0; countX < width; countX++){
                        int index_pixel = countY*width+countX;
                        int color = pixels[index_pixel];
                        int newindex = newy*width+countX;
                        tmppixels[newindex] = color;
                }
                newy++;
            }
      }
      replacePixels(tmppixels);
      height = neww;
}

void Image::decreaseWidth(int neww){
     int mod = width % neww ;
     int copia = mod > 0 ? width / mod : 0;               // Sempre parte do pressuposto que neww != width
     int repete = (width - mod) / neww;
     
     int *tmppixels = new int[neww*height]; // Novo buffer para conter os pixels da imagem
     
     for(int countY = 0; countY < height; countY++){
            for(int countX = 0; countX < neww; countX++){
                    int avg = 0;
                    for(int count = 0; count < repete; count++){
                            int index_pixel = countY*width+(countX*repete)+count;
                            int color = pixels[index_pixel];
                            avg += color;
                    }
                    int newindex = countY*neww+countX;
                    tmppixels[newindex] = avg/repete;
            }
            
      }
     
     replacePixels(tmppixels);
     width = neww;
}

void Image::decreaseHeight(int neww){
     int mod = height % neww ;
     int copia = mod > 0 ? height / mod : 0;               // Sempre parte do pressuposto que neww != width
     int repete = (height - mod) / neww;
     
     int *tmppixels = new int[neww*width]; // Novo buffer para conter os pixels da imagem
     
     for(int countY = 0; countY < neww; countY++){
            for(int countX = 0; countX < width; countX++){
                    int avg = 0;
                    for(int count = 0; count < repete; count++){
                            int index_pixel = ((countY*repete)+count)*width+countX;
                            int color = pixels[index_pixel];
                            avg += color;
                    }
                    int newindex = countY*width+countX;
                    tmppixels[newindex] = avg/repete;
            }
            
      }
     
     replacePixels(tmppixels);
     height = neww;
}

void Image::applyFilter(int radix, int *map){
     int *tmppixels = new int[height*width];
     for(int countY = 0; countY < height; countY++){
            for(int countX = 0; countX < width; countX++){
                    int avg = 0, count = 0;
                    int index_pixel = countY*width+countX;
                    
                    int index_map = 0;
                    for(int ry = countY - radix; ry <= countY + radix; ry++)
                            for(int rx = countX - radix; rx <= countX + radix; rx++){
                                if(rx >= 0 && rx < width && ry >= 0 && ry < height){
                                      avg += pixels[ry*width+rx]* map[index_map];
                                      count += abs(map[index_map]);
                                }
                                index_map++;
                            }
                    int color = avg/count;
                    tmppixels[index_pixel] = color;
            }
            
      }
      replacePixels(tmppixels);
}

void Image::blur(){
     int map[] =  {1, 1, 1, 1, 8, 1, 1, 1, 1};
     applyFilter(1, map );
     /*int map[] =  { 1, 1, 1, 1, 1,
                    1, 3, 3, 3, 1,
                    1, 3, 20, 3, 1,
                    1, 3, 3, 3, 1,
                    1, 1, 1, 1, 1,};
     applyFilter(2, map );
     */
}

void Image::sharpen(){
      int map[] =  {-1, -1, -1, -1, 27, -1, -1, -1, -1};
      applyFilter(1, map );
}
