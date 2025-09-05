#ifndef CREATE_TABLE_DIALOG_H
#define CREATE_TABLE_DIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QList>
#include <QPair>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QMenu>
#include <QTimeEdit>
#include <QWidget>


struct ColumnInputs
{
    QLineEdit* nameEdit;
    QComboBox* typeSelector;
    QComboBox* role;
    QLineEdit* references;
};


namespace Ui {
class Create_Table_Dialog;
}

class Create_Table_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Create_Table_Dialog(QWidget *parent = nullptr);
    QString get_column() const;
    QString get_table_name() const;
    void add_widgets_to_VBox_Layout(); // arg. should be the amount of colums to be created
    ~Create_Table_Dialog();

private slots:
    void on_pushButton_cancel_create_table_input_clicked();

    void on_pushButton_add_elements_to_table_clicked();
    void on_actiongoBack_triggered();

private:
    Ui::Create_Table_Dialog *ui;
    QStringList columns;
    QString col_str;
    QString table_name;
    QFormLayout* layout;
    QVBoxLayout* vl;
    QList<ColumnInputs> column_inputs; // Allows append of multiple different elements of different datatypes to be stored together
    void create_menue_bar();
    void how_many_columns_available();
    void populate_colum_comboBox();
    void add_reference();



};

#endif // CREATE_TABLE_DIALOG_H
