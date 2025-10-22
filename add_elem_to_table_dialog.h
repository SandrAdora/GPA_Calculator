#ifndef ADD_ELEM_TO_TABLE_DIALOG_H
#define ADD_ELEM_TO_TABLE_DIALOG_H

#include <QDialog>
#include "create_table_dialog.h"
#include "mysqlite_db.h"
#include <QCheckBox>
#include <QMenu>
#include <QtCore/qglobal.h> // or include <QCoreApplication> indirectly
#include "administration.h"



namespace Ui {
class Add_Elem_To_Table_Dialog;
}

class Add_Elem_To_Table_Dialog : public QDialog
{
    Q_OBJECT

public:
     explicit Add_Elem_To_Table_Dialog(Create_Table_Dialog* sourceDialog, QWidget *parent = nullptr);
    ~Add_Elem_To_Table_Dialog();



private slots:
    void on_pushButton_create_sql_clicked();

    void on_pushButton_add_elem_cancel_clicked();
    void on_actiongoBack_triggered();


private:
    Ui::Add_Elem_To_Table_Dialog *ui;
    Create_Table_Dialog* create_table = new Create_Table_Dialog(this);
    MySqlite_db* db_instance = new MySqlite_db();
    QLineEdit* elem;
    QLineEdit* reference;
    QComboBox* type ;  QComboBox* role;
    QList<QLineEdit*> elemFields;
    QList<QComboBox*> typeFields;
    QList<QComboBox*> roleFields;
    QList<QLineEdit*> referenceFields;
    QList<QCheckBox*> incrementFields;
    QStringList sql_elems;
    Administration* administator;

    void available_elems();
    void go_back_menu();
    void send_to_database(std::vector<QStringList>);
};
#endif // ADD_ELEM_TO_TABLE_DIALOG_H
