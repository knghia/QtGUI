#include <math.h>
#include "glwidget.h"
#include <QtWidgets>
#include <QtOpenGL>

GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent)
{
    float a = 1;
    float b = (Jm*Ra + La*Bm)/(La*Jm);
    float c = (Ke*Kt + Ra*Bm)/(La*Jm);
    float delta = b*b - 4*a*c;

    x1 = (-b+sqrt(delta))/(2*a);
    x2 = (-b-sqrt(delta))/(2*a);

    K = Kt/(La*Jm);
    A1 = 1/(x1*x2);
    A2 = 1/(x1*(x1-x2));
    A3 = 1/(x2*(x2-x1));

    U = 0;
    part_U = 0;
    delta_U = 0;

    wt = 0;
    part_wt = 0;

    theta = 0;
    part_theta = 0;

    time = 0;
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

float GLWidget::func_wt(float t){
    return K*delta_U*(A2*exp(x1*t) + A3*exp(x2*t) - (A2+A3));
}

float GLWidget::func_theta(float t){
    return K*delta_U*((A2/x1)*exp(x1*t) + (A3/x2)*exp(x2*t) - (A2+A3)*t - (A2/x1 + A3/x2));
}

void GLWidget::drawGL(void){
    wt= func_wt(time) + part_wt;
    theta= func_theta(time)+ part_wt*time + part_theta;
    if (U - part_U != 0){
        delta_U = U - part_U;
        part_wt = wt;
        part_theta = theta;
        part_U = U;
        time = 0;
    }

    float x = cos(theta);
    float y = sin(theta);

    glBegin(GL_LINES);
    setColor(36, 149, 67);
    glVertex2f(x,y);
    glVertex2f(0,0);
    glEnd();
}

void GLWidget::resizeGL(int width, int height){
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float zoom = 2.0;
    glOrtho(-zoom, zoom, -zoom, zoom, -zoom, zoom);
    glMatrixMode(GL_MODELVIEW);
}

void GLWidget::setColor(uint8_t r, uint8_t g, uint8_t b){
    GLfloat materialColor[] = {r/(float)255, g/(float)255, b/(float)255};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
}

void GLWidget::set_translatef(float x,float y){
    x_tran = x;
    y_tran = y;
    updateGL();
}

void GLWidget::set_time(float ts){
    time += ts;
    updateGL();
}

void GLWidget::set_voltage(float value){
    U = value;
    updateGL();
}

float GLWidget::get_wt(void){
    return wt;
}

float GLWidget::get_theta(void){
    return theta;
}











