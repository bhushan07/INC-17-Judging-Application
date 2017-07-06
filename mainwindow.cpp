#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap p1("2logo.png");
    QPixmap p2("inc17.png");

    ui->label_4->setPixmap(p1);
    ui->label_5->setPixmap(p2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_login_clicked()
{

    QString uname=ui->uname->text();
    QString pwd=ui->pwd->text();
    if(uname.compare("inc2017")==0&&pwd.compare("inc2017")==0)
    {
         h=new Home();
         h->show();
         this->hide();
    }
    else
    {
         QMessageBox::critical(this,"Error","Incorrect Username and Password !!");
    }

}
