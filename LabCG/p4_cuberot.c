#include<GL/glut.h>
#include<stdio.h>

float v[8][3]={{-1,-1,-1},{-1,1,-1},{1,1,-1},{1,-1,-1},
	       {-1,-1,1},{-1,1,1},{1,1,1},{1,-1,1}};
float theta[3]={0,0,0};
int axis=1;

void colorcube();
void polygon(int a,int b,int c,int d);
void mouse(int x,int y,int button,int state);


void display()
{   
	glClearColor(1,1,1,1);
     glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
     glLoadIdentity();
     
     glRotatef(theta[2],0,0,1);
     glRotatef(theta[1],0,1,0);
     glRotatef(theta[0],1,0,0);

	
    colorcube();

    glFlush();
    glutSwapBuffers();
}



void colorcube()
{
   glColor3f(1,0,0);
   polygon(0,1,5,4);

   glColor3f(0,1,0);
   polygon(2,6,7,3);

   glColor3f(0,0,1);
   polygon(1,5,6,2);

   glColor3f(1,0,1);
   polygon(0,4,7,3);

   glColor3f(1,1,0);
   polygon(0,1,2,3);

   glColor3f(0,0,0);
   polygon(4,5,6,7);

}
void polygon(int a,int b,int c,int d)
{
   glBegin(GL_POLYGON);
   glVertex3fv(v[a]);
   glVertex3fv(v[b]);
   glVertex3fv(v[c]);
   glVertex3fv(v[d]);
   glEnd();
}

void mouse(int button,int state,int x,int y)
{
   if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
      axis=0;
   if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
      axis=1;
   if(button==GLUT_MIDDLE_BUTTON && state==GLUT_DOWN)
      axis=2;
    display();
}
void spin()
{
theta[axis]+=1;

    display();
}

void init()
{
 glMatrixMode(GL_PROJECTION);
 glOrtho(-2,2,-2,2,-2,2);
 glMatrixMode(GL_MODELVIEW);

}

int main(int argc,char **argv)
{ 
 glutInit(&argc,argv);
 glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);

 glutInitWindowPosition(0,0);
 glutInitWindowSize(500,500);
 glutCreateWindow("CUBE");

 init();
 glutDisplayFunc(display);

 glutMouseFunc(mouse);
 glutIdleFunc(spin);

 glEnable(GL_DEPTH_TEST);
 glutMainLoop();
 return 0;
}
