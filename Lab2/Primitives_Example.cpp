#include <windows.h>
#include <stdlib.h>
#include <math.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glaux.h>
#include <ctime>
#include <cmath>
struct XYZ {
	GLfloat X;
	GLfloat Y;
	GLfloat Z;
};

struct RGB {
	GLfloat R;
	GLfloat G;
	GLfloat B;
};


struct PointObj {
	XYZ position;
	RGB color;
};

PointObj Black = { {-3, -3, 3}, {0,0,0} };
PointObj Blue = { {3, -3, 3}, {0,0,1} };
PointObj Magenta = { {3, -3, -3}, {1,0,1} };
PointObj Red = { {-3, -3, -3}, {1,0,0} };
PointObj Green = { {-3, 3, 3}, {0,1,0} };
PointObj Cyan = { {3, 3, 3}, {0,1,1} };
PointObj White = { {3, 3, -3}, {1,1,1} };
PointObj Yellow = { {-3, 3, -3}, {1,1,0} };

void drawPoint(PointObj point) {

	glColor3f(point.color.R, point.color.G, point.color.B);
	glVertex3f(point.position.X, point.position.Y, point.position.Z);
}


void DrawScene(GLfloat xRot, GLfloat yRot) 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glLoadIdentity();

    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	//glBegin(GL_LINES);
	//	glColor3f(1,1,1);
	//	glVertex3f(10,0,0);
	//	glVertex3f(-10,0,0);
	//	glVertex3f(0,10,0);
	//	glVertex3f(0,-10,0);
	//	glVertex3f(0,0,10);
	//	glVertex3f(0,0,-10);
	//glEnd();

	//glBegin(GL_QUADS);
	//	glColor3f(0,1,0);
	//	glVertex3f(-3,-3,-5);
	//	glVertex3f(-3,3,-5);
	//	glVertex3f(3,3,-5);
	//	glVertex3f(3,-3,-5);

	//	glColor3f(0,0,1);
	//	glVertex3f(-3,-3,5);
	//	glVertex3f(-3,3,5);
	//	glVertex3f(3,3,5);
	//	glVertex3f(3,-3,5);
	//glEnd();

	glBegin(GL_QUADS);
		drawPoint(Black);
		drawPoint(Blue);
		drawPoint(Cyan);
		drawPoint(Green);

		drawPoint(Red);
		drawPoint(Yellow);
		drawPoint(White);
		drawPoint(Magenta);

		drawPoint(Blue);
		drawPoint(Magenta);
		drawPoint(White);
		drawPoint(Cyan);

		drawPoint(Red);
		drawPoint(Black);
		drawPoint(Green);
		drawPoint(Yellow);

		drawPoint(Green);
		drawPoint(Cyan);
		drawPoint(White);
		drawPoint(Yellow);

		drawPoint(Black);
		drawPoint(Red);
		drawPoint(Magenta);
		drawPoint(Blue);
	glEnd();
	glFinish();
}

void SetMyPixelFormat(HDC hdc) 
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(pfd));
	pfd.nSize = sizeof(pfd);
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 16;
	pfd.iLayerType = PFD_MAIN_PLANE;

	int nPixelFormat = ChoosePixelFormat(hdc, &pfd);
	SetPixelFormat(hdc, nPixelFormat, &pfd);
}
void ResizeWindow(int width, int height)
{


	if (height*width==0) return;
	glViewport(0,0,width,height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-10, 10, -10, 10, -10, 10) -> TAK BY£O;
	
	//GLfloat aspectRatio = (GLfloat)width / (GLfloat)height;
	//glOrtho(-10, 10, -10.0 / aspectRatio, 10.0 / aspectRatio, -10, 10);
	
	GLfloat aspectRatio = (GLfloat)height/ (GLfloat)width;
	glOrtho(-10.0 / aspectRatio, 10.0 / aspectRatio ,-10, 10, -10, 10);

	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	//glEnable(GL_DEPTH_TEST); TO BY£O
	//glEnable(GL_CULL_FACE);

	//+
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);
	glShadeModel(GL_SMOOTH);


}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	static HGLRC hrc;
	static GLfloat xRot = 0.0f;
	static GLfloat yRot = 0.0f;

	switch (message) 
	{
	case WM_SIZE: 
		ResizeWindow(LOWORD(lParam),HIWORD(lParam));
		break;
	case WM_CREATE:
		hdc = GetDC(hWnd);
		SetMyPixelFormat(hdc);
		hrc = wglCreateContext(hdc);
		wglMakeCurrent(hdc, hrc);
		ReleaseDC(hWnd, hdc);
		break;
	case WM_KEYDOWN:
		if(wParam==VK_UP) xRot-= 5.0f;
		if(wParam==VK_DOWN) xRot += 5.0f;
		if(wParam==VK_LEFT) yRot -= 5.0f;
		if(wParam==VK_RIGHT) yRot += 5.0f;

		if(xRot > 356.0f) xRot = 0.0f;
		if(xRot < -1.0f) xRot = 355.0f;
		if(yRot > 356.0f) yRot = 0.0f;
		if(yRot < -1.0f) yRot = 355.0f;
		
		InvalidateRect(hWnd,NULL,FALSE);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		DrawScene(xRot, yRot);
		SwapBuffers(hdc);
		EndPaint(hWnd, &ps);		
		break;
	case WM_ERASEBKGND:
		return 1;
		break;
	case WM_DESTROY:
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(hrc);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX); 
	wcex.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= NULL;
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= "Primitives";
	wcex.hIconSm		= NULL;
	return RegisterClassEx(&wcex);
}
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;
   hWnd = CreateWindow("Primitives", "Primitives", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
   if (!hWnd) return FALSE;
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   return TRUE;
}
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	MyRegisterClass(hInstance);
	if (!InitInstance(hInstance, nCmdShow)) return FALSE;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int) msg.wParam;
}


