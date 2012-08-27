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

using namespace std;

int img[] = {
0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
0,	0,	0,	0,	0,	0,	0,	2,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
0,	0,	0,	0,	0,	0,	2,	2,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
0,	0,	0,	0,	0,	2,	1,	1,	2,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
0,	0,	0,	0,	0,	1,	1,	1,	1,	2,	0,	0,	0,	0,	0,	0,	2,	2,	0,	0,
0,	0,	0,	0,	2,	1,	1,	1,	1,	1,	2,	0,	0,	0,	0,	2,	1,	2,	0,	0,
0,	0,	0,	2,	1,	1,	1,	1,	1,	1,	1,	2,	0,	0,	2,	1,	1,	0,	0,	0,
0,	0,	2,	1,	1,	3,	3,	3,	1,	1,	1,	1,	2,	2,	1,	1,	2,	0,	0,	0,
0,	2,	1,	1,	1,	3,	5,	3,	1,	1,	1,	1,	1,	1,	1,	2,	0,	0,	0,	0,
2,	1,	1,	1,	1,	3,	3,	3,	1,	1,	1,	1,	1,	1,	2,	0,	0,	0,	0,	0,
2,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	2,	0,	0,	0,	0,	0,
0,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	2,	0,	0,	0,	0,
0,	2,	2,	1,	1,	1,	1,	1,	1,	1,	1,	1,	2,	2,	1,	1,	2,	0,	0,	0,
0,	0,	0,	2,	1,	1,	1,	1,	1,	1,	1,	2,	0,	0,	2,	1,	1,	0,	0,	0,
0,	0,	0,	0,	2,	1,	1,	1,	1,	1,	2,	0,	0,	0,	0,	2,	1,	2,	0,	0,
0,	0,	0,	0,	0,	2,	1,	1,	1,	2,	0,	0,	0,	0,	0,	0,	2,	2,	0,	0,
0,	0,	0,	0,	0,	2,	1,	1,	2,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
0,	0,	0,	0,	0,	0,	2,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
0,	0,	0,	0,	0,	0,	0,	2,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,
0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0
};

int main(int argc, char *argv[])
{
    // Inicializa o modo gráfico
    initwindow(200,200); //open a 400x300 graphics window
    
    // Move o cursor gráfico para o pixel [0,0]
    moveto(0,0);  
    
    Image image(20,20);
    image.load(img);
    
    
    //image.createHistogram();
    //image.showHistogram();
    //image.setPaletteMaxColors(2);
    //image.createPalette();
    //image.applyPalette();
    
    image.resize(80,80);
    
    image.resize(40,80);
    
    image.draw();
    
               
    system("PAUSE");
    closegraph();
    return EXIT_SUCCESS;
}
