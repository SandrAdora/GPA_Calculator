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

    // -- Fetch data from the database
    QSqlDatabase db_connection = QSqlDatabase::addDatabase("QSQLITE");
    db_connection.setDatabaseName("C:/Users/sandr/Documents/GitHub/Qt_Projects/GPA_Calculator/database/db_gpa.db");
    QSqlQuery query(db_connection);

    query.prepare(
        "SELECT ID, course, fullname, birthdate, gender, email, password FROM students WHERE :email=email AND :password=password");
    query.bindValue(":email",  email);
    query.bindValue(":password", password);

    if(query.exec())
    {
        hide();
        this->pro = new student_profile_Dialog(this);
        this->pro->show();

    }

}


void signIn_Dialog::on_pushButton_signIn_canceled_clicked()
{
    ui->lineEdit_email->setText("");
    ui->lineEdit_password->setText("");
}

