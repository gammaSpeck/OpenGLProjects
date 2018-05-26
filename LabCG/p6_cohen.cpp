#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>

float xmin =50,xmax=100,ymin=50,ymax=100;	//The small square dimensions
float x0=60,y0=20,x1=80,y1=120;				//The line that cuts through the window

const int left=8, right=2, bottom=1, top=4;
float m=(y1-y0)/(x1-x0);					//Slope

int compute(int x,int y);
void cohen();

int compute(int x,int y)		//The clipper which returns which clipper code to be applied
{
   	int code=0;
 	if(x<xmin)					//Assign Left clipper code
 		code|=left;

 	if(x>xmax)					//Assign Right clipper code
  		code|=right;

  	if(y<ymin)					//Assign Bottom clipper code
   		code|=bottom;
 
 	if(y>ymax)					//Assign Top clipper code
   		code|=top;

	return code;
}

void cohen()
{ 
	float x=0.0,y=0.0;			//The points to be found
  	int code0,code1,codeout;
  	bool done=false;
  	bool accept=false;
  
	code0=compute(x0,y0);		//Find the code of the 2 points to determine if it cuts through window
	code1=compute(x1,y1);

	do
	{   
 		codeout=code0?code0:code1;		// See what clipping to do then apply necessary equations

 		printf("Codeout: %d\n",codeout);		//Shows what clipping is about to happen
           
        if(!(code0|code1))			//Means line is fully in
             {
                  done=true;
                  accept=true;
              }
        else if(code0 & code1)		//Means line is completely out
             {
                     done=true;
              }
        else						//Means line is partial in, partial out
            {
                 if(codeout & top)		//Line cuts through top edge THUS, y=ymax
                    {
                      x=x0+((1/m)*(ymax-y0));
                      y=ymax;
                    }
                  
                 if(codeout & bottom)	//Line cuts through bottom edge THUS, y=ymin
                   {
                      x=x0+((1/m)*(ymin-y0));
                      y=ymin;
                    }
             
                 if(codeout & left)		//Line cuts through left edge THUS, x=xmin
                   {
                      y=y0+(m*(xmin-x0));
                      x=xmin;
                    }

                 if(codeout & right)	//Line cuts through right edge THUS, x=xmax
                   {
                      y=y0+(m*(xmax-x0));
                      x=xmax;
                    }
                 
               if(codeout==code0)		//This shows first end point after clipping the line
                 {
                       x0=x;
                       y0=y;
                       code0=compute(x0,y0);
                       printf("X0=%f Y0=%f\n",x0,y0); 
                 }
               if(codeout==code1)		//This shows second end point after clipping the line
                 {
                       x1=x;
                       y1=y;
                       code1=compute(x1,y1);
                       printf("x1=%f y1=%f",x1,y1);
                 }
          }
	}while(!done);						//Untill all clippins are done

   if(accept)		//Means after clipping is done
    {   
         
         glTranslatef(100,0,0);		//Move origin to new loc z val is 0 as its 2D- Over here is where clipped fig is seen (Here, shift a lil right)
         glColor3f(0,0,0);				//The line loop color
         glBegin(GL_LINE_LOOP);
		     glVertex2f(xmin,ymin);
		     glVertex2f(xmax,ymin);
		     glVertex2f(xmax,ymax);
		     glVertex2f(xmin,ymax);
         glEnd();
         glColor3f(1,0,0);				//The cutting line color
         glBegin(GL_LINES);
		     glVertex2f(x0,y0);
		     glVertex2f(x1,y1);
         glEnd();
         glFlush();
      
    } 
}


void display()
{   
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);
	
	glTranslatef(100,200,0);			//This is done for making the fig come in the center
	
	glColor3f(0,0,0);					//The line loop color
	glBegin(GL_LINE_LOOP);
		glVertex2f(xmin,ymin);
		glVertex2f(xmax,ymin);
		glVertex2f(xmax,ymax);
		glVertex2f(xmin,ymax);
	glEnd();
	glColor3f(1,0,0);					//The inner line color
	glBegin(GL_LINES);
		glVertex2f(x0,y0);
		glVertex2f(x1,y1);
	glEnd();
	cohen();	
}


void init()
{
   gluOrtho2D(0,500,0,500);				//Sets view volume- By changing this, we can change how close our cam is to fig, thereby making it seem bigger
}

int main(int argc,char **argv)
{ 
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);

	glutInitWindowPosition(0,0);
	glutInitWindowSize(500,500);
	glutCreateWindow("CLIP WINDOW");

	init();
	glutDisplayFunc(display);

	glutMainLoop();
	return 0;
}











