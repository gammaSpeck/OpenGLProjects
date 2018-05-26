#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
typedef float point[3];		//User defined datatype

point v[]={{0,0,1}, {-1,-1,-1},{0,1,-1}, {1,-1,-1}};	//Tetrahedron's points
float theta[] = {0,0,0};
int n;


void triangle( point a, point b, point c)
{
	glBegin(GL_POLYGON);
	glNormal3fv(a);
		glVertex3fv(a);
		glVertex3fv(b);
		glVertex3fv(c);
	glEnd();
}


void divide_triangle(point a, point b, point c, int m)		//m is the number of times to cut the triangle into
{
	point v1, v2, v3;
	int j;
	if(m>0)													//Until it's cut m times, keep halving it...
	{
		for(j=0; j<3; j++) 
			v1[j]=(a[j]+b[j])/2;
		for(j=0; j<3; j++)
			v2[j]=(a[j]+c[j])/2;
		for(j=0; j<3; j++) 
			v3[j]=(b[j]+c[j])/2;
		divide_triangle(a, v1, v2, m-1);
		divide_triangle(c, v2, v3, m-1);
		divide_triangle(b, v3, v1, m-1);
	}
	else
		triangle(a,b,c); 									//Keeps drawing all the tiny cut up triangles
}
 
 
void tetrahedron(int m)										//Since there are 4 triangles, all 4 must be divided m times
{
	glColor3f(1,0,0);
		divide_triangle(v[0], v[1], v[2], m);
	glColor3f(0,1,0);
		divide_triangle(v[3], v[2], v[1], m);
	glColor3f(0,0,1);
		divide_triangle(v[0], v[3], v[1], m);
	glColor3f(0,1,1);
		divide_triangle(v[0], v[2], v[3], m);
}


void display()
{
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		//As the tetrahedron IS a 3D obj
	glLoadIdentity();
	tetrahedron(n);
	glFlush();
}


void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2,2,-2,2,-10,10);			//Viewing volume
	glMatrixMode(GL_MODELVIEW);
	display();
}


void main(int argc, char **argv)
{
	printf(" No. of Divisions ? ");
	scanf("%d",&n);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);								//By default WindowPosition is 0,0
	glutCreateWindow("3D Gasket");
	init();
	glutDisplayFunc(display);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}




