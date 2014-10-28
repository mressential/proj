
#include <GL/glut.h>
#include <iostream>
#include <time.h>
#include <vector>


//#define RASPR_NORM
//#define RASPR_STUP
#define RASPR_P

//#define USLOV_1
#define USLOV_2
//#define USLOV_3

#include "inc/cgraph.hpp"
void DrawCoords()
{
    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_LINES);
        glVertex2d(-graph::width, 0);
        glVertex2d(graph::width, 0);
    glEnd();
    glBegin(GL_LINES);
        glVertex2d(0, -graph::height);
        glVertex2d(0, graph::height);
    glEnd();

    for(long double i = -graph::width; i < graph::width; i += 0.1f)
    {
        glBegin(GL_LINES);
            glVertex2d(i, -0.01);
            glVertex2d(i, 0.01);
        glEnd();
    }
    for(long double i = -graph::height; i < graph::height; i += 0.1f)
    {
        glBegin(GL_LINES);
            glVertex2d(0.01, i);
            glVertex2d(-0.01, i);
        glEnd();
    }
}

void SetColor(shades key)
{
    switch(key)
    {
        case RED:
        {
            graph::color::red = 1.0f;
            graph::color::green = 0.0f;
            graph::color::blue = 0.0f;
        }
        break;
        case GREEN:
        {
            graph::color::red = 0.0f;
            graph::color::green = 1.0f;
            graph::color::blue = 0.0f;
        }
        break;
        case BLUE:
        {
            graph::color::red = 0.0f;
            graph::color::green = 0.0f;
            graph::color::blue = 1.0f;
        }
        break;
        case YELLOW:
        {
            graph::color::red = 1.0f;
            graph::color::green = 1.0f;
            graph::color::blue = 0.0f;
        }
        break;
        case WHITE:
        {
            graph::color::red = 1.0f;
            graph::color::green = 1.0f;
            graph::color::blue = 1.0f;
        }
        break;
        case BLACK:
        {
            graph::color::red = 0.0f;
            graph::color::green = 0.0f;
            graph::color::blue = 0.0f;
        }
        break;
    }
}

long double scale = 8;

void DrawGraf(long double *x, long double *y, unsigned int size)
{
    glColor3f(graph::color::red, graph::color::green, graph::color::blue);
    glBegin(GL_LINE_STRIP);
    for (unsigned int i = 0; i < size; i += 1)
    {
            glVertex2d(x[i], y[i]);
    }
    glEnd();
}

double
                d =
                    #ifdef USLOV_2
                        0.4f,
                    #else
                        0.3f,
                    #endif // USLOV_2

                x_0 = -0.5,
                C =
                    #ifdef USLOV_2
                        0.5f;
                    #else
                        0.3f;
                    #endif // USLOV_2


const int       N = 150;
long double
                x[N],
                y[N],
                yt0[N],

                yt1[N],
                yt2[N],
                maxy[N],
                ksi[N];


long double dx = graph::width/N;

void Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glLoadIdentity();

    DrawCoords();
    SetColor(RED);
    DrawGraf(x,yt2,N);

   // SetColor(BLUE);
   // DrawGraf(x,maxy,N);


  //  SetColor(WHITE);
   // DrawGraf(x,ksi,N);




	glPopMatrix();
	glutSwapBuffers();

}



void Initialize()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-graph::width/2, graph::width/2, -graph::height/2, graph::height/2, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}

#include <cmath>

#ifdef RASPR_NORM
long double MyFunc(long double x, long double _x_0)
{
    return 1.0f*exp(- (x - _x_0)*(x - _x_0)/d/d*graph::width*graph::width);
}
#endif // RASPR_NORM

#ifdef RASPR_STUP
long double MyFunc(long double x, long double _x_0)
{
    return (x > _x_0) ? 1 : 0;
}
#endif // RASPR_STUP

#ifdef RASPR_P
long double MyFunc(long double x, long double _x_0)
{
    if ((x > _x_0)&&(x < (_x_0 + d)))
        return 1;
    return 0;
}
#endif

void move(void)
{

    #ifdef USLOV_1
    for (int i = 2; i < N; i++)
        yt2[i] = (1 - C)*yt1[i] + C*yt1[i-1];
    #endif // USLOV_1

    #ifdef USLOV_2
    for (int i = 1; i < N - 1; i++)
        yt2[i] = -C/2*(yt1[i + 1] - yt1[i - 1]) + 0.5f*C*C*(yt1[i + 1] - 2*yt1[i] + yt1[i - 1]) + yt1[i];
    #endif // USLOV_2

    #ifdef USLOV_3
    for (int i = 2; i < N ; i++)
        yt2[i] = -2*C*(yt1[i] - yt1[i-1]) - (yt1[i-1] - yt0[i-1]) + yt1[i];
    #endif // USLOV_3


    #ifdef RASPR_NORM
    double _max = 0.0f;
    int j = 0;
    #endif // RASPR_NORM




    for (int i = 0; i < N; i++)
    {
        yt0[i] = yt1[i];
    }

    for (int i = 2; i < N; i++)
    {
        #ifdef RASPR_NORM
        if (yt2[i] > _max)
        {
            _max = yt2[i];
            j = i;
        }
        #endif // RASPR_NORM
        yt1[i] = yt2[i];
    }
    #ifdef RASPR_NORM
    maxy[j] = _max;
    double temp = MyFunc(x[j], x[j]);
    if ((temp - _max) < 0)
        ksi[j] = -(temp - _max)/temp;
    else
        ksi[j] = (temp - _max)/temp;
    #endif // RASPR_NORM

}


void initFUNC()
{
    for (int i = 0; i < N; i++)
    {
        x[i] = -graph::width/2 + (long double)(dx*i);
    }
    for (int i = 0; i < N; i++)
    {
        y[i] = MyFunc(x[i], x_0);
        yt1[i] = y[i];
        yt2[i] = y[i];
    }
}


void Timer(int value)
{
    move();
    glutPostRedisplay();
    glutTimerFunc(33, Timer, 0);
}


int main(int argc, char** argv)
{
    initFUNC();
    Initialize();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(window::width, window::height);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("g");
	glutDisplayFunc(Draw);
    glutTimerFunc(1000, Timer, 0);

	glutMainLoop();

	return 0;
}
