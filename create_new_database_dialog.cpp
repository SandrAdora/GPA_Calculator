#include "create_new_database_dialog.h"
#include "ui_create_new_database_dialog.h"

Create_new_Database_Dialog::Create_new_Database_Dialog( QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Create_new_Database_Dialog)

{
    ui->setupUi(this);
    this->populateDBCombo();
}

Create_new_Database_Dialog::~Create_new_Database_Dialog()
{
    delete ui;
}

void Create_new_Database_Dialog::populateDBCombo()
{
    get_dbs();
    ui->comboBox_choose_db->addItems(this->db_list);

}

void Create_new_Database_Dialog::get_dbs()
{
    this->db_list.append(QSqlDatabase::drivers());

}

void Create_new_Database_Dialog::on_pushButton_connect_db_clicked()
{
    // build connection with the db the user selected
    QString user_choice = ui->comboBox_choose_db->currentText();
    QString db_name  = ui->lineEdit_db_name->text(); // db name
    connection_db = new MySqlite_db(user_choice, db_name);
    bool connected = connection_db->check_status();

    if(connected)
        QMessageBox::information(nullptr, "Database Connection", "open successeded...");
    else
        QMessageBox::warning(nullptr, "Database Connection", "Could not be found...");



}


void Create_new_Database_Dialog::on_pushButton_disconnect_db_clicked()
{
    this->connection_db->disconnect_db();
    QMessageBox::information(this, "Database Disconnection", "disconnecting database...successeded");
}

