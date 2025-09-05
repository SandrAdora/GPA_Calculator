#include "admin_profile_dialog.h"
#include "ui_admin_profile_dialog.h"
#include "create_table_dialog.h"
#include "create_new_database_dialog.h"
#include <QLabel>
#include <QPixmap>
#include <QHBoxLayout>
Admin_Profile_Dialog::Admin_Profile_Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Admin_Profile_Dialog)
{
    ui->setupUi(this);
    ui->listView_admin_profile->setEnabled(true);
    this->current_date();

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

void Admin_Profile_Dialog::current_date()
{
    this->_date = QDate::currentDate();
    QLabel* dateLable = new QLabel(this->_date.toString());
    dateLable->setStyleSheet("font-size: 18px; font-weight: bold; color: #333;");


    QPixmap pix(":/icons/documentation/logos/admin.png");
    QLabel* img = new QLabel();
    img->setPixmap(pix.scaled(300, 500, Qt::KeepAspectRatio));
    QHBoxLayout* hl = new QHBoxLayout();
    hl->addWidget(img);

    this->vlayout = new QVBoxLayout();
    this->vlayout->addWidget(dateLable);
    this->vlayout->addLayout(hl);

    ui->verticalLayout_date->addLayout(this->vlayout);

}



void Admin_Profile_Dialog::on_pushButton_view_table_clicked()
{
    // open another dialog that shows all tables available in the database

}

