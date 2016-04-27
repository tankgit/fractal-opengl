// 2016/04/27  Tank derektanko@gmail.com
//
// Fractal with OpenGL

#include<GL/glut.h>
#include<stdlib.h>
#include<math.h>


void myinit()
{
	glClearColor(0.0,0.0,0.0,0.0);
}

void ChangeSize(GLsizei w,GLsizei h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat x=2.0;
	if(w<=h)
		glOrtho(-x,x,-x*(GLfloat)h/(GLfloat)w,x*(GLfloat)h/(GLfloat)w,-100.0,100.0);
	else 
		glOrtho(-x/(GLfloat)h*(GLfloat)w,x/(GLfloat)h*(GLfloat)w,-x,x,-100.0,100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


typedef struct com{
	float real;
	float vir;
}com;


com cmul(com a,com b)
{
	com c;
	c.real=a.real*b.real-a.vir*b.vir;
	c.vir=a.real*b.vir+a.vir*b.real;
	return c;
}

com cadd(com a,com b)
{
	com c;
	c.real=a.real+b.real;
	c.vir=a.vir+b.vir;
	return c;
}

float m(com a)
{
	return sqrt(a.real*a.real+a.vir*a.vir);
}

float cfunc(com a,int iter)
{
	//const c: real part affects pattern complication, virtual part affects symmetry
	com c={-1,0.3};
	if(iter)
	{
		com d=cadd(cmul(a,a),c);
		com e=cadd(cmul(d,d),c);
		return cfunc(e,--iter);
	}	
	else return (int)(m(a)/4*10);
}

void RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	float i,j;
	glBegin(GL_POINTS);
	float d;
	com a;

	//draw the fractal point
	for(i=-2;i<=2;i+=0.01)
		for(j=-2;j<=2;j+=0.01)
		{
			a.real=i;
			a.vir=j;
			d=cfunc(a,6);
			d=d/10;
			glColor3f(d,d*1.2,d*1.5);
			glVertex2f(i,j);
		}

	glEnd();
	glFlush();
}

int main(int argc,char *argv[])
{
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(50,100);
	glutInit(&argc,argv);
	glutCreateWindow("fractal");
	
	myinit();

	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);

	glutMainLoop();

	return 0;
}

