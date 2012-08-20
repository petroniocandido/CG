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
                    putpixel(countX*2, countY*2, color);
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
