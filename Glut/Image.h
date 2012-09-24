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
 

#include <GL\glut.h>

using namespace std;

 class Image 
   {
   private:
      float *pixels; 
      int height, width, size;
      void replacePixels(Image img);
      int calcIndex(int px, int py);
   public:
      float getPixel(int x, int y, int color);
      Image increaseWidth(int dw);
      Image increaseHeight(int dh);
      Image decreaseWidth(int dw);
      Image decreaseHeight(int dh);

      Image(int h, int w);
      Image(char * );
      ~Image();
      void setPixel(int x, int y, float r, float g, float b);
      float getPixelR(int x, int y);
      float getPixelG(int x, int y);
      float getPixelB(int x, int y);
      void load();
      void draw();
      void draw(int x, int y);
      Image applyFilter(int radix, int *map);
      Image blur();
      Image sharpen();
      Image resize(int neww, int newh);
      Image invert();
      Image grayscale();
      Image sepia();
      Image colorFilter(float *map);
      Image swap();
      Image Degrade(float r, float g, float b, int d);
      Image applyRotate(float ang);
   };


