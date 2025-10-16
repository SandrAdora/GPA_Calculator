#include "admin_dialog.h"
#include "ui_admin_dialog.h"
#include <QDebug>
#include <QMessageBox>
#include "registration_dialog.h"
Admin_Dialog::Admin_Dialog( Person* p, Administration* a,QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Admin_Dialog)
    ,person(p)
    , admin(a)

{
    ui->setupUi(this);


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
    // open admin profile


}


void Admin_Dialog::on_lineEdit_admin_returnPressed()
{
    this->on_pushButton_admin_ok_clicked();
}

