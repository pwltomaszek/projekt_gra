#include <QCloseEvent>
#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "glwidget.h"
#include "gra.h"

#include "opengl/IL/il.h"
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mGra( 0 ),
    FramesPerSec( 60 )
{
    ui->setupUi(this);
    ui->pushButton->setDefault( true );
    ilInit();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mGra;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::closeEvent(QCloseEvent */*e*/)
{
    // dirty dirty hack
    // zamiast zostawac w tle po alt+f4, proces ma segfaulta przy zamykaniu
//    delete mGra;
//    this->deleteLater();
//    e->accept();

    exit( 0 );
}

void MainWindow::debugFPS() {
    qDebug() << "FPS: " << (double)mFPSCount / 10.f;
    mFPSCount = 0;
}

void MainWindow::nastepnaKlatka()
{
    ++mFPSCount;
    mGra->petla();
    mGLWidget->updateGL();
}

void MainWindow::on_pushButton_clicked()
{
    qobject_cast< QPushButton* >( sender() )->hide();

    mGra = new Gra;
    mGLWidget = new GLWidget( this, mGra );
    setCentralWidget( mGLWidget );

    connect(&mFPSCountTimer, SIGNAL(timeout()), this, SLOT(debugFPS()));
    mFPSCountTimer.start( 10000 );
    mFPSCount = 0;

    connect(&mFPSTimer, SIGNAL(timeout()), this, SLOT(nastepnaKlatka()));
    mFPSTimer.start( 1000.f / FramesPerSec );
}

void MainWindow::on_actionSterowanie_triggered(){
    QMessageBox msgBox;
    msgBox.setText("Sterowanie");
    msgBox.setInformativeText("Strza³ki, spacja, Home");
    msgBox.exec();
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    // trzeba to poprawiæ
    if( e->key() == Qt::Key_Q )
        exit( 0 );

    if ( e->isAutoRepeat() || !mGra->akcje.contains( e->key() ) )    {
        e->ignore();
        return;
    }

    mGra->klawiszWcisniety( e->key() );
}

void MainWindow::keyReleaseEvent(QKeyEvent *e)
{
    if ( e->isAutoRepeat() || !mGra->akcje.contains( e->key() ) )    {
        e->ignore();
        return;
    }

    mGra->klawiszZwolniony( e->key() );
}
