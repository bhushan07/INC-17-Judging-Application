#include "home.h"
#include "ui_home.h"
#include <QMessageBox>
#include <iostream>
using namespace std;


Home::Home(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Home)
{
    ui->setupUi(this);

    di=new Dialog();

    QPixmap p3("2logo.png");
    QPixmap p4("inc17.png");

    ui->label->setPixmap(p3);
    ui->label_2->setPixmap(p4);

    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("inc17db");
    db.setUserName("inc17");
    db.setPassword("inc17");
    ok = db.open();

    QSqlQuery q0;

    q0.exec("SELECT JID FROM Judgeinfo ORDER BY JID DESC LIMIT 1");
    while(q0.next())
        cur_jid=q0.value(0).toInt()+1;
    if(cur_jid==0)
        cur_jid=1;

    ui->lineEdit->setText(QString::number(cur_jid));

    ui->tabWidget->setCurrentIndex(0);

}

Home::~Home()
{
    delete ui;
}

void Home::on_ad_judge_clicked()
{
    int jid=ui->lineEdit->text().toInt();
    QString name=ui->lineEdit_2->text();
    QString mail=ui->lineEdit_3->text();
    QString dom;
    if(ui->checkBox->isChecked())
        dom=dom+"1,";
    if(ui->checkBox_2->isChecked())
        dom=dom+"2,";
    if(ui->checkBox_3->isChecked())
        dom=dom+"3,";
    if(ui->checkBox_4->isChecked())
        dom=dom+"4,";
    if(ui->checkBox_5->isChecked())
        dom=dom+"5,";
    if(ui->checkBox_6->isChecked())
        dom=dom+"6,";
    if(ui->checkBox_7->isChecked())
        dom=dom+"7,";

    if(ok)
    {
        QSqlQuery q2;
        if(jid!=0&&name!=""&&mail!="")
        {
            bool ok1=q2.exec("INSERT INTO Judgeinfo VALUES('"+QString::number(jid)+"','"+name+"','"+mail+"','"+dom.left(dom.length()-1)+"')");
            if(ok1)
            {
                QMessageBox::information(this,"Success","New JID Added");
                clr_judge();
            }
            else
                QMessageBox::critical(this,"Error","Entry discarded. Something went Wrong !");
        }
        else
            QMessageBox::critical(this,"Error","Fill all fields !");
    }
    else
        QMessageBox::critical(this,"Error","Database not accessible. Something went Wrong !");
}
void Home::clr_judge()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->checkBox->setChecked(false);
    ui->checkBox_2->setChecked(false);
    ui->checkBox_3->setChecked(false);
    ui->checkBox_4->setChecked(false);
    ui->checkBox_5->setChecked(false);
    ui->checkBox_6->setChecked(false);
    ui->checkBox_7->setChecked(false);

    QSqlQuery x0;

    x0.exec("SELECT JID FROM Judgeinfo ORDER BY JID DESC LIMIT 1");
    while(x0.next())
        cur_jid=x0.value(0).toInt()+1;
    if(cur_jid==0)
        cur_jid=1;

    ui->lineEdit->setText(QString::number(cur_jid));

}

void Home::on_clear_judge_clicked()
{
    clr_judge();
}

void Home::on_ad_grp_clicked()
{
    QString pid=ui->lineEdit_4->text();
    QString title=ui->lineEdit_5->text();
    QString clg=ui->lineEdit_6->text();
    QString m1=ui->lineEdit_7->text();
    QString m2=ui->lineEdit_8->text();
    QString m3=ui->lineEdit_9->text();
    QString m4=ui->lineEdit_10->text();
    QString m5=ui->lineEdit_11->text();


    int gdom=ui->lineEdit_16->text().toInt();

    if(ok)
    {
        QSqlQuery q3;
        if(pid!=""&&title!=""&&clg!=""&&m1!=""&&gdom!=0)
        {
            bool ok2=q3.exec("INSERT INTO Groupinfo VALUES('"+pid+"','"+QString::number(gdom)+"','"+title+"','"+clg+"','"+m1+"','"+m2+"','"+m3+"','"+m4+"','"+m5+"')");
            if(ok2)
            {
                QMessageBox::information(this,"Success","New PID Added");
                clr_grp();
            }
            else
                QMessageBox::critical(this,"Error","Entry discarded. Something went Wrong !");
        }
        else
            QMessageBox::critical(this,"Error","Fill all fields !");
    }
    else
        QMessageBox::critical(this,"Error","Database not accessible. Something went Wrong !");

}

void Home::clr_grp()
{
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->lineEdit_6->clear();
    ui->lineEdit_7->clear();
    ui->lineEdit_8->clear();
    ui->lineEdit_9->clear();
    ui->lineEdit_10->clear();
    ui->lineEdit_11->clear();
    ui->lineEdit_16->clear();
}

void Home::on_clear_group_clicked()
{
    clr_grp();
}

void Home::on_show_judge_clicked()
{
    QStandardItemModel * model = new QStandardItemModel(400,4,this);
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("JID")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Name")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("E-mail")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QString("Domain interest")));


    QSqlQuery q4;
    q4.exec("SELECT * FROM Judgeinfo");
    int j=0;
    while (q4.next())
    {
        int jid = q4.value(0).toInt();
        QString nm = q4.value(1).toString();
        QString eml = q4.value(2).toString();
        QString dm = q4.value(3).toString();

        QStandardItem *firstRow;
        firstRow = new QStandardItem(QString::number(jid));
        model->setItem(j,0,firstRow);
        firstRow = new QStandardItem(QString(nm));
        model->setItem(j,1,firstRow);
        firstRow = new QStandardItem(QString(eml));
        model->setItem(j,2,firstRow);
        firstRow = new QStandardItem(QString(dm));
        model->setItem(j,3,firstRow);

        j++;

    }


    di->ui->di_table->setModel(model);
    di->ui->di_table->resizeColumnsToContents();
    di->show();

}

void Home::on_show_grpinfo_clicked()
{
    QStandardItemModel * model = new QStandardItemModel(400,9,this);
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("PID")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Domain")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Title")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QString("College")));
    model->setHorizontalHeaderItem(4, new QStandardItem(QString("Grp Leader")));
    model->setHorizontalHeaderItem(5, new QStandardItem(QString("Member 2")));
    model->setHorizontalHeaderItem(6, new QStandardItem(QString("Member 3")));
    model->setHorizontalHeaderItem(7, new QStandardItem(QString("Member 4")));
    model->setHorizontalHeaderItem(8, new QStandardItem(QString("Member 5")));


    QSqlQuery q5;
    q5.exec("SELECT * FROM Groupinfo");
    int j=0;
    while (q5.next())
    {
        QString pid = q5.value(0).toString();
        int dm = q5.value(1).toInt();
        QString ttl = q5.value(2).toString();
        QString clg = q5.value(3).toString();
        QString m1 = q5.value(4).toString();
        QString m2 = q5.value(5).toString();
        QString m3 = q5.value(6).toString();
        QString m4 = q5.value(7).toString();
        QString m5 = q5.value(8).toString();


        QStandardItem *firstRow;
        firstRow = new QStandardItem(QString(pid));
        model->setItem(j,0,firstRow);
        firstRow = new QStandardItem(QString::number(dm));
        model->setItem(j,1,firstRow);
        firstRow = new QStandardItem(QString(ttl));
        model->setItem(j,2,firstRow);
        firstRow = new QStandardItem(QString(clg));
        model->setItem(j,3,firstRow);
        firstRow = new QStandardItem(QString(m1));
        model->setItem(j,4,firstRow);
        firstRow = new QStandardItem(QString(m2));
        model->setItem(j,5,firstRow);
        firstRow = new QStandardItem(QString(m3));
        model->setItem(j,6,firstRow);
        firstRow = new QStandardItem(QString(m4));
        model->setItem(j,7,firstRow);
        firstRow = new QStandardItem(QString(m5));
        model->setItem(j,8,firstRow);

        j++;

    }

    di->ui->di_table->setModel(model);
    di->ui->di_table->resizeColumnsToContents();
    di->show();

}

void Home::on_ad_marks_clicked()
{
    int jid=ui->lineEdit_12->text().toInt();
    QString pid=ui->lineEdit_13->text();
    int mrks=ui->lineEdit_14->text().toInt();
    int cat=0;
    int maxm=0;

         if(ok)
         {

             QSqlQuery q6;
             q6.exec("SELECT Pdomain FROM Groupinfo where PID='"+pid+"';");
             while(q6.next())
                 cat=q6.value(0).toInt();

             if(jid!=0&&pid!=""&&mrks!=0&&cat!=0)
             {
                 QSqlQuery q7;
                 bool ok3=q7.exec("INSERT INTO Marks VALUES ('"+pid+"',"+QString::number(jid)+","+QString::number(mrks)+");");
                 if(ok3)
                 {
                      QMessageBox::information(this,"Status","Marks Added");
                      clr_ad_marks();

                      QSqlQuery pa;
                      pa.exec("INSERT INTO Projects VALUES('"+pid+"',0,0,"+QString::number(cat)+");");

                      pa.exec("INSERT INTO Judges VALUES("+QString::number(jid)+",0);");


                      QSqlQuery q8;
                      q8.exec("UPDATE Projects SET Jtime=Jtime+1 WHERE PID='"+pid+"';");
                      QSqlQuery q9;
                      q9.exec("SELECT MaxMarks FROM Judges WHERE JID="+QString::number(jid)+";");
                      if(q9.next())
                      {
                          maxm=q9.value(0).toInt();
                      }
                      if(mrks>maxm)
                      {
                          QSqlQuery q10;
                          q10.exec("UPDATE Judges SET MaxMarks="+QString::number(mrks)+" WHERE JID="+QString::number(jid)+";");
                      }

                 }
                 else
                     QMessageBox::critical(this,"Status","Check Entry .Something went Wrong!!");
             }
             else
                 QMessageBox::critical(this,"Error","Fill all fields Correctly !");
         }
         else
             QMessageBox::critical(this,"Error","Database not accessible. Something went Wrong !");
}

void Home::clr_ad_marks()
{
    ui->lineEdit_12->clear();
    ui->lineEdit_13->clear();
    ui->lineEdit_14->clear();
}

void Home::on_clear_marks_clicked()
{
    clr_ad_marks();
}

void Home::on_show_marksentry_clicked()
{
    QStandardItemModel * model = new QStandardItemModel(1500,3,this);
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("PID")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("JID")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Marks")));


    QSqlQuery q11;
    q11.exec("SELECT * FROM Marks");
    int j=0;
    while (q11.next())
    {
        QString pid = q11.value(0).toString();
        int jid = q11.value(1).toInt();
        int mrk = q11.value(2).toInt();


        QStandardItem *firstRow;
        firstRow = new QStandardItem(QString(pid));
        model->setItem(j,0,firstRow);
        firstRow = new QStandardItem(QString::number(jid));
        model->setItem(j,1,firstRow);
        firstRow = new QStandardItem(QString::number(mrk));
        model->setItem(j,2,firstRow);

        j++;

    }

    di->ui->di_table->setModel(model);
    di->ui->di_table->resizeColumnsToContents();
    di->show();

}

void Home::on_tabWidget_tabBarClicked(int index)
{
    double prg=0,temp=0;
    int no,in;
    int cn=1;
    double arr[30];
    ui->progressBar->setValue(prg);
    if(index==3)
    {
        QSqlQuery q12,q13,q14,q15,ins;
        q12.exec("SELECT count(PID) from Projects;");
        if (q12.next())
            no=q12.value(0).toInt();
        no=no*2;

        q12.exec("SELECT * FROM Projects;");

        while(q12.next())
        {
            in=0;
            QString pid=q12.value(0).toString();
            q13.exec("SELECT * FROM Marks WHERE PID='"+pid+"';");
            double avg=0;
            int cnt=0;
            int maxm;


            prg=cn;
            prg=(prg/no)*100;
            ui->progressBar->setValue(prg);
            cn++;


            while(q13.next())
            {
                int marks=q13.value(2).toInt();

                q14.exec("SELECT MaxMarks FROM Judges WHERE JID="+QString::number(q13.value(1).toInt())+";");
                if(q14.next())
                {
                   maxm=q14.value(0).toInt();
                }
                arr[in]=((double)marks/maxm)*50;
                cnt++;
                in++;
            }

            if(in>1)
            {
            for(int k=0;k<in-1;k++)
                for(int l=0;l<in-k-1;l++)
                {
                    if(arr[l]<arr[l+1])
                    {
                        temp=arr[l];
                        arr[l]=arr[l+1];
                        arr[l+1]=temp;
                    }
                }
            }


            if(in==2)
                avg=(arr[0]+arr[1])/2;
            else if(in==1)
                avg=arr[0];
            else
                avg=(arr[0]+arr[1]+arr[2])/3;

            q15.exec("UPDATE Projects SET Average="+QString::number(avg)+" WHERE PID='"+pid+"'");
        }

            QSqlQuery de;
            de.exec("TRUNCATE TABLE Result");

            q15.exec("SELECT * FROM Projects where Jtime >= '2' ORDER BY Jtime DESC ;");

            int flag=0;
            while(q15.next())
            {

                q14.exec("SELECT DISTINCT PID FROM Result");
                while(q14.next())
                {
                    if(q15.value(0).toString()==q14.value(0).toString())
                    {
                        flag=1;
                        break;
                    }
                }
                if(flag==1)
                    ins.exec("UPDATE Result SET Average="+QString::number(q15.value(1).toFloat())+" WHERE PID='"+q14.value(0).toString()+"';");
                else
                    ins.exec("INSERT INTO Result VALUES('"+q15.value(0).toString()+"',"+QString::number(q15.value(1).toFloat())+","+QString::number(q15.value(2).toInt())+","+QString::number(q15.value(3).toInt())+");");

                flag=0;
            }
            prg=no;
            prg=(prg/no)*100;
            ui->progressBar->setValue(prg);

    }
}

void Home::on_view_oresult_clicked()
{
    int category=ui->comboBox->currentIndex();

    QSqlQuery q16;

    QString pid;
    double avg;
    int jtime;
    int cat;
    int j=0;


    if(category==0)
        q16.exec("SELECT * FROM Result ORDER BY Average DESC");
    else if (category!=0)
        q16.exec("SELECT * FROM Result WHERE Category="+QString::number(category)+" ORDER BY Average DESC");


    QStandardItemModel * model = new QStandardItemModel(400,5,this);
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Rank")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("PID")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Average")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QString("No Of Times Judged")));
    model->setHorizontalHeaderItem(4, new QStandardItem(QString("Category")));

    while (q16.next())
    {
                        pid = q16.value(0).toString();
                        avg = q16.value(1).toDouble();
                        jtime = q16.value(2).toInt();
                        cat =q16.value(3).toInt();


                        QStandardItem *firstRow = new QStandardItem(QString::number(j+1));
                        model->setItem(j,0,firstRow);
                        firstRow = new QStandardItem(QString(pid));
                        model->setItem(j,1,firstRow);
                        firstRow = new QStandardItem(QString::number(avg));
                        model->setItem(j,2,firstRow);
                        firstRow = new QStandardItem(QString::number(jtime));
                        model->setItem(j,3,firstRow);
                        firstRow = new QStandardItem(QString::number(cat));
                        model->setItem(j,4,firstRow);

                       j++;
    }
    di->ui->di_table->setModel(model);
    di->ui->di_table->resizeColumnsToContents();
    di->show();

}

void Home::on_view_presult_clicked()
{

        QString pid=ui->lineEdit_15->text();
        QStandardItemModel * model = new QStandardItemModel(50,2,this);
        model->setHorizontalHeaderItem(0, new QStandardItem(QString("Judge Id")));
        model->setHorizontalHeaderItem(1, new QStandardItem(QString("Marks Given")));


        QSqlQuery q19;
        q19.exec("SELECT Average FROM Projects WHERE PID='"+pid+"';");
        double avg=0;
        if(q19.next())
            avg=q19.value(0).toDouble();

        QStandardItem *firstRow;

        QSqlQuery q18;
        q18.exec("SELECT * FROM Marks WHERE PID='"+pid+"';");
        int j=0;
        while (q18.next())
        {
            int jid = q18.value(1).toInt();
            int marks = q18.value(2).toInt();
            firstRow = new QStandardItem(QString::number(jid));
            model->setItem(j,0,firstRow);
            firstRow = new QStandardItem(QString::number(marks));
            model->setItem(j,1,firstRow);

            j++;

        }
        j++;

        firstRow = new QStandardItem(QString("Percentile"));
        model->setItem(j,0,firstRow);
        firstRow = new QStandardItem(QString::number(avg));
        model->setItem(j,1,firstRow);
        j++;
        firstRow = new QStandardItem(QString("PID"));
        model->setItem(j,0,firstRow);
        firstRow = new QStandardItem(QString(pid));
        model->setItem(j,1,firstRow);


        di->ui->di_table->setModel(model);
        di->ui->di_table->resizeColumnsToContents();
        di->show();



}

void Home::on_prnt_oresult_clicked()
{
    int category=ui->comboBox->currentIndex();
    QString data;
    data="<head><style>"
         "table, td, th {text-align: center;}"
         "</style></head><body>"
         "<p><img src='pict_logo2.png' align='left'><img src='logo4.png' align='right'><h3 align='center'>PUNE INSTITUTE OF COMPUTER TECHNOLOGY</h3><h4 align='center'>IMPETUS AND CONCEPTS 2017</h4></p><hr>";
    QSqlQuery q20;

    QString pid;
    double avg;
    int jtime;
    int cat;
    int j=0;

    if(category==0)
    {
        data=data+"<h3><center>Concepts Overall Result </center></h3><br>";
        data=data+"<center><table border='1' cellspacing='0' cellpadding='0' width='100%'>"
                  "<tr><th width='15%'>Rank</th><th width='15%'>PID</th><th width='20%'>Percentile</th><th width='35%'>No. of times Judged</th><th width='15%'>Category</th></tr>";

        q20.exec("SELECT * FROM Result ORDER BY Average DESC");

    }
    else if(category!=0)
    {
        data=data+"<h3><center>Concepts Result For Category No. : "+QString::number(category)+"</center></h3><br>";
        data=data+"<center><table border='1' cellspacing='0' cellpadding='0' width='100%'>"
                  "<tr><th width='15%'>Rank</th><th width='15%'>PID</th><th width='20%'>Percentile</th><th width='35%'>No. of times Judged</th><th width='15%'>Category</th></tr>";

        q20.exec("SELECT * FROM Result WHERE Category="+QString::number(category)+" ORDER BY Average DESC");

    }

    while (q20.next())
    {
            pid = q20.value(0).toString();
            avg = q20.value(1).toDouble();
            jtime = q20.value(2).toInt();
            cat =q20.value(3).toInt();

            data=data+"<tr><td>"+QString::number(j+1)+"</td><td>"+pid+"</td><td>"+QString::number(avg)+"</td><td>"+QString::number(jtime)+"</td><td>"+QString::number(cat)+"</td></tr>";

            j++;
    }

    data=data+"</center></table></body>";
    doc.setHtml(data);

    QString pdfFile = QFileDialog::getSaveFileName(this);
    QPrinter printer;
    printer.setOutputFileName(pdfFile);
    printer.setOutputFormat(QPrinter::PdfFormat);
    doc.print(&printer);
    printer.newPage();
}

void Home::on_prnt_presult_clicked()
{
    QString pid=ui->lineEdit_15->text();
    QString data;
    data="<head><style>"
         "table, td, th {text-align: center;}"
         "</style></head><body>"
         "<p><img src='pict_logo2.png' align='left'><img src='logo4.png' align='right'><h3 align='center'>PUNE INSTITUTE OF COMPUTER TECHNOLOGY</h3><h4 align='center'>IMPETUS AND CONCEPTS 2017</h4></p><hr>";
    QSqlQuery q21,q22,q23,q24;


    double avg=0,avg2=0;
    int jid;
    int mk,dm;
    QString ttl,clg,m1,m2,m3,m4,m5,jname,catname;
    int j=1;


    if(pid!="")
    {
        data=data+"<h3><center>Project : "+pid+"</center></h3>";

        q22.exec("SELECT Average FROM Projects WHERE PID='"+pid+"';");
        if(q22.next())
            avg=q22.value(0).toDouble();

        q23.exec("SELECT * FROM Groupinfo WHERE PID='"+pid+"';");
        if(q23.next())
        {
            dm=q23.value(1).toInt();
            ttl=q23.value(2).toString();
            clg=q23.value(3).toString();
            m1=q23.value(4).toString();
            m2=q23.value(5).toString();
            m3=q23.value(6).toString();
            m4=q23.value(7).toString();
            m5=q23.value(8).toString();
        }

        q24.exec("SELECT * FROM Cats WHERE catno="+QString::number(dm)+";");
        if (q24.next())
        {
            catname=q24.value(1).toString();
        }
        data=data+"<p><b>Category : </b>"+QString::number(dm)+" . "+catname+"<br/><br><b>Title : </b>"+ttl+"<br/><b>College : </b>"+clg+"<br/><br/>Member 1 : "+m1+"<br/>Member 2 : "+m2+"<br/>Member 3 : "+m3+"<br/>Member 4 : "+m4+"<br/>Member 5 : "+m5+"</p>";
        data=data+"<center><h4>Marks</h4><table border='1' cellspacing='0' cellpadding='0' width='100%'>"
                  "<tr><th width='15%'>Sr.</th><th width='15%'>JID</th><th width='55%'>Judge</th><th width='15%'>Marks</th></tr>";

        q21.exec("SELECT * FROM Marks WHERE PID='"+pid+"'");
        while (q21.next())
        {
            jid = q21.value(1).toInt();
            mk = q21.value(2).toInt();
            avg2=avg2+mk;

            q23.exec("SELECT * FROM Judgeinfo WHERE JID="+QString::number(jid)+";");
            if(q23.next())
            {
                jname=q23.value(1).toString();
            }

            data=data+"<tr><td>"+QString::number(j)+"</td><td>"+QString::number(jid)+"</td><td>"+jname+"</td><td>"+QString::number(mk)+"</td></tr>";

            j++;
        }

        avg2=avg2/(j-1);
    }

    data=data+"</center></table><br><h4 align='right'>Average : "+QString::number(avg2)+"<br><h4 align='right'>Percentile : "+QString::number(avg)+"</body>";
    doc.setHtml(data);

    QString pdfFile = QFileDialog::getSaveFileName(this);
    QPrinter printer;
    printer.setOutputFileName(pdfFile);
    printer.setOutputFormat(QPrinter::PdfFormat);
    doc.print(&printer);
    printer.newPage();


}

void Home::on_about_clicked()
{
    di->ui->di_table->hide();
    di->ui->label->show();
    di->show();

}
