#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

    Ui::Dialog *ui;

private slots:
    void on_pushButton_clicked();

private:

};

#endif // DIALOG_H
