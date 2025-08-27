#include "add_elem_to_table_dialog.h"
#include "ui_add_elem_to_table_dialog.h"
#include "create_table_dialog.h"

#include <QLabel>
#include <QMessageBox>


Add_Elem_To_Table_Dialog::Add_Elem_To_Table_Dialog(Create_Table_Dialog* sourceDialog, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Add_Elem_To_Table_Dialog)
    , create_table(sourceDialog)
{
    ui->setupUi(this);
    available_elems();
    ui->label_table_name->setText(this->create_table->get_table_name());
    this->go_back_menu();


}

Add_Elem_To_Table_Dialog::~Add_Elem_To_Table_Dialog()
{
    delete ui;
}

void Add_Elem_To_Table_Dialog::available_elems()
{
    bool ok;
    int cols = this->create_table->get_column().toInt(&ok);
    if (!ok || cols <= 0) return;



    QStringList typesList = {"Element type", "INTEGER", "REAL", "TEXT", "BLOB", ""};
    QStringList rolesList = {"Element role", "PRIMARY KEY", "FOREIGN KEY", ""};

    for (int i = 0; i < cols; ++i)
    {
        elem = new QLineEdit;
        elem->setPlaceholderText("Name of Element " + QString::number(i + 1));
        this->elemFields.append(this->elem);

        this->type = new QComboBox;
        type->addItems(typesList);
        this->typeFields.append(this->type);

        this->role = new QComboBox;
        role->addItems(rolesList);
        this->roleFields.append(this->role);
        this->autoincrement = new QCheckBox("Auto Increment");
        this->incrementFields.append(this->autoincrement);
        QHBoxLayout* rowLayout = new QHBoxLayout;
        rowLayout->addWidget(elem);
        rowLayout->addWidget(type);
        rowLayout->addWidget(role);
        rowLayout->addWidget(autoincrement);

        ui->verticalLayout_display_items->addLayout(rowLayout);
    }
}

void Add_Elem_To_Table_Dialog::on_actiongoBack_triggered()
{
    hide();
    create_table->show();
}

void Add_Elem_To_Table_Dialog::on_pushButton_create_sql_clicked()
{
    QMessageBox::information(this, "SQL", "creating sql statement...");

}

void Add_Elem_To_Table_Dialog::on_pushButton_add_elem_cancel_clicked()
{

    for (int i= 0; i < this->elemFields.size(); ++i)
    {
        this->elemFields[i]->setText("");
        this->typeFields[i]->setCurrentText("Element type");
        this->roleFields[i]->setCurrentText("Element Role");
        this->incrementFields[i]->setChecked(false);
    }

}

void Add_Elem_To_Table_Dialog::go_back_menu()
{
    QMenu* menu = new QMenu(this);
    QVBoxLayout* vl = new QVBoxLayout;

    QAction* go_back = new QAction(QIcon(":/icons/documentation/logos/back.png"),"back", this);
    // connect
    connect(go_back, &QAction::triggered, this, &Add_Elem_To_Table_Dialog::on_actiongoBack_triggered);

    // add action
    menu->addAction(go_back);

    // add menu to layout
    vl->addWidget(menu);
    // add vl to parent layout
    ui->verticalLayout->addLayout(vl);
}



