#include <math.h>
#include "glwidget.h"
#include <QtWidgets>
#include <QtOpenGL>

GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent)
{

}

void GLWidget::initializeGL(){
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_BLEND);
    glClearColor(187/(float)255, 190/(float)255, 191/(float)255, 1.0);
}

void GLWidget::paintGL(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    drawGL();
    glPopMatrix();
}

void GLWidget::drawGL(void){

    float xA = a*cos(alpha);
    float yA = a*sin(alpha);

    setColor(226, 58, 45);

    glLineWidth(3.0);
    glBegin(GL_LINES);
    glVertex2f(0,0);
    glVertex2f(xA,yA);
    glEnd();

    xB = b*cos(beta) + xA;
    yB = b*sin(beta) + yA;

    setColor(36, 149, 67);
    glLineWidth(3.0);
    glBegin(GL_LINES);
    glVertex2f(xA,yA);
    glVertex2f(xB,yB);
    glEnd();
}

void GLWidget::resizeGL(int width, int height){
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-200.0, 200.0, -200.0, 200.0, -200.0, 200.0);
    glMatrixMode(GL_MODELVIEW);
}

void GLWidget::setColor(uint8_t r, uint8_t g, uint8_t b){
    GLfloat materialColor[] = {r/(float)255, g/(float)255, b/(float)255};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
}

void GLWidget::setAlpha(int alpha){
    this->alpha = alpha*M_PI/180;
    updateGL();
}

void GLWidget::setBeta(int beta){
    this->beta = beta*M_PI/180;
    updateGL();
}





















