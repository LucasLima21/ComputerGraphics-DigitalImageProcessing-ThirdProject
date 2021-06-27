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
const int QUANTITY = 5000;
const int EXHIBITION_PROP = 40;

int initialTime = time(NULL), finalTime, frameCount = 0;

float positions_x[QUANTITY];
float positions_y[QUANTITY];
void timer(int value){
    glutPostRedisplay();
    glutTimerFunc(refreshMili, timer, 0);
}
void drawRotatedTriangle(GLfloat position_x, GLfloat position_y){
    glTranslatef((position_x), (position_y), 0.0f);
    glRotatef(angle, 0, 0, 1);
    GLfloat black[] = {0.1,0.1,0.1,1.0};
    GLfloat white[] = {1.0,1.0,1.0,1.0};
    GLfloat green[] = {0.0,1.0,0.0,1.0};
    glMaterialfv(GL_FRONT, GL_AMBIENT, green);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialf(GL_FRONT, GL_SHININESS, 60.0);


    glBegin(GL_TRIANGLES);
    glNormal3f(0.0,0.0,1.0);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(0.0, 5.0);
    glColor3f(0.0, 1.0, 0.0);
    glVertex2f(4.0,-3.0);
    glColor3f(0.0, 0.0, 1.0);
    glVertex2f(-4.0,-3.0);
    glEnd();

}


void createTriangles(GLfloat position_x, GLfloat position_y){
    glPushMatrix();
    drawRotatedTriangle(position_x, position_y);
    glPopMatrix();
}

void display () {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for(int i = 0; i < QUANTITY; i++){
        createTriangles(positions_x[i],positions_y[i]);
        createTriangles(-positions_x[i],positions_y[i]);
        createTriangles(positions_x[i],-positions_y[i]);
        createTriangles(-positions_x[i],-positions_y[i]);
    }
    angle += 0.2;
    glutSwapBuffers();
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
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    //set light intensify and color
    GLfloat ambientLight[] = {0.2, 0.2, 0.2, 1.0};
    GLfloat diffuseLight[] = {0.8, 0.8, 0.8, 1.0};
    GLfloat specularLight[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat lightPosition[] = {0.0, 0.0, 25.0, 1.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    gluOrtho2D(int(-QUANTITY/EXHIBITION_PROP), int(QUANTITY/EXHIBITION_PROP), int(-QUANTITY/EXHIBITION_PROP), int(QUANTITY/EXHIBITION_PROP));
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


int main(int argc, char** argv)
{
    srand((unsigned int) time(NULL));
    int j = QUANTITY - 1;
    for(int i = 0; i < QUANTITY; i++){
        positions_x[i] = (float(rand())/float((RAND_MAX)) * 100);
        positions_y[j]=(float(rand())/float((RAND_MAX)) * 100);
        j--;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowPosition(int(QUANTITY/EXHIBITION_PROP), int(QUANTITY/EXHIBITION_PROP));
    glutInitWindowSize(500, 500);
    glutCreateWindow("Spinning Triangles");

    glutReshapeFunc(reshapeFigure);
    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);
    backgroundDisplay();
    glutMainLoop();
    return 0;
}
