#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>

class Gra;
class GLWrapper;

class GLWidget : public QGLWidget
{
Q_OBJECT
public:
    explicit GLWidget( QWidget *parent, Gra *gra);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);

private:
    Gra *mGra;

signals:

public slots:

};

#endif // GLWIDGET_H
