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
 
#include <queue>
#include <iostream>

using namespace std;

struct histogram_entry {
       int color;
       int frequency;
};

struct CompareHistogramEntry  
{  
  bool operator()(const histogram_entry& l, const histogram_entry& r)  
  {  
      return l.frequency < r.frequency;  
  }  
};  

 class Image 
   {
   private:
      priority_queue<histogram_entry,vector<histogram_entry>, CompareHistogramEntry > histogram;  
      int *palette;
      int *pixels; 
      int height, width;
      bool usingPalette;
      int paletteMaxColors;   
      
      int findPalette(int color);   
      void increaseWidth(int dw);
      void increaseHeight(int dh);
      //void decreaseWidth(int dw);
      //void decreaseHeight(int dh);
   public:
      Image(int h, int w);
      ~Image();
      void setPixel(int x, int y, int color);
      int getPixel(int x, int y);
      void createHistogram();
      void showHistogram();
      void createPalette();
      void applyPalette();
      void setPaletteMaxColors(int m);
      int getHeight();
      int getWidth();
      void draw();
      void load(int *bmp);
      void resize(int neww, int newh);
   };


