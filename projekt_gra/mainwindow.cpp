#include <QCloseEvent>
#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "glwidget.h"
#include "gra.h"

#include "IL/il.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mGra( 0 )
{
    ui->setupUi(this);

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

void MainWindow::closeEvent(QCloseEvent *e)
{
    // dirty dirty hack
    // zamiast zostawac w tle po alt+f4, proces ma segfaulta przy zamykaniu
    delete mGra;
    this->deleteLater();
    e->accept();
}

void MainWindow::on_pushButton_clicked()
{
    qobject_cast< QPushButton* >( sender() )->hide();

    mGra = new Gra;
    GLWidget *glWidget = new GLWidget( this, mGra );
    setCentralWidget( glWidget );
    glWidget->setFocus();

    while( true ) {
        mGra->petla();

        glWidget->paintGL();
        glWidget->swapBuffers();

        QApplication::processEvents();
    }
}
