#include<stdio.h>
#include<GL/glut.h>
void wall(double thickness)	
{
    glPushMatrix();
	    glTranslated(0.5,0.5*thickness,0.5);
	    glScaled(1.0,thickness,1.0);
	    glutSolidCube(1.0);
    glPopMatrix();
}

void tableLeg(double thick,double len)
{
    glPushMatrix();
	    glTranslated(0,len/2,0);
	    glScaled(thick,len,thick);
	    glutSolidCube(1.0);
    glPopMatrix();
}

void table(double topWid,double topThick,double legThick,double legLen)
{
    glPushMatrix();
	    glTranslated(0,legLen,0);
	    glScaled(topWid,topThick,topWid);		//Square faced table top			
	    glutSolidCube(1.0);
    glPopMatrix();

    double dist=0.95*topWid/2.0-legThick/2.0;		//The dist of how in the legs are gonna be from table top face

    glPushMatrix();					//We translate each time to draw the 4 legs- The y cood is 0
	    glTranslated(dist,0,dist);			//Front leg
	    tableLeg(legThick,legLen);

	    glTranslated(0,0,-2*dist);			//Right leg
	    tableLeg(legThick,legLen);

	    glTranslated(-2*dist,0,0);			//Back leg
	    tableLeg(legThick,legLen);

	    glTranslated(0,0,2*dist);			//Left leg
	    tableLeg(legThick,legLen);
    glPopMatrix();
}


void setStage()
{
	GLfloat xlight[]={0.7,0.7,0.7,0.7};
	GLfloat mat_diffuse[]={0.5,0.5,0.5,1};
	GLfloat mat_shininess[]={50};

	//The glMaterialfv function specifies material parameters for the lighting model.
	glMaterialfv(GL_FRONT,GL_AMBIENT,xlight);
	glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
	glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);

	GLfloat light_position[]={2,6,3,0};

	//The glLightfv function returns light source parameter values.
	glLightfv(GL_LIGHT0,GL_POSITION,light_position);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,xlight);


}

void displaySolid(void)
{
	setStage();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-1.33,1.33,-1,1,-1,4);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
 
    gluLookAt(2.3,1,2,0,0.25,0,0,1,0);			//Cam position
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
	    glTranslated(0.5,0.4,0.5);
	    glRotated(30,0,1,0);		//Rotate the teapot y axis so that it is facing cam
	    glutSolidTeapot(0.08);
    glPopMatrix();

    
    glPushMatrix();
    	glTranslated(0.4,0,0.4);
    	table(0.6,0.02,0.02,0.3);
    glPopMatrix();

    wall(0.02);			//First wall is actually the floor
    glPushMatrix();
	    glRotated(90,0,0,1);    //draw second wall after rotating x axis by 90degrees
	    wall(0.02);			//Left wall
    glPopMatrix();
    glPushMatrix();
	    glRotated(-90,1,0,0);   //Now rotate again
	    wall(0.02);			//Right wall
    glPopMatrix();
    glFlush();
}

int main(int argc,char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Simple shaded scene consisting of a teapot");
    glutDisplayFunc(displaySolid);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);			//To ensure 3D modelling is possible
    glEnable(GL_NORMALIZE);
    glClearColor(0.1,0.1,0.1,0);
    glutMainLoop();
  }
