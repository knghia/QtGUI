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
    glTranslatef(x_tran, y_tran, 0);
    drawGL();
    glPopMatrix();
}

void GLWidget::drawGL(void){
    setColor(36, 149, 67);
    glLineWidth(3.0);
    glBegin(GL_LINES);
    glVertex2f(0, 0);
    glVertex2f(1, 1);
    glEnd();
}

void GLWidget::resizeGL(int width, int height){
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-zoom, zoom, -zoom, zoom, -zoom, zoom);
    glMatrixMode(GL_MODELVIEW);
}

void GLWidget::setColor(uint8_t r, uint8_t g, uint8_t b){
    GLfloat materialColor[] = {r/(float)255, g/(float)255, b/(float)255};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
}

void GLWidget::set_zoom(float z){
    zoom = (z<0)?z=0:z;
    this->resizeGL(600,400);
    updateGL();
}

void GLWidget::set_translatef(float x,float y){
    x_tran = x;
    y_tran = y;
    updateGL();
}












