#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
#include<stdlib.h>
#include<GL/gl.h>

float triangle[3][3]= {{150,250,350},{200,400,200},{1,1,1}};
float rot_mat[3][3]={{0},{0},{0}};
float result[3][3]={{0},{0},{0}};
float h=10,k=10;
float m=0,n=0;
float theta;




void multiply()
{
int i,j,l;
for(i=0;i<3;i++)
    for(j=0;j<3;j++)
    {
        result[i][j]=0;
        for(l=0;l<3;l++)
            result[i][j]=result[i][j]+rot_mat[i][l]*triangle[l][j];
    }}


void rrotate(float m,float n)
{

    rot_mat[0][0]=cos(theta);
    rot_mat[0][1]=-sin(theta);
    rot_mat[0][2]=m;
    rot_mat[1][0]=sin(theta);
    rot_mat[1][1]=cos(theta);
    rot_mat[1][2]=n;
    rot_mat[2][0]=0;
    rot_mat[2][1]=0;
    rot_mat[2][2]=1;
    multiply();
}

void drawtri()
{
    glBegin(GL_TRIANGLES);
    glColor3f(1,0.5,0);
    glVertex2f(triangle[0][0],triangle[1][0]);
    glVertex2f(triangle[0][1],triangle[1][1]);
    glVertex2f(triangle[0][2],triangle[1][2]);
    glEnd();
    glFlush();   
}

void drawrotatetriangle()
{
    glBegin(GL_TRIANGLES);
    glVertex2f(result[0][0],result[1][0]);
    glVertex2f(result[0][1],result[1][1]);
    glVertex2f(result[0][2],result[1][2]);
    glEnd();
}


void display()
{
    glClearColor(0.1,0.1,0.1,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
   
    glColor3f(1,0,0);
    drawtri();
   
    rrotate(0,0);
    glColor3f(1,1,0);
    drawrotatetriangle();
   
    m=-h*(cos(theta)-1)+k*(sin(theta));
    n=-k*(cos(theta)-1)-h*(sin(theta));
    rrotate(m,n);
    glColor3f(0,0,1);
    drawrotatetriangle();
    glFlush();
   
}

void init()
{
    glClearColor(0.1,0.1,0.1,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,500,0,500);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc,char ** argv)
{

printf("Enter the rotating angle \n");
scanf("%f",&theta);
theta=((3.14/180)*theta);

printf("Enter the x and y value for fixed point\n");
scanf("%f%f",&h,&k);

glutInit(&argc,argv);
glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
glutInitWindowPosition(0,0);
glutInitWindowSize(500,500);
glutCreateWindow("line");

glutDisplayFunc(display);
init();
//glutKeyboardFunc(keys);
glutMainLoop();
}
