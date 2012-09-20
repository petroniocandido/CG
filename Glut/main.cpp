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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Image img((char *)"teste.bmp");
    Image i2 = img.blur(); 
    i2.draw();  
    glutSwapBuffers();
}


/* Program entry point */

int 
main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    
    glViewport(0, 0, 0, 0); 
    gluOrtho2D(0,0,0,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    glutCreateWindow("Aula computação gráfica");

    glutDisplayFunc(display);

    glutMainLoop();

}

