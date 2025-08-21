#include "admin_profile_dialog.h"
#include "ui_admin_profile_dialog.h"

Admin_Profile_Dialog::Admin_Profile_Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Admin_Profile_Dialog)
{
    ui->setupUi(this);
    ui->listView_admin_profile->setEnabled(true);
}

Admin_Profile_Dialog::~Admin_Profile_Dialog()
{
    delete ui;
}
