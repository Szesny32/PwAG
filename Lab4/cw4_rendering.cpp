//Laboratorium 4
//Modelowanie sceny w OpenGL

//Zadania:
// - dodac do sceny blyszczaca czerwona sfere z rozblyskiem
//--> ustawic oswietlenie - dwa zrodla swiatla (0 (kierunkowe): AMBIENT, DIFFUSE, 1 (punktowe): SPECULAR)
//--> ustawic parametry materialu
// - szescian z nalozona tekstura (na ka¿d¹ scianê)
//--> ustawic uwzglednianie oswietlenia na teksturze 
// - dodaæ obiekt sfery reprezentujacy punktowe zrodlo swiatla (zrodlo swiatla numer 1)
//- dodaæ sfere z nalozona tekstur¹ 

#include <iostream>
#include <fstream>

#define GLUT_DISABLE_ATEXIT_HACK

#include "GL/glut.h"

using namespace std;


static float zMove = 0.0; 
static float xRot = 0.0;
static float yRot = 0.0;
static unsigned int texture[2]; // indeksy tekstur.

const GLfloat black[] = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat white[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat yellow[] = { 1.0f, 1.0f, 0.0f, 1.0f };
const GLfloat red[] = { 1.0f, 0.0f, 0.0f, 1.0f };
const GLfloat shininess[] = { 30.0f};
const GLfloat directionalLight[] = {0.0f, 5.0f, 0.0f, 0.0f};
const GLfloat pointLight[] = { 5.0f, 5.0f, -10.0f, 1.0f };


// Struktura dla pliku bitmapy.
struct BitMapFile
{
   int sizeX;
   int sizeY;
   unsigned char *data;
};

// Routine to read a bitmap file.
// Works only for uncompressed bmp files of 24-bit color.
BitMapFile *getBMPData(string filename)
{
   BitMapFile *bmp = new BitMapFile;
   unsigned int size, offset, headerSize;
  
   // Read input file name.
   ifstream infile(filename.c_str(), ios::binary);
 
   // Get the starting point of the image data.
   infile.seekg(10);
   infile.read((char *) &offset, 4); 
   
   // Get the header size of the bitmap.
   infile.read((char *) &headerSize,4);

   // Get width and height values in the bitmap header.
   infile.seekg(18);
   infile.read( (char *) &bmp->sizeX, 4);
   infile.read( (char *) &bmp->sizeY, 4);

   // Allocate buffer for the image.
   size = bmp->sizeX * bmp->sizeY * 24;
   bmp->data = new unsigned char[size];

   // Read bitmap data.
   infile.seekg(offset);
   infile.read((char *) bmp->data , size);
   
   // Reverse color from bgr to rgb.
   int temp;
   for (int i = 0; i < size; i += 3)
   { 
      temp = bmp->data[i];
	  bmp->data[i] = bmp->data[i+2];
	  bmp->data[i+2] = temp;
   }

   return bmp;
}

// Zaladowanie tekstury.
void loadExternalTextures()			
{
   
   BitMapFile *image[2];

   // Zaladownie tekstu z plikow.
   image[0] = getBMPData("Textures/grass.bmp");
   image[1] = getBMPData("Textures/sky.bmp");
   
   
   //tekstura grass 
   glBindTexture(GL_TEXTURE_2D, texture[0]); 

   //ToDo - ustawienie parametrow tekstury glTexParametri 

   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image[0]->sizeX, image[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image[0]->data);
  

   //tekstura sky
   glBindTexture(GL_TEXTURE_2D, texture[1]);
     

   //ToDo - ustawienie parametrow tekstury glTexParametri 

   
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image[1]->sizeX, image[1]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image[1]->data);	
   
   
}


//inicjalizacja
void setup(void)
{
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glEnable(GL_DEPTH_TEST); 

   
   //ToDo - ustawienie parametrow oswietlenia dla dwoch zrodel swiatla

   //glLightModelfv();

   glLightfv(GL_LIGHT0, GL_AMBIENT, red);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
   glLightfv(GL_LIGHT0, GL_SPECULAR, black);
   glLightfv(GL_LIGHT0, GL_POSITION, directionalLight);
   glEnable(GL_LIGHT0);


   glLightfv(GL_LIGHT1, GL_AMBIENT, yellow);
   glLightfv(GL_LIGHT1, GL_DIFFUSE, black);
   glLightfv(GL_LIGHT1, GL_SPECULAR, white);
   glLightfv(GL_LIGHT1, GL_POSITION, pointLight);
   glEnable(GL_LIGHT1);
   
   glEnable(GL_LIGHTING); //To trzeba wlaczyc!!!
   //Tekstury
   glGenTextures(2, texture);

   loadExternalTextures();

   glEnable(GL_CULL_FACE);
   glCullFace(GL_BACK);
}



//Rysowanie sceny
void drawScene()
{  
     
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glLoadIdentity();

   
   glTranslatef(0.0, 0.0, -10.0);

  
   glRotatef(xRot, 1.0, 0.0, 0.0);
   glRotatef(yRot, 0.0, 1.0, 0.0);

   glColor3f(1.0, 0.0, 0.0);//tylko zeby sie cos pojawilo
   glTranslatef(1.5, 0.0, zMove); 

   //ToDo - ustawic parametry materialu dla sfery - czerwona z rozblyskiem




   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, red);
   glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, red);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
   glMaterialfv(GL_FRONT, GL_EMISSION, black);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

   glutSolidSphere(1.25, 100, 100);

    //ToDo - dodac sfere reprezentujaca polozenie swiatla punktowego o numerze 1 
   //ToDo - zdefiniowac material dla swiecacej sfery (GL_EMISSION)

   glPushMatrix();
   glLoadIdentity();
	   glTranslatef(pointLight[0], pointLight[1], pointLight[2]);
	   glMaterialfv(GL_FRONT, GL_AMBIENT, black);
	   glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, black);
	   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, black);
	   glMaterialfv(GL_FRONT, GL_EMISSION, white);
	  // glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	  glutSolidSphere(0.5, 100, 100);
	glPopMatrix();





   glTranslatef(-2.5, 0.0, 0.0); 
   
 
   glEnable(GL_TEXTURE_2D); 
   //ToDo - obsluga tekstury dla szescianu

   float s = 1.0;
   
  glBegin(GL_QUADS);
	 //Sciana przednia
     glVertex3f(-s, -s,  s);	 
	 glVertex3f( s, -s,  s);	
	 glVertex3f( s,  s,  s);	
	 glVertex3f(-s,  s,  s);	
   	
	 //Sciana tylna 
	 glVertex3f(-s, -s, -s);	
	 glVertex3f(-s,  s, -s);	
	 glVertex3f( s,  s, -s);	
	 glVertex3f( s, -s, -s);	
	
	 //Sciana gorna
	 glVertex3f(-s,  s, -s);	
	 glVertex3f(-s,  s,  s);	
	 glVertex3f( s,  s,  s);	
	 glVertex3f( s,  s, -s);	
	
	 //Sciana dolna
	 glVertex3f(-s, -s, -s);	
	 glVertex3f( s, -s, -s);	
	 glVertex3f( s, -s,  s);	
	 glVertex3f(-s, -s,  s);	
	 
	 //Prawa sciana
	 glVertex3f( s, -s, -s);	
	 glVertex3f( s,  s, -s);	
	 glVertex3f( s,  s,  s);	
	 glVertex3f( s, -s,  s);	
	
	 //Lewa sciana
	 glVertex3f(-s, -s, -s);	
	 glVertex3f(-s, -s,  s);	
	 glVertex3f(-s,  s,  s);	
	 glVertex3f(-s,  s, -s);	
  glEnd();

  //ToDo - dodac sfere z nalozona tekstutra
  glDisable(GL_TEXTURE_2D);

  
   glutSwapBuffers();
}


void resize (int w, int h)
{
   glViewport (0, 0, (GLsizei)w, (GLsizei)h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(70.0, (float)w/(float)h, 1.0, 50.0);
   glMatrixMode(GL_MODELVIEW);
}



void specialKeyInput(int key, int x, int y)
{
    if (key == GLUT_KEY_UP) zMove -= 0.1;
    if (key == GLUT_KEY_DOWN) if (zMove < 3.0) zMove += 0.1;

	if (key == GLUT_KEY_LEFT) yRot -= 5.0f;
	if (key == GLUT_KEY_RIGHT) yRot += 5.0f;

	if (xRot > 356.0f) xRot = 0.0f;
	if (xRot < -1.0f) xRot = 355.0f;
	if (yRot > 356.0f) yRot = 0.0f;
	if (yRot < -1.0f) yRot = 355.0f;
   glutPostRedisplay();
}


int main(int argc, char **argv) 
{
  
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
   glutInitWindowSize (500, 500);
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("OpenGL - Laboratorium 4");
   setup();
   glutDisplayFunc(drawScene);
   glutReshapeFunc(resize);

   glutSpecialFunc(specialKeyInput);
   glutMainLoop();
   
   return 0;
}
