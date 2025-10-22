#include "admin_profile_dialog.h"
#include "ui_admin_profile_dialog.h"
#include "create_table_dialog.h"
#include "create_new_database_dialog.h"
#include <QLabel>
#include <QPixmap>
#include <QHBoxLayout>
#include <QGroupBox>
Admin_Profile_Dialog::Admin_Profile_Dialog( Admin* a, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Admin_Profile_Dialog)
    , admin_pro(a)
{
    ui->setupUi(this);
    ui->listView_admin_profile->setEnabled(true);
    this->current_date();
    this->admin_profile();

}

Admin_Profile_Dialog::~Admin_Profile_Dialog()
{
    delete ui;
    delete admin_pro;
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
    hide();
    this->view_tab = new Dialog_view_tables(this);
    this->view_tab->show();
}


/// Admin Profile
///
/// Retrives data from the database and displaying them in the admin profile
/// @parmeter --> none
/// @Return --> none
void Admin_Profile_Dialog::admin_profile()
{


    /// This section displays the the details of the admin
    QGroupBox* groupBox = new QGroupBox();
    QString id = QString::number(admin_pro->get_admin_id());
    QLabel* admin_id = new QLabel(id, groupBox);
    QLabel* admin_name = new QLabel(admin_pro->get_fullname(), groupBox);
    QLabel* admin_email = new QLabel(admin_pro->get_email(), groupBox);

    // adding widgets to layout
    QVBoxLayout* v = new QVBoxLayout();
    v->addWidget(groupBox);
    // add layout to screen
    ui->verticalLayout_profile->addLayout(v);

}

