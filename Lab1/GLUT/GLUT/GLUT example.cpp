#include<windows.h>
#include<GL/gl.h>
#include"glut-3.7.6-bin/glut.h"

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(-0.5, -0.5);
    glVertex2f(0.0, 0.5);
    glVertex2f(0.5, -0.5);
    glEnd();
    glFinish();
}

int main(int argc, CHAR* argv[])
{
    glutInitWindowSize(400, 300);
    glutInitWindowPosition(100, 100);
    glutInitDisplayMode(GLUT_RGB);
    glutCreateWindow("GLUT");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
