#include "admin_dialog.h"
#include "ui_admin_dialog.h"
#include <QDebug>
#include <QMessageBox>
Admin_Dialog::Admin_Dialog( QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Admin_Dialog)

{
    ui->setupUi(this);

}

Admin_Dialog::~Admin_Dialog()
{
    delete ui;

}




void Admin_Dialog::on_checkBox_new_admin_clicked()
{
    hide();
    reg = new registration_Dialog(this);
    reg->show();
}




void Admin_Dialog::on_pushButton_admin_ok_clicked()
{
    // open admin profile
    this->pw = ui->lineEdit_admin->text();
    this->admin = new Admin();
    QString ad_password = this->admin->get_it_admin_password();

    if(pw == ad_password)
    {
        hide();
        admin_profile = new Admin_Profile_Dialog(this);
        admin_profile->show();

    }else{
        QMessageBox::warning(nullptr, "Password failiure", "Wrong password...");
        ui->lineEdit_admin->setText("");
    }



}


void Admin_Dialog::on_lineEdit_admin_returnPressed()
{
    this->on_pushButton_admin_ok_clicked();
}

