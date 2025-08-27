#include "admin_profile_dialog.h"
#include "ui_admin_profile_dialog.h"
#include "create_table_dialog.h"
#include "create_new_database_dialog.h"

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

void Admin_Profile_Dialog::on_pushButton_create_table_clicked()
{
    hide();
    Create_Table_Dialog* create_table = new Create_Table_Dialog(this);
    create_table->show();

}


void Admin_Profile_Dialog::on_commandLinkButton_create_database_clicked()
{
    hide();
    Create_new_Database_Dialog* db = new Create_new_Database_Dialog(this);
    db->show();

}

