/**
*   Programa para ilustrar:
*   - Acesso a textura em GLSL
*   - comando glActiveTexture()
*
*
*   Autor/Adaptacao: Cesar Tadeu Pozzer
*   UFSM - 09/2007
*
*   pozzer@inf.ufsm.br
*   pozzer3@gmail.com
*
**/

#include <GL/glew.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

#include "Bmp.h"
#include "glsl.h"

#define RECT_SIZE 10

int u_mode = 4;
int u_qtd_parts = 22;

//variaveis uniform
GLint loc_u_texture_0;  //local da variavel texture do arquivo tex.frag
GLint loc_u_texture_1;  //local da variavel texture do arquivo tex.frag
GLint loc_u_bright;     //local da variavel bright do arquivo tex.frag
GLint loc_u_dimension;
GLint loc_u_mode;
GLint loc_u_qtd_parts;

float brilho = 0;

Bmp *img1, *img2;
unsigned char *data1, *data2;
GLuint tex1, tex2;

float ang = 0;

Glsl *shader1;

void init_gl(void)
{
   glClearColor (0.0, 0.0, 0.0, 0.0);

   glShadeModel (GL_SMOOTH);
   //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

   img1 = new Bmp("glsl_5_Texture\\resource\\lena.bmp");
   img1->convertBGRtoRGB();
   data1 = img1->getImage();
   if( data1 == NULL )
   {
       printf("erro");
	   exit(0);
   }
   img2 = new Bmp("glsl_5_Texture\\resource\\textura.bmp");
   img2->convertBGRtoRGB();
   data2 = img2->getImage();
   if( data2 == NULL )
   {
       printf("erro");
	   exit(0);
   }
   //glEnable(GL_TEXTURE);
   //glEnable(GL_TEXTURE_2D);
   glGenTextures( 1, &tex1 );
   glBindTexture( GL_TEXTURE_2D, tex1 );
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img1->getWidth(),img1->getHeight(), 0,GL_RGB, GL_UNSIGNED_BYTE, data1);

   glGenTextures( 1, &tex2 );
   glBindTexture( GL_TEXTURE_2D, tex2 );
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img2->getWidth(),img2->getHeight(), 0,GL_RGB, GL_UNSIGNED_BYTE, data2);


   //glActiveTexture selects which texture unit subsequent texture state calls will
   //affect.  The number of texture units an implementation supports is
   //implementation dependent, but must be at least 2.
   glActiveTexture(GL_TEXTURE0);
   glEnable(GL_TEXTURE_2D);
   glBindTexture( GL_TEXTURE_2D, tex1 );

   glActiveTexture(GL_TEXTURE1);
   glEnable(GL_TEXTURE_2D);
   glBindTexture( GL_TEXTURE_2D, tex2 );

}

void display(void)
{
   Sleep(5);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   //muda a intensidade da cor de cada pixel por uma senoide no intervalo [0.2, 4.2]
   float valor = (sin(brilho+=0.01))*1.0;
   int texture = (valor>0.5)? 0:1;

   if(u_mode >= 0 && u_mode <= 3){
       glUniform1f(loc_u_bright, valor);
       glUniform1i(loc_u_texture_0, 0);
       glUniform1i(loc_u_texture_1, 1);
       glUniform1i(loc_u_dimension, img1->getWidth());
       glUniform1i(loc_u_mode, u_mode);
       glUniform1i(loc_u_qtd_parts, u_qtd_parts);

      glNormal3f(0, 1, 0);
      glBegin(GL_QUADS);
       glTexCoord2f(0, 0);
       glVertex3f(-2, -2,  -10);

       glTexCoord2f(1, 0);
	   glVertex3f(2, -2,   -10);

       glTexCoord2f(1, 1);
       glVertex3f(2, 2,  -10);

       glTexCoord2f(0, 1);
       glVertex3f(-2, 2, -10);
      glEnd();
   }

   if(u_mode == 4) {
       glMatrixMode(GL_PROJECTION);
       glLoadIdentity( );
       glOrtho(2, -2, -2, 2, 1, 1000);

       glMatrixMode(GL_MODELVIEW);
       glLoadIdentity( );
       gluLookAt(0, 0, 2,
                 0, 0, 0,
                 0, 1, 0);
      glutSolidTeapot(1);
   }

   glutSwapBuffers();
}

void reshape (int w, int h)
{
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(30, 1, 1, 100);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void keyboard(unsigned char c, int x, int y)
{
   if ( c == '0' )
      u_mode = 0;
   else if (c == '1' )
	  u_mode = 1;
   else if (c == '2' )
	  u_mode = 2;
   else if (c == '3' )
	  u_mode = 3;
   else if (c == '4' )
	  u_mode = 4;
   else if (c == '5' )
	  u_mode = 5;
   else
      u_mode = 1;
      printf("%d", u_mode);
}

int main(int argc, char** argv)
{

   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (600, 600);
   glutInitWindowPosition (100, 100);
   glutCreateWindow("Shader 1");
   glutDisplayFunc(display);
   glutIdleFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);

   //neste caso, o glsl deve ser inicializado antes do gl para poder chamar o
   //comando  glActiveTexture();
   shader1 = new Glsl("glsl_5_Texture\\src\\tex.vert", "glsl_5_Texture\\src\\tex.frag");
   shader1->setActive(true);
   init_gl();

   loc_u_texture_0 = shader1->getUniformLoc("texture_0");
   loc_u_texture_1 = shader1->getUniformLoc("texture_1");
   loc_u_bright    = shader1->getUniformLoc("brilho");
   loc_u_dimension = shader1->getUniformLoc("dim");
   loc_u_mode      = shader1->getUniformLoc("mode");
   loc_u_qtd_parts = shader1->getUniformLoc("qtd_parts");


   //printf(" IDs: %d %d ", loc_u_texture, loc_u_bright);

   glutMainLoop();
   return 0;
}
