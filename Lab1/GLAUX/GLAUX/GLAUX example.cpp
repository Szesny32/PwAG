#include<windows.h>
#include<GL/gl.h>
#include<GL/glaux.h>

void CALLBACK Resize(GLsizei, GLsizei)
{

}

void CALLBACK Idle(void)
{

}

void CALLBACK Render(void)
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
    auxInitDisplayMode(AUX_SINGLE + AUX_RGBA);
    auxInitPosition(100, 100, 400, 400);
    auxInitWindow(L"GLAUX");

    auxReshapeFunc(Resize);
    auxIdleFunc(Idle);
    auxMainLoop(Render);
    return 0;
}

