#include "mainwindow.h"
#include "ui_mainwindow.h"

# include <QMessageBox>
#include <QPixmap>
#include <QVBoxLayout>
#include <QActionGroup>
#include <QSqlDatabase>
#include <QDebug>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{


    ui->setupUi(this);
    // Add image to window
    //QPixmap pix("/res/documentation/GPA-Calculator-2.png");
    //ui->label->setPixmap(pix.scaled(300, 500, Qt::KeepAspectRatio));
    qDebug()<<QSqlDatabase::drivers();


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_calculate_gpa_clicked()
{

    // Get input
    QString userInput = ui->lineEdit_input_grades->text();

    QRegularExpression reg("[*+]+");
    QStringList str_num = userInput.split(reg, Qt::SkipEmptyParts);

    QStringList grades_str, ects_str;
    for (int i = 0; i < str_num.size(); i += 2)
        grades_str.append(str_num[i]);
    for (int i = 1; i < str_num.size(); i += 2)
        ects_str.append(str_num[i]);

    QList<double> grades;
    QList<int> ects;

    for (const QString &val : grades_str)
        grades.append(val.toDouble());

    for (const QString &val : ects_str)
        ects.append(val.toInt());

    double gpa = 0.0;
    int totalCredits = 0;

    for (int i = 0; i < grades.size(); ++i) {
        gpa += grades[i] * ects[i];
        totalCredits += ects[i];
    }

    double output =  totalCredits == 0 ? 0.0 : gpa / totalCredits;

    QString gpa_str = QString::number(output);
    QMessageBox::information(this, "GPA Calculator", gpa_str);
    ui->lineEdit_gpa_output->setText(gpa_str);


}



void MainWindow::on_actiondelete_triggered()
{
    QString empty_str = "";
    ui->lineEdit_input_grades->setText(empty_str);

}


void MainWindow::on_actionsignIn_triggered()
{
    hide();
    signIn = new signIn_Dialog(this);
    signIn->show();

}


void MainWindow::on_actionregistration_triggered()
{
    hide();
    reg = new registration_Dialog(this);
    reg->show();
}

void MainWindow::on_action_password_triggered(){
    hide();
}
