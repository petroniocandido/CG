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

/************************************************************

 *  Inicializa o modo VGA/SVGA.										*

 ************************************************************/

void InitVGA(void)

{

	int  Gd, Gm;

	char GrErr;



	Gd=installuserdriver("svga256",NULL); Gm=0;



	/* A variavel Gm deve assumir um dos seguintes valores, de acordo com

		a resolucao desejada:



		0. 320x200x256

		1. 640x400x256

		2. 640x480x256

		3. 800x600x256

		4. 1024x768x256

		5. 640x350x256

		6. 1280x1024x256 */



	initgraph(&Gd,&Gm,"");



	GrErr = graphresult();

	if (GrErr != grOk) {

	  printf("Erro grafico: %s\n",grapherrormsg(GrErr));

	  exit(1);

	}

}


int main(int argc, char *argv[])
{
    // Inicializa o modo gráfico
    //initwindow(400,400); //open a 400x300 graphics window
    
    InitVGA();
    
    // Move o cursor gráfico para o pixel [0,0]
    moveto(100,100);  
    
    Image image(100,100);
    image.load(peixe100x100);
    
    
    //image.createHistogram();
    //image.showHistogram();
    //image.setPaletteMaxColors(2);
    //image.createPalette();
    //image.applyPalette();
    
//    image.resize(188,121);
    
//    image.resize(40,40);
      int mapA[] =  {1, 1, 1, 1, 0, 1, 1, 1, 1};
      int mapB[] =  {0, 0, 0, 0, 1, 0, 0, 0, 0};
      int mapC[] =  {-1, -1, -1, -1, 8, -1, -1, -1, -1};
    //  image.applyFilter(1, mapA );
    
    image.draw();

      //image.dump();
    
               
    system("PAUSE");
    closegraph();
    return EXIT_SUCCESS;
}
