#include "admin_dialog.h"
#include "ui_admin_dialog.h"
#include <QDebug>
Admin_Dialog::Admin_Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Admin_Dialog)
{
    ui->setupUi(this);

}

Admin_Dialog::~Admin_Dialog()
{
    delete ui;
}

void Admin_Dialog::on_lineEdit_admin_returnPressed()
{
    // open admin interface
    // check if password corresponds with the it password before opening the admin profile
    QString pw = ui->lineEdit_admin->text();
    str it_pass = admin->get_it_admin_password();

    if (pw == it_pass){
        qDebug()<<"pass";
        // open admin profile
    }

}

