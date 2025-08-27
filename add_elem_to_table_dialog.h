#ifndef ADD_ELEM_TO_TABLE_DIALOG_H
#define ADD_ELEM_TO_TABLE_DIALOG_H

#include <QDialog>
#include "create_table_dialog.h"
#include <QCheckBox>
#include <QMenu>

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
    QLineEdit* elem;
    QComboBox* type ;  QComboBox* role;
    QCheckBox* autoincrement;
    QList<QLineEdit*> elemFields;
    QList<QComboBox*> typeFields;
    QList<QComboBox*> roleFields;
    QList<QCheckBox*> incrementFields;

    void available_elems();
    void go_back_menu();
};
#endif // ADD_ELEM_TO_TABLE_DIALOG_H
