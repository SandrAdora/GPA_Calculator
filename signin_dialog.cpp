#include "signin_dialog.h"
#include "ui_signin_dialog.h"
#include <QMessageBox>

signIn_Dialog::signIn_Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::signIn_Dialog)
{
    ui->setupUi(this);
}

signIn_Dialog::~signIn_Dialog()
{
    delete ui;
}

void signIn_Dialog::on_pushButton_clicked()
{
    QMessageBox::information(this, "Profile", "Successfull log in...");
    hide();
    pro = new student_profile_Dialog(this);
    // TODO: Logic before showing profile picture
    pro->show();
}


void signIn_Dialog::on_pushButton_signIn_canceled_clicked()
{
    ui->lineEdit_email->setText("");
    ui->lineEdit_password->setText("");
}

