#include "signin_dialog.h"
#include "ui_signin_dialog.h"
#include <QMessageBox>
#include "mysqlite_db.h"

signIn_Dialog::signIn_Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::signIn_Dialog)
{
    ui->setupUi(this);
}

signIn_Dialog::~signIn_Dialog()
{
    delete ui;
    delete this->pro;
    this->pro = nullptr;
}

void signIn_Dialog::on_pushButton_clicked()
{
    QString email = ui->lineEdit_email->text();
    QString password = ui->lineEdit_password->text();

    std::vector<Student* > profile = admin_class->SignInStudent(email, password);


    if(!profile.empty())
    {
        this->pro = new student_profile_Dialog(profile);
        hide();
        pro->show();
        return;
    }
    QMessageBox::warning(this, "SignIn status", "failed.. email or password was wrong or student doesnt  exist");


}


void signIn_Dialog::on_pushButton_signIn_canceled_clicked()
{
    ui->lineEdit_email->setText("");
    ui->lineEdit_password->setText("");
}

