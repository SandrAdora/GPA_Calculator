#ifndef CREATE_NEW_DATABASE_DIALOG_H
#define CREATE_NEW_DATABASE_DIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include <QStringList>

#include "mysqlite_db.h"

namespace Ui {
class Create_new_Database_Dialog;
}

class Create_new_Database_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Create_new_Database_Dialog( MySqlite_db* db, QWidget *parent = nullptr);
    ~Create_new_Database_Dialog();

private slots:
    void on_pushButton_connect_db_clicked();

private:
    Ui::Create_new_Database_Dialog *ui;
    void populateDBCombo();
    void get_dbs();
    QStringList db_list;
    MySqlite_db* db;
};

#endif // CREATE_NEW_DATABASE_DIALOG_H
