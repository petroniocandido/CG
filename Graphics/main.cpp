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
 
#include <cstdlib>
#include <iostream>
#include <graphics.h>
#include "Image.h"
#include "bitmaps.h"

using namespace std;



int main(int argc, char *argv[])
{
    // Inicializa o modo gráfico
    initwindow(400,400); //open a 400x300 graphics window
    
    // Move o cursor gráfico para o pixel [0,0]
    moveto(100,100);  
    
    Image image(94,121);
    image.load(monalisa121x94);
    
    
    //image.createHistogram();
    //image.showHistogram();
    //image.setPaletteMaxColors(2);
    //image.createPalette();
    //image.applyPalette();
    
    image.resize(188,121);
    
//    image.resize(40,40);
    
    image.draw();

      //image.dump();
    
               
    system("PAUSE");
    closegraph();
    return EXIT_SUCCESS;
}
