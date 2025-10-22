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

    qDebug() << "Attempting sign-in with email:" << email;

    bool ok = admin_class->get_administration()->SignInStudent(email, password);
    if(ok)
    {
        student_vec = admin_class->get_administration()->get_student(email, password);

        if (student_vec.empty() || student_vec[0] == nullptr) {
            QMessageBox::warning(this, "Fehler", "Kein gültiger Student gefunden.");
            return;
        }
        Student* obj = new Student(); // ✅ Allocate memory
        obj->set_personId(student_vec[0]->get_personID());
        obj->set_course(student_vec[0]->get_course());
        obj->set_fullname(student_vec[0]->get_fullname());
        obj->set_birthdate(student_vec[0]->get_birthdate());
        obj->set_email(student_vec[0]->get_email());
        Gender gen = student_vec[0]->get_gender();
        QString g_ = admin_class->genderToString(gen);
        obj->set_gender(g_);
        obj->set_password(student_vec[0]->get_password());
        obj->set_course(student_vec[0]->get_course());
        QString gpa = QString::number(student_vec[0]->get_gpa());
        double gpa_ = gpa.toDouble();
        obj->set_gpa(gpa_);


        hide();
        Subject* subject_obj=new Subject("Programming one", 2, 2);
        std::vector<Subject*> sub= {subject_obj};
        this->pro = new student_profile_Dialog(obj, sub, this);
        pro->show();
          return; // ✅ Prevent falling through to error message

        }



    QMessageBox::warning(this, "Error", "Sign In failed");
    close();


}



void signIn_Dialog::on_pushButton_signIn_canceled_clicked()
{
    ui->lineEdit_email->setText("");
    ui->lineEdit_password->setText("");
}

