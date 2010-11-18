#include <QKeyEvent>

#include "glwidget.h"

#include "opengl/opengl.h"

#include "gra.h"

GLWidget::GLWidget(QWidget *parent, Gra *gra) :
    QGLWidget(parent),
    mGra( gra )
{
}

void GLWidget::initializeGL()
{
    GLWrapper::instance().init( 0, 0 );
}

void GLWidget::paintGL()
{
    mGra->rysuj();
    glColor3f( 0, 0, 0);
    renderText( 10, 10, "test" );
}

void GLWidget::resizeGL(int w, int h)
{
    glViewport( 0, 0, w, h );
    GLWrapper::instance().setPerspective( 60.0, (float)w / (float)h, 0.1, 10000.0 );
}
