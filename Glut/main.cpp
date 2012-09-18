
#include <GL/glut.h>
#include <stdlib.h>
#include "Image.h"


static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /*Image img(300, 300);
    
    for(int x = 0; x < 300; x++)
      for(int y = 0; y < 300; y++){
              float fx = (float) x;
              float fy = (float) y;
            img.setPixel(x, y, (fx+fy)/300, (fx+fx)/300, (fy+fy)/300);
      }

    Image i2 = img.blur();
            
            //    img.draw();
      i2.draw();
*/

    Image img((char *)"teste.bmp");
    Image i2 = img.blur();
    i2.draw();
    //img.draw();   
   
   
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

