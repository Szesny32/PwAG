#include <windows.h>
#include <stdlib.h>
#include <math.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glaux.h>
#include <vector>

#define PI 3.14159265358979323846

constexpr GLfloat identity[16] =
{
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
};

GLint _xKey = 0;
GLint _zKey = 0;
GLfloat _xRot = 5.0f;
GLfloat _zRot = 5.0f;

const GLfloat Deg2Rad =  PI / 180.0;


std::vector<GLfloat> getRx(GLfloat xRot) {
	std::vector<GLfloat> rotation =
	{
		1,			0,						0,							0,
		0,			(GLfloat) cos(xRot),	(GLfloat) -sin(xRot),		0,
		0,			(GLfloat) sin(xRot),	(GLfloat) cos(xRot),		0,
		0,			0,						0,							1
	};
	return rotation;
}

std::vector<GLfloat> getRy(GLfloat yRot) {
	std::vector<GLfloat> rotation =
	{
		(GLfloat) cos(yRot),		0,			(GLfloat) sin(yRot),		0,
		0,							1,			0,							0,
		(GLfloat) -sin(yRot),		0,			(GLfloat) cos(yRot),		0,
		0,							0,			0,							1
	};
	return rotation;
}

std::vector<GLfloat> getRz(GLfloat zRot) {
	std::vector<GLfloat> rotation =
	{
		(GLfloat) cos(zRot),		(GLfloat) -sin(zRot),		0,		0,
		(GLfloat) sin(zRot),		(GLfloat) cos(zRot),		0,		0,
		0,							0,							1,		0,
		0,							0,							0,		1
	};
	return rotation;
}

std::vector<GLfloat> getT(GLfloat x, GLfloat y, GLfloat z) {
	std::vector<GLfloat> translation =
	{
		1,		0,		0,		0,
		0,		1,		0,		0,
		0,		0,		1,		0,
		x,		y,		z,		1
	};
	return translation;
}

constexpr GLfloat identityMatrix[16] =
{
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
};




void DrawScene(GLfloat xRot, GLfloat yRot) 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

	glMatrixMode(GL_MODELVIEW);

	if (GetKeyState('A') & 0x8000/*Check if high-order bit is set (1 << 15)*/)
	{
		_zKey--;
	}
	else if ((GetKeyState('D') & 0x8000)) {
		_zKey++;
	}
	else if ((GetKeyState('W') & 0x8000)) {
		_xKey--;
	}
	else if ((GetKeyState('S') & 0x8000)) {
		_xKey++;
	}




	std::vector<GLfloat> Rx = getRx(xRot * Deg2Rad);
	std::vector<GLfloat> Ry = getRy(yRot * Deg2Rad);
	std::vector<GLfloat> T;
	

	//glLoadIdentity();
	glLoadMatrixf(identityMatrix);

	//glRotatef(xRot, 1.0f, 0.0f, 0.0f);
	glMultMatrixf(Rx.data());
    
    //glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	glMultMatrixf(Ry.data());

		glPushMatrix();
		{
			std::vector<GLfloat> Rx = getRx(_xKey * _xRot * Deg2Rad);
			glMultMatrixf(Rx.data());

			std::vector<GLfloat> Rz = getRz(_zKey * _zRot * Deg2Rad);
			glMultMatrixf(Rz.data());

			auxWireCube(5);
			auxWireCube(1);
		}
		glPopMatrix();

	//glLoadIdentity();
    //glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    //glRotatef(yRot, 0.0f, 1.0f, 0.0f);

	//glTranslatef(0, 3, 0);
	T = getT(0, 3, 0);
	glMultMatrixf(T.data());

	auxWireCube(2);

	//glTranslatef(0, 3, 5);
	T = getT(0, 3, 5);
	glMultMatrixf(T.data());

	auxWireCube(2);

	//glTranslatef(0, -3, -1);
	T = getT(0, -3, -1);
	glMultMatrixf(T.data());


	auxWireCube(2);

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
	glOrtho(-10, 10, -10, 10, -10, 10);
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	glEnable(GL_DEPTH_TEST);
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
	wcex.lpszClassName	= "Matrix";
	wcex.hIconSm		= NULL;
	return RegisterClassEx(&wcex);
}
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;
   hWnd = CreateWindow("Matrix", "Matrix", WS_OVERLAPPEDWINDOW, 50, 50, 550, 550, NULL, NULL, hInstance, NULL);
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