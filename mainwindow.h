#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "home.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Home* h;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_login_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
