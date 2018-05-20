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

#include <windows.h>
#include <gl/glu.h>
#include <math.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

float speed = 0.7f;
float q = 0.0f;
float w = 0.0f;
float e = 0.0f;
bool rotMundo = false;

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


     glOrtho(-30.0, 30.0, -30.0, 30.0, -1000.0, 1000.0);
     gluLookAt(1.0,0.0,0.7,0.0,0.0,0.5,0.0,0.0,1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    //roda o mundo
 //   glPushMatrix();

    //roda o cubinho
    glPushMatrix();
//    glTranslatef(w,e,0);
//    glRotatef(q,0.0f,0.0f,1.0f);

    desenhaCubo();
    glPopMatrix();

    //glRotatef(q,0.0f,0.0f,1.0f);
    //glTranslatef(w*sin(q),w*cos(q),0.0f);


 //   glTranslatef(w*sin(q),w*cos(q),0.0f);
    //glRotatef(q,0.0f,0.0f,1.0f);


        glPushMatrix();

    //glTranslatef(w,e,0);
    //glTranslatef(w*cos(q),w*sin(q),0.0f);
    //glRotated(q,0,0,1);
    //glTranslatef(-w*cos(q),-w*sin(q),0.0f);



 //  if(rotMundo == true){
    // Rotacionando o mapa em relação ao novo Pivo
        // Deixar o ponto de pivo na origem do sistema (0,0)
        glTranslatef(-w,-e,0.0);

        // Rotaciona o objeto
        glRotated(q,0,0,1);

        // Retorna a posição inicial o objeto ja rotacionado
        glTranslatef(w,e,0.0);

        BaseCirculo();


        // Rotaciona em relação ao eixo


   //     rotMundo = false;
  // }


   // glTranslatef(w*cos(q),w*sin(q),0.0f);
    //glTranslatef(w*sin(q),w*cos(q),0.0f);

    //glRotatef(q,0.0f,0.0f,1.0f);


       // chao();

   // glTranslatef(w*sin(q),w*cos(q),0.0f);

    //glRotatef(q/1.0f,0.0f,0.0f,0.01f);


  //  eixos(10.0);



    //termina de rodar o mundo
    glPopMatrix();


    glutSwapBuffers();
}


static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'p':
            exit(0);
            break;

        case '+':
            break;

        case 'q':
            q = q + 1.0f;
            rotMundo = true;
            break;

        case 'a':
            q = q - 1.0f;
            rotMundo = true;
            break;

        case 'w':
            w = w + 1.0f;
            break;

        case 's':
            w = w - 1.0f;
            break;

        case 'e':
            e = e + 1.0f;
            break;

        case 'd':
            e = e - 1.0f;
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


    glutMainLoop();

    return EXIT_SUCCESS;
}
