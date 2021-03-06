/*
 * CG - C�digos gerados para a disciplina de Computa��o Gr�fica
 * Copyright (C) 2012 Petr�nio C�ndido de Lima e Silva.
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
#include <dos.h>
#include <io.h>
#include <fcntl.h>
#include "Image.h"
#include "bitmaps.h"
//#include "VGA.h"



using namespace std;



int main(int argc, char *argv[])
{
    
    // Inicializa o modo gr�fico
    initwindow(500,500); //open a 400x300 graphics window
    
    // Move o cursor gr�fico para o pixel [0,0]
    moveto(100,100);  
    
    Image image(94,120);
    image.load(monalisa94x120);
        
   image.resize(282,240);
    
    image.draw(0,0);
    
   image.sharpen();  

/*    
    image.createHistogram();
    image.createPalette();
    image.applyPalette();
*/    
    image.draw(260,0);

      //image.dump();
    
    system("PAUSE");
    
    closegraph();
         
    
    
    return EXIT_SUCCESS;
    
}
