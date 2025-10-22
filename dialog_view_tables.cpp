#include "dialog_view_tables.h"
#include "ui_dialog_view_tables.h"
#include "mysqlite_db.h"
#include <QSqlQueryModel>
#include <QDebug>
#include <QMenu>
#include <QVBoxLayout>
#include "admin_profile_dialog.h"
#include <QToolButton>
Dialog_view_tables::Dialog_view_tables(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog_view_tables)
{
    ui->setupUi(this);
    this->goback_button();
}

Dialog_view_tables::~Dialog_view_tables()
{
    delete ui;
}

void Dialog_view_tables::on_pushButton_load_table_clicked()
{
    QString table_name  = ui->lineEdit_name_of_table_to_load->text(); // table user inputs
    MySqlite_db* db; // database for setting up connection
    bool ok = db->status();
    QSqlQuery* qry;
    QSqlQueryModel* modal = new QSqlQueryModel();
    if(!ok){ // check database status
        qDebug() << "No Connection!!...";
        return;
    }
    qry->prepare("SELECT * " + table_name);
    bool ex = qry->exec();
    if(!ex){
        qDebug() <<"Error: Last Error: " << qry->lastError() << "Error: " << qry->lastQuery();
    }
    ui->tableView_table->setModel(modal);
}

void Dialog_view_tables::on_actiongoback_triggered()
{
    hide();
    Admin_Profile_Dialog* ad = new Admin_Profile_Dialog();
    ad->show();
}

void Dialog_view_tables::goback_button()
{
    // Create the action
    QAction* go_back_act = new QAction(QIcon(":/icons/documentation/logos/back.png"), "Back", this);
    connect(go_back_act, &QAction::triggered, this, &Dialog_view_tables::on_actiongoback_triggered);
    QMenu* menu = new QMenu(this);

    QVBoxLayout* vl = new QVBoxLayout;
    menu->addAction(go_back_act);
    vl->addWidget(menu);
    // Add the tool button to your layout
    ui->verticalLayout_back->addLayout(vl);

}


