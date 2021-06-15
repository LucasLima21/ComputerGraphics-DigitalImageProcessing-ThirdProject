#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
GLfloat angle = 30.0f;
int refreshMili = 1;

void timer(int value){
    glutPostRedisplay();
    glutTimerFunc(refreshMili, timer, 0);
}
void drawTriangle(){
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(0.0, 5.0);
    glColor3f(0.0, 1.0, 0.0);
    glVertex2f(4.0,-3.0);
    glColor3f(0.0, 0.0, 1.0);
    glVertex2f(-4.0,-3.0);
    glEnd();
}



void display () {
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glTranslatef(0.5f, 0.0f, 0.0f);
    glRotatef(angle, 0, 0, 1);
    drawTriangle();
    glPopMatrix();
    glutSwapBuffers();
    angle += 0.2;
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