#ifndef HOME_H
#define HOME_H

#include <QDialog>
#include <QSqlDatabase>
#include <QPrinter>
#include <QSqlQuery>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QFileDialog>
#include <QTextDocument>
#include "dialog.h"
#include "ui_dialog.h"
namespace Ui {
class Home;
}

class Home : public QDialog
{
    Q_OBJECT
    QSqlDatabase db;
    bool ok;
    int cur_jid,cur_pid;

    QTextDocument doc;

    Dialog *di;



public:
    explicit Home(QWidget *parent = 0);
    ~Home();

private slots:

    void clr_judge();
    void clr_grp();
    void clr_ad_marks();

    void on_ad_judge_clicked();

    void on_clear_judge_clicked();

    void on_ad_grp_clicked();

    void on_clear_group_clicked();

    void on_show_judge_clicked();

    void on_show_grpinfo_clicked();

    void on_ad_marks_clicked();

    void on_clear_marks_clicked();

    void on_show_marksentry_clicked();

    void on_tabWidget_tabBarClicked(int index);

    void on_view_oresult_clicked();

    void on_view_presult_clicked();

    void on_prnt_oresult_clicked();

    void on_prnt_presult_clicked();

    void on_about_clicked();

private:
    Ui::Home *ui;
};

#endif // HOME_H
