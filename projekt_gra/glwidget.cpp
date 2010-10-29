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
}

void GLWidget::resizeGL(int w, int h)
{
    glViewport( 0, 0, w, h );
    GLWrapper::instance().setPerspective( 60.0, (float)w / (float)h, 0.1, 10000.0 );
}

void GLWidget::keyPressEvent(QKeyEvent *e)
{
    // trzeba to poprawiæ
    if( e->key() == Qt::Key_Q ) 
        exit( 0 );

    mGra->klawiszWcisniety( e->key() );
}

void GLWidget::keyReleaseEvent(QKeyEvent *e)
{
    mGra->klawiszWcisniety( e->key(), false );
}
