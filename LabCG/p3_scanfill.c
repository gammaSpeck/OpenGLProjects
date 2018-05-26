#include<GL/glut.h>
#include<stdio.h>
int x0,x1,x2,x3,y0,y1,y2,y3;
int flag=0;

void scanfill( int a,int b,int c,int d,int e,int f,int g,int h);
void edge(int a0,int b0,int a1,int b1,float *p,float *q);
void scan_menu(int id);

void init()
{
 
 gluOrtho2D(0,500,0,500);

}
void display()
{   glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1,0,0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x0,y0);
    glVertex2f(x1,y1);
    glVertex2f(x2,y2);
    glVertex2f(x3,y3);

    glEnd();
 if(flag==0)
  {
    scanfill(x0,y0,x1,y1,x2,y2,x3,y3);
  }
     glFlush();
}

void scanfill( int a,int b,int c,int d,int e,int f,int g,int h)
{  int i,j;
   float le[500],re[500];
   for(i=0;i<500;i++)
     {
        le[i]=500;
        re[i]=0;
     }
   edge(a,b,c,d,le,re);
   edge(c,d,e,f,le,re);
   edge(g,h,e,f,le,re);
   edge(a,b,g,h,le,re);
    
    for(i=0;i<500;i++)
      {
         if(le[i]<re[i])
           for(j=le[i];j<re[i];j++)
              {       glColor3f(0,1,0);
                      glBegin(GL_POINTS);
                      glVertex2f(j,i);
                      glEnd();
               }
      }
}
void edge(int a0,int b0,int a1,int b1,float *p,float *q)
{
   float x,m;
   m=(b1-b0)/(a1-a0);
   x=a0;
   for(int i=b0;i<b1;i++)
     {
       if(x<p[i])
            p[i]=x;
       if(x>q[i])
            q[i]=x;
        x+=1/m;
     }
}

void scan_menu(int id)
{
  if(id==1)
    flag=0;
  if(id==2)
    flag=1;
 display();
}

int main(int argc,char **argv)
{ 
  printf("ENTER THE VALUES OF x0-y0,x1-y1...x3-y3 resp\n");
  scanf("%d%d%d%d%d%d%d%d",&x0,&y0,&x1,&y1,&x2,&y2,&x3,&y3);
 glutInit(&argc,argv);
 glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
 glutInitWindowPosition(50,50);
 glutInitWindowSize(500,500);
 glutCreateWindow("SCANLINE");
 glutCreateMenu(scan_menu);
 glutAddMenuEntry("FILL",1);
 glutAddMenuEntry("Clear",2);
 glutAttachMenu(GLUT_RIGHT_BUTTON);
 init();
 glutDisplayFunc(display);
 glutMainLoop();
 return 0;
}

