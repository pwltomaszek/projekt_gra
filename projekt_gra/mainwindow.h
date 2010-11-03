#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class Gra;

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

private:
    Ui::MainWindow *ui;
    Gra *mGra;

private slots:
    void on_actionSterowanie_triggered();
    void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
