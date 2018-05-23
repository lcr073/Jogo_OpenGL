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

// Variavel que indica se tem balas ainda n�o eliminadas
int qtdTiros = 5;

GLuint texture;

//Checkerboard texture
GLuint mTextureID = 0;
GLsizei mTextureWidth;
GLsizei mTextureHeight;



// Limpando a textura da memoria

// Limpando oque esta na referencia
void freeTexture()
{
    //Delete texture
    if( mTextureID != 0 )
    {
        glDeleteTextures( 1, &mTextureID );
        mTextureID = 0;
    }

    mTextureWidth = 0;
    mTextureHeight = 0;
}

// Limpando tendo o id da textura
void FreeTexture( GLuint texture )
{
  glDeleteTextures( 1, &texture );  //Delete our texture, simple enough.
}

// Realiza os pedidos para o openGL de gerar um ID e vincula uma fonte de pixeis de dados nesse ID
bool loadTextureFromPixels32( GLuint* pixels, GLuint width, GLuint height )
{
    //Free texture if it exists
    freeTexture();

    //Get texture dimensions
    mTextureWidth = width;
    mTextureHeight = height;

    //Generate texture ID
    glGenTextures( 1, &mTextureID );

    //Bind texture ID
    glBindTexture( GL_TEXTURE_2D, mTextureID );

    //Generate texture
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels );

    //Set texture parameters
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

    //Unbind texture
    glBindTexture( GL_TEXTURE_2D, NULL );

    //Check for error
    GLenum error = glGetError();
    if( error != GL_NO_ERROR )
    {
        printf( "Error loading texture from %p pixels! %s\n", pixels, gluErrorString( error ) );
        return false;
    }

    return true;
}


// Realiza a cria��o de uma textura quadriculada no array realizado manualmente
bool loadMedia()
{
    //Checkerboard pixels
    const int CHECKERBOARD_WIDTH = 128;
    const int CHECKERBOARD_HEIGHT = 128;
    const int CHECKERBOARD_PIXEL_COUNT = CHECKERBOARD_WIDTH * CHECKERBOARD_HEIGHT;
    GLuint checkerBoard[ CHECKERBOARD_PIXEL_COUNT ];

    //Go through pixels
    for( int i = 0; i < CHECKERBOARD_PIXEL_COUNT; ++i )
    {
        //Get the individual color components
        GLubyte* colors = (GLubyte*)&checkerBoard[ i ];

        //If the 5th bit of the x and y offsets of the pixel do not match
        if( i / 128 & 16 ^ i % 128 & 16 )
        {
            //Set pixel to white
            colors[ 0 ] = 0xFF;
            colors[ 1 ] = 0xFF;
            colors[ 2 ] = 0xFF;
            colors[ 3 ] = 0xFF;
        }
        else
        {
            //Set pixel to red
            colors[ 0 ] = 0xFF;
            colors[ 1 ] = 0x00;
            colors[ 2 ] = 0x00;
            colors[ 3 ] = 0xFF;
        }
    }
    //Load texture
    if(! loadTextureFromPixels32( checkerBoard, CHECKERBOARD_WIDTH, CHECKERBOARD_HEIGHT ) )
    {
		printf( "Unable to load checkerboard texture!\n" );
        return false;
    }

    return true;
}


void RenderizarTextura(GLfloat x, GLfloat y)
{
    // Checa se tem textura armazenada para come�ar a desenhar
    if(mTextureID != 0){
        // Limpando qualquer transforma��o
        glLoadIdentity();

        // Movimentando o ponto de renderizacao para o desejado
        glTranslatef(x,y,0.0f);

        // Vinculando novamente a textura aos objetos desejados
        glBindTexture(GL_TEXTURE_2D, mTextureID);

        // Desenhando um objeto texturizado
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f,0.0f); glVertex2f(0.0f, 0.0f);
        glTexCoord2f(1.0f,0.0f); glVertex2f(mTextureWidth, 0.0f);
        glTexCoord2f(1.0f,1.0f); glVertex2f(mTextureWidth, mTextureHeight);
        glTexCoord2f(0.0f,1.0f); glVertex2f(0.0f, mTextureHeight);
        glEnd();
    }

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

     glOrtho(-500.0, 500.0, -500.0, 500.0, -1000.0, 1000.0);
//     gluLookAt(1.0,0.0,0.7,0.0,0.0,0.5,0.0,0.0,1.0);



    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    RenderizarTextura(0.0f, 3.0f);
    desenhaCubo();


	gluLookAt(	x, z, 0.4f,x+lx, z+lz,0.0f,0.0f, 0.0f,1.0f);
        glPushMatrix();
        BaseCirculo();

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

    glEnable(GL_TEXTURE_2D);
    glutReshapeFunc(resize);

    //Load media
    if( !loadMedia() )
    {
        printf( "Unable to load media!\n" );
        return 2;
    }

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

//    texture = LoadTexture("texture.raw",256,256);

    glutMainLoop();

//    FreeTexture( texture );

    return EXIT_SUCCESS;
}
