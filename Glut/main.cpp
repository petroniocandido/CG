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
 
#include <GL/glut.h>
#include <stdlib.h>
#include "Image.h"


static void display(void)
{
  //  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Image img((char *)"teste.bmp");
    img.draw(0,0);
    
    //Image i2 = img.grayscale(); 
    //i2.draw(240, 0);  
    
    //Image i3 = img.invert();
    //i3.draw(480,0);      
    
    //Image i4 = img.sepia();
    //i4.draw(480,0);
    
    Image i5 = img.blur();
    i5.draw(240,0);
    
    Image i6 = img.sharpen();
    i6.draw(480,0);
    
    glutSwapBuffers();
}

void reshape(int w, int h)
{
   glViewport(0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho (0, w, 0, h, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);
}

/* Program entry point */

int 
main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(800,800);
    glutInitWindowPosition(10,10);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
   
   //glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
   
    glDisable(GL_DITHER);
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);
   
    
    glutCreateWindow("Aula computação gráfica");

    glutDisplayFunc(display);
    
    
    //glutReshapeFunc(reshape); 

    glutMainLoop();

}

