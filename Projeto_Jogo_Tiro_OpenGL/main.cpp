/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */
#include <stdio.h>
#include <stdlib.h>
#include "readBMP.h" // para textura
#include <windows.h>
#include <gl/glu.h>
#include <math.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif



// Angulo
float angle=0.0;
// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f;
// XZ position of the camera
float x=0.0f,z=2.0f;

// Variavel que indica se tem balas ainda não eliminadas
int qtdTiros = 5;

GLuint texture;

// Limpando a textura da memoria
void FreeTexture( GLuint texture )
{
  glDeleteTextures( 1, &texture );  //Delete our texture, simple enough.
}

void square (void) {
    glBindTexture( GL_TEXTURE_2D, texture ); //bind our texture to our shape
    glRotatef( angle, 1.0f, 1.0f, 1.0f );
    glBegin (GL_QUADS);
    glTexCoord2d(0.0,0.0); glVertex2d(-1.0,-1.0); //with our vertices we have to assign a texcoord
    glTexCoord2d(1.0,0.0); glVertex2d(+1.0,-1.0); //so that our texture has some points to draw to
    glTexCoord2d(1.0,1.0); glVertex2d(+1.0,+1.0);
    glTexCoord2d(0.0,1.0); glVertex2d(-1.0,+1.0);
    glEnd();
}

GLuint LoadTexture( const char * filename, int width, int height )
{
    GLuint texture;
    unsigned char * data;
    FILE * file;

    // Abrindo arquivo
    file = fopen(filename, "rb" );  //We need to open our file
    if ( file == NULL ) return 0;  //If our file is empty, set our texture to empty
    data = (unsigned char *)malloc( width * height * 3 ); // assign the nessecary memory for the texture

    fread( data, width * height * 3, 1, file );  //read in our file
    fclose( file ); //close our file, no point leaving it open

    glGenTextures( 1, &texture ); // then we need to tell OpenGL that we are generating a texture primeiro parametro é o numero de texturas que
                                    // queremos e o segundo e um ponteiro para onde ele ira salvar
    glBindTexture( GL_TEXTURE_2D, texture ); //now we bind the texture that we are working with
//    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE ); // set texture environment parameters

    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    free( data ); //free the texture

    return texture; //return the texture data

}



void face(){
                float di = 1.0/20.0;

                float i = 0.5;
                float u = 0.5;


                glBegin(GL_QUADS);
                while(i >= (-0.5)){
                        while(u >= (-0.5)){
               //             glColor3f(u,i,0);
                            glVertex3f(0.5,i,u);
                            glNormal3f(1,0,0);

                            glVertex3f(0.5,i-di,u);

                            glVertex3f(0.5,i-di,u-di);

                            glVertex3f(0.5,i,u-di);
                            u = u - di;
                        }
                            u = 0.5;
                            i = i - di;
                }
                 glEnd();


                glPushMatrix();
                glRotated(90.0,0,0,1);
                glPopMatrix();
}

void chao(){
    glColor3f(1,0,0);
                float di = 1.0/5.0;

                float i = 40.0;
                float u = 40.0;

                glRotatef(-90,0.0f,1.0f,0.0f);

                glPushMatrix();

                    glBegin(GL_QUADS);
                    while(i >= (-40.0)){
                            while(u >= (-40.0)){
                                glVertex3f(0.5,i,u);
                                glNormal3f(1,0,0);

                                glVertex3f(0.5,i-di,u);

                                glVertex3f(0.5,i-di,u-di);

                                glVertex3f(0.5,i,u-di);

                                u = u - di;
                            }
                                u = 40;
                                i = i - di;
                    }
                     glEnd();
                glPopMatrix();
}


void desenhaCubo(){
            glColor3d(1,0,1);
                face();

            glPushMatrix();
                glColor3d(1,0,0);
                glRotated(90.0,0,0,1);
                face();
            glPopMatrix();

            glPushMatrix();
                glColor3d(0,1,0);
                glRotated(180.0,0,0,1);
                face();
            glPopMatrix();

            glPushMatrix();
                glColor3d(1,1,0);
                glRotated(270.0,0,0,1);
                face();
            glPopMatrix();

            glPushMatrix();
                glColor3d(0,1,0);
                glRotated(90,0,1,0);
                face();
            glPopMatrix();

            glPushMatrix();
                glColor3d(0,1,1);
                glRotated(-90,0,1,0);
                face();
            glPopMatrix();
}

void atira(){
    glPushMatrix();
    glTranslatef(x,(z-2),0.0);
    desenhaCubo();
    glPopMatrix();
}

void eixos(float T)
{
    glBegin(GL_LINES);

    glColor3f(1,0,0);

    glVertex3f(0,0,0);
    glVertex3f(T,0,0);

    glColor3f(0,1,0);

    glVertex3f(0,0,0);
    glVertex3f(0,T,0);

    glColor3f(0,0,1);

    glVertex3f(0,0,0);
    glVertex3f(0,0,T);

    glEnd();
};

void BaseCirculo(){
    float umin = 0;
    float umax = 360;
    float du = (umax-umin)/32;
      // float du = 4 * M_PI / 180;
    float i;
    i = umin;

    // Definindo as dimensos do cubo
    //glScaled(1.0,2.0,4.0);

    while(i <= umax){
            glPushMatrix();
                glRotated(i,0,0,1);
                glTranslated(16,0,2.0);
            glScalef(1,1,4);

                desenhaCubo();
            glPopMatrix();
        i = i + du;
    }
}

/* GLUT callback Handlers */

static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);

  //  glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
}

static void display(void)
{
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

     glOrtho(-4.0, 4.0, -4.0, 4.0, -1000.0, 1000.0);
//     gluLookAt(1.0,0.0,0.7,0.0,0.0,0.5,0.0,0.0,1.0);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    desenhaCubo();


	gluLookAt(	x, z, 0.4f,x+lx, z+lz,0.0f,0.0f, 0.0f,1.0f);
        glPushMatrix();
        BaseCirculo();

    glEnable(GL_TEXTURE_2D);
    square();
       // chao();

  //  eixos(10.0);



    //termina de rodar o mundo
    glPopMatrix();


    glutSwapBuffers();
}


static void key(unsigned char key, int xx, int yy)
{
    switch (key)
    {
        case 27 :

            case 'k' :
                // Permite atirar se tiver municao
                if(qtdTiros > 0){
                    atira();
                    qtdTiros = qtdTiros - 1;
                }

        break;

		case 'd' :
			angle -= 0.01f;
			lx = sin(angle);
			lz = -cos(angle);
			break;
		case 'a' :
			angle += 0.01f;
			lx = sin(angle);
			lz = -cos(angle);
			break;
		case 'w' :
			x += lx ;
			z += lz ;
			break;
		case 's' :
			x -= lx;
			z -= lz;
			break;

        case 'p':
            exit(0);
            break;

        case '+':
            break;

        case 'x':

            break;

        case '-':

            break;
    }

    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Jogo de Tiro");

    glutReshapeFunc(resize);

    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    glClearColor(1,1,1,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    texture = LoadTexture("texture.raw",256,256);

    glutMainLoop();

    FreeTexture( texture );

    return EXIT_SUCCESS;
}
