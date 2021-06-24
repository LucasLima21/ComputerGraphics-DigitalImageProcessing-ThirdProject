#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <ctime>

using namespace std;
GLfloat angle = 30.0f;
int refreshMili = 1;
int initialTime = time(NULL), finalTime, frameCount = 0;


void timer(int value){
    glutPostRedisplay();
    glutTimerFunc(refreshMili, timer, 0);
}
void drawTriangle(){
    //set material properties
    GLfloat black[] = {0.1,0.1,0.1,1.0};
    GLfloat white[] = {1.0,1.0,1.0,1.0};
    GLfloat green[] = {0.0,1.0,0.0,1.0};
    glMaterialfv(GL_FRONT, GL_AMBIENT, green);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialf(GL_FRONT, GL_SHININESS, 60.0);


    glBegin(GL_TRIANGLES);
    glNormal3f(1.0,0.0,0.0);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(0.0, 5.0);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(4.0,-3.0);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(-4.0,-3.0);
    glEnd();
    glFlush();
}



void display () {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //SET LIGHT
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    //set light intensify and color
    GLfloat ambientLight[] = {0.2, 0.2, 0.2, 1.0};
    GLfloat diffuseLight[] = {0.8, 0.8, 0.8, 1.0};
    GLfloat specularLight[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat lightPosition[] = {0.0, 0.0, 0.0, 1.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    glPushMatrix();
    glTranslatef(0.5f, 0.0f, 0.0f);
    glRotatef(angle, 0, 0, 1);
    drawTriangle();
    glPopMatrix();
    glutSwapBuffers();
    angle += 0.2;
    frameCount++;
    finalTime = time(NULL);
    if(finalTime - initialTime > 0){
        cout <<"FPS = " << frameCount/(finalTime - initialTime) << endl;
        frameCount = 0;
        initialTime = finalTime;
    }
}

void backgroundDisplay(){
    glClearColor(0.0,0.0,0.0,0.0);
}

void reshapeFigure(int w, int h){
    glViewport(0,0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10, 10, -10, 10);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Spinning Triangle");

    glutDisplayFunc(display);
    glutReshapeFunc(reshapeFigure);
    glutTimerFunc(0, timer, 0);
    backgroundDisplay();
    glutMainLoop();
    return 0;
}
