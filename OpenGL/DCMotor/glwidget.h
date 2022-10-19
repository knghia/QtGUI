#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = nullptr);
    void drawGL(void);
    void set_translatef(float x,float y);
    void setColor(uint8_t r, uint8_t g, uint8_t b);

    float func_wt(float t);
    float func_theta(float t);
    void set_time(float ts);
    void set_voltage(float value);

    float get_theta(void);
    float get_wt(void);

signals:

protected:
    void initializeGL(void);
    void paintGL(void);
    void resizeGL(int width, int height);
public slots:

private:
    float x_tran = 0;
    float y_tran = 0;

// dc motor
    const float Ra = 2;
    const float La = 0.23;
    const float Jm = 0.000052;
    const float Bm = 0.01;
    const float Kt = 0.235;
    const float Ke = 0.235;

    float K;
    float A1, A2, A3;
    float x1, x2;

    float U = 0;
    float part_U = 0;
    float delta_U = 0;

    float wt = 0;
    float part_wt = 0;

    float theta = 0;
    float part_theta = 0;

    float time = 0;
};

#endif // GLWIDGET_H
