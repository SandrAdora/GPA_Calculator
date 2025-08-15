#include "admin_signIn_dialog.h"
#include "ui_admin_signIn_dialog.h"

Admin_signIn_Dialog::Admin_signIn_Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Admin_signIn_Dialog)
{
    ui->setupUi(this);
}

Admin_signIn_Dialog::~Admin_signIn_Dialog()
{
    delete ui;
}
