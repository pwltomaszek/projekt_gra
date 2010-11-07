#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

class Gra;
class GLWidget;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);
    void closeEvent(QCloseEvent *e);
    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);

private:
    const float FramesPerSec;

    Ui::MainWindow *ui;
    Gra *mGra;
    GLWidget *mGLWidget;

    QTimer mFPSCountTimer;
    unsigned int mFPSCount;

    QTimer mFPSTimer;

private slots:
    void on_actionSterowanie_triggered();
    void on_pushButton_clicked();

    void debugFPS();
    void nastepnaKlatka();
};

#endif // MAINWINDOW_H
