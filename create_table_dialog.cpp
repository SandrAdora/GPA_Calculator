#include "create_table_dialog.h"
#include "ui_create_table_dialog.h"
#include "add_elem_to_table_dialog.h"
#include "admin_profile_dialog.h"
#include <QIcon>
#include <QTime>
#include <qcombobox.h>
#include <QStringList>
Create_Table_Dialog::Create_Table_Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Create_Table_Dialog)
{
    ui->setupUi(this);
    ui->label_time->setText(QTime::currentTime().toString("hh:mm:ss"));
    create_menue_bar();
    populate_colum_comboBox();


}

Create_Table_Dialog::~Create_Table_Dialog()
{
    delete ui;
}

void Create_Table_Dialog::on_pushButton_cancel_create_table_input_clicked()
{
    ui->comboBox_create_table_dia_columns->setCurrentText("Colums for table");
    ui->lineEdit_create_table_dialog->setText("");
}



QString Create_Table_Dialog::get_column() const
{
    return ui->comboBox_create_table_dia_columns->currentText();
}
QString Create_Table_Dialog::get_table_name() const
{
    return ui->lineEdit_create_table_dialog->text();
}

void Create_Table_Dialog::add_widgets_to_VBox_Layout()
{

    // convert to an int
    bool ok;
    int columns = get_column().toInt(&ok);
    if(ok)
    {


        for(int i = 0; i < columns; ++i)
        {
            QLineEdit* columnNameEdit = new QLineEdit(this);
            QComboBox* typeSelector = new QComboBox(this);
            QComboBox* columnRole = new QComboBox(this);

            typeSelector->addItems({"INTEGER", "TEXT", "REAL", "BLOB"});
            columnRole->addItems({"PRIMARY KEY AUTOINCREMENT", "FOREIGN KEY"});
            layout->addRow("Column" + QString::number(i+1), columnNameEdit);
            layout->addRow("Type", typeSelector);
            layout->addRow("Role", columnRole);


            QWidget* referenceContainer = new QWidget(this);
            QFormLayout* referenceLayout = new QFormLayout(referenceContainer);
            QLineEdit* refenceEdit = new QLineEdit(this);
            referenceLayout->addRow("Reference", refenceEdit);
            referenceContainer->setVisible(false); // hide initially
            connect(columnRole, &QComboBox::currentTextChanged, this, [referenceContainer](const QString& text){
                referenceContainer->setVisible(text == "FOREIGN KEY");
            });

            layout->addRow(referenceContainer );
            column_inputs.append({columnNameEdit, typeSelector, columnRole , refenceEdit});


        }
    }
}


void Create_Table_Dialog::on_pushButton_add_elements_to_table_clicked()
{
    hide();
    Add_Elem_To_Table_Dialog* dia = new Add_Elem_To_Table_Dialog(this);
    dia->show();

}

void Create_Table_Dialog::create_menue_bar()
{


    QMenu* menu = new QMenu(this);
    QAction* back  = new QAction(QIcon(":/icons/documentation/logos/back.png"),"back", this);

    // connect action to goback method
    connect(back, &QAction::triggered, this, &Create_Table_Dialog::on_actiongoBack_triggered);

    // add action to menu
    menu->addAction(back);

    // create a seprate vlayout
    QVBoxLayout *vl = new QVBoxLayout;
    vl->addWidget(menu);
    ui->verticalLayout_admin_menuebar->addLayout(vl);

}

void Create_Table_Dialog::how_many_columns_available()
{
    this->columns = {
        "Colums for table","2", "3", "4","5","6","7","8","9","10","11","12","13","14","15","16",
        "17","18","19","20"
};

}

void Create_Table_Dialog::populate_colum_comboBox()
{

    this->how_many_columns_available();
    ui->comboBox_create_table_dia_columns->addItems(columns);

}

void Create_Table_Dialog::add_reference()
{

}


void Create_Table_Dialog::on_actiongoBack_triggered()
{
    hide();
    Admin_Profile_Dialog* diag = new Admin_Profile_Dialog(this);
    diag->show();
}
