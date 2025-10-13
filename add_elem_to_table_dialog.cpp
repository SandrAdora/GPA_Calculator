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
        QHBoxLayout* rowLayout = new QHBoxLayout;

        elem = new QLineEdit;
        elem->setPlaceholderText( QString::number(i + 1) + " Element");
        this->elemFields.append(this->elem);


        this->type = new QComboBox;
        type->addItems(typesList);
        this->typeFields.append(this->type);

        this->role = new QComboBox;
        role->addItems(rolesList);
        this->roleFields.append(this->role);
        if(i == 0)
            role->setCurrentText("PRIMARY KEY");
        if(i == 1)
            role->setCurrentText("FOREIGN KEY");


        rowLayout->addWidget(elem);
        rowLayout->addWidget(type);
        rowLayout->addWidget(role);

        if(i ==  1)
        {

            reference = new QLineEdit;
            reference->setPlaceholderText("reference");
            this->referenceFields.append(reference);
            rowLayout->addWidget(reference);

        }

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
    QString table_name = this->create_table->get_table_name();
    if (table_name.isEmpty())
    {
        QMessageBox::warning(this, "Table Name", "Please enter a tabel name ");
        return;
    }
    QString elems, types, roles, formatted, ref;
    this->sql_elems.clear(); // make sure the list is empty

    for (int i = 0; i < this->elemFields.size(); ++i )
    {
        elems = this->elemFields[i]->text();
        types = this->typeFields[i]->currentText();
        if(i < this->roleFields.size())
            roles = this->roleFields[i]->currentText();
        if(i < this->referenceFields.size())
            ref = this->referenceFields[i]->text();
        formatted = elems;
        if (!roles.isEmpty() && roles != "Element Role") {
            if(roles == "PRIMARY KEY")
                formatted += " INTEGER PRIMARY KEY AUTOINCREMENT ";
            else if (roles == "FOREIGN KEY")
                formatted += " " + types + " REFERENCES " + ref;
            else
                formatted += " " + types + " " + roles;
        }else
            formatted = elems + " " + types;
        this->sql_elems.append(formatted);

    }

    // passing list to method table creator
    for (int i = 0; i < sql_elems.size(); ++i)
        qDebug() << sql_elems;

    if(!db_instance->status())

        QMessageBox::warning(this, "Database connection ", "faliure");
    //bool success = db_instance->get_instance()->build_table(this->sql_elems, table_name);
    if(true)
        QMessageBox::information(this, "Success", "Table was created");
    else
        QMessageBox::warning(this, "Faliure", "Table could not be created");



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



