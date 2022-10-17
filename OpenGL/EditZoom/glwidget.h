#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = nullptr);
    void drawGL(void);
    void setColor(uint8_t r, uint8_t g, uint8_t b);
    void set_zoom(float z);
    void set_translatef(float x,float y);

signals:

protected:
    void initializeGL(void);
    void paintGL(void);
    void resizeGL(int width, int height);
public slots:

private:
    float zoom = 1.0;
    float x_tran = 0;
    float y_tran = 0;
};

#endif // GLWIDGET_H
