#include "admin_dialog.h"
#include "ui_admin_dialog.h"
#include <QDebug>
#include <QMessageBox>
#include "registration_dialog.h"
#include "admin_profile_dialog.h"
Admin_Dialog::Admin_Dialog( Person* p, Administration* a,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Admin_Dialog)
    ,person(p)
    , admin(a)

{
    ui->setupUi(this);
    setWindowTitle("Administration");


}

Admin_Dialog::~Admin_Dialog()
{
    delete ui;



}

bool Admin_Dialog::get_box() const
{
    // return check state
    return ui->checkBox_new_admin->isChecked();
}




void Admin_Dialog::on_checkBox_new_admin_clicked()
{
    hide();
    registration_Dialog* reg = new registration_Dialog();
    reg->show();

}




void Admin_Dialog::on_pushButton_admin_ok_clicked()
{
    // get Admin details

    QString usr_pw = ui->lineEdit_admin->text();
    QString email = ui->lineEdit_email->text();

    bool ok = this->admin->get_administration()->signInAdmin( email, usr_pw);
    if(ok)
    {
        admin_profile_vec = admin->get_administration()->get_Admin(email, usr_pw);
        Admin* obj = new Admin();
        obj->set_fullname( admin_profile_vec[0]->get_fullname());
        obj->set_birthdate(admin_profile_vec[0]->get_birthdate());
        QString gender = admin->genderToString(admin_profile_vec[0]->get_gender());
        obj->set_gender(gender);
        obj->set_email(admin_profile_vec[0]->get_email());
        obj->set_password(admin_profile_vec[0]->get_password());
        obj->set_personId(admin_profile_vec[0]->get_admin_id());

        // pass object to profile
        this->admin_profile = new Admin_Profile_Dialog(obj);
        this->admin_profile->show();
        hide();
        return;
    }
    else
        QMessageBox::warning(nullptr, "Admin Signing In Error", "failed");

    close();



}


void Admin_Dialog::on_lineEdit_admin_returnPressed()
{
    this->on_pushButton_admin_ok_clicked();
}

