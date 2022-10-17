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
    void setAlpha(int alpha);
    void setBeta(int beta);

signals:

protected:
    void initializeGL(void);
    void paintGL(void);
    void resizeGL(int width, int height);
public slots:

private:
    const int a = 100;
    const int b = 100;

    float alpha = 0;
    float beta = 0;

    float xB = a + b;
    float yB = 0;
};

#endif // GLWIDGET_H
