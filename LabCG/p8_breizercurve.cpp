#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include<math.h>

void beizercoeff(int n,float *c)
{
    for(int k=0;k<=n;k++)
      {
         c[k]=1.0;

       for(int i=n;i>=k+1;i--)
          c[k]*=i;

       for(int i=n-k;i>=1;i--)
           c[k]/=i;
      }
}
void display()
{

 glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);

    int cp[3][2]={{10,10},{150,850},{200,10}};
    int n=2;
    float c[3];
 
    beizercoeff(n,c);
   

    glColor3f(1,0,0);
    glLineWidth(5.0);
    glBegin(GL_LINE_STRIP);
    for(float u=0;u<=1;u+=0.1)
      {
          float x=0;
           float y=0;
              
              for(int k=0;k<=n;k++)
                {
                   float blend=c[k]*pow(u,k)*pow(1-u,n-k);
                    x+=cp[k][0]*blend;
                    y+=cp[k][1]*blend;

                }
                   
                     glVertex2f(x,y);

      }
         glEnd();
         glFlush();
      
     
}

void init()
{
 glMatrixMode(GL_PROJECTION);
 gluOrtho2D(0,1000,0,1000);
 glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{

glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );

glutInitWindowPosition(0, 0);
glutInitWindowSize(1000, 1000);
glutCreateWindow("beizercoeff");

init();
glutDisplayFunc(display);

glutMainLoop();
return 0;
}
