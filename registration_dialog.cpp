#include "registration_dialog.h"
#include "ui_registration_dialog.h"
#include "signin_dialog.h"
#include "administration.h"
#include "admin_dialog.h"
#include <QMessageBox>
#include "mysqlite_db.h"

registration_Dialog::registration_Dialog( QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::registration_Dialog)

{
    ui->setupUi(this);
    ui->widget->setEnabled(true);
    ui->comboBox_courses->setEditable(true);
    ui->comboBox_gender->setEditable(true);
    if(ui->comboBox_courses->currentText() == "Administration")
        ui->checkBox_reg_as_admin->setEnabled(false);
    else
        ui->checkBox_reg_as_admin->setEnabled(true);
    populateComboCourses();
    populateComboGender();
}

registration_Dialog::~registration_Dialog()
{
    delete ui;
}

// Populating Comboboxes
void registration_Dialog::getCoursesList()
{
    coursesList = {
        "As:",
        "Mathematics",
        "Informatics",
        "Medical Informatics",
        "Technical Informatics",
        "Business Informatics",
        "Human Medicine",
        "Vet Medicine",
        "Data Science",
        "Artifical Intelligence",
        "Biomedical Engineering",
        "Medical Engineering",
        "Electronical Engineering",
        "Architect",

    };

}

void registration_Dialog::populateComboCourses()
{
    getCoursesList();
    ui->comboBox_courses->addItems(coursesList);
}

void registration_Dialog::getGenders()
{
    // in this section the list will be populated
    genderList = {
        "other",
        "Male",
        "Female",

    };
}

void registration_Dialog::populateComboGender()
{
    getGenders();
    ui->comboBox_gender->addItems(genderList);
}


void registration_Dialog::on_pushButton_signUp_clicked()
{

    QString major = ui->comboBox_courses->currentText();
    QString fullname = ui->lineEdit_fullname->text();
    QDate  birthdate = ui->dateEdit_birthdate->date();
    QString gender = ui->comboBox_gender->currentText();
    QString email = ui->lineEdit_email->text();
    QString password = ui->lineEdit_password->text();
    QString curr_gpa = "";

    // ---- Database connection
    QSqlDatabase db_connection = QSqlDatabase::addDatabase("QSQLITE");
    db_connection.setDatabaseName("C:/Users/sandr/Documents/GitHub/Qt_Projects/GPA_Calculator/database/db_gpa.db");

    // check if file exists
    if(QFile::exists("C:/Users/sandr/Documents/GitHub/Qt_Projects/GPA_Calculator/database/db_gpa.db")){

        qDebug() << "File exists, check connection to the database";
        if (!db_connection.open()) {
            QMessageBox::critical(nullptr, "Database Connection", db_connection.lastError().text());
            qDebug() << "Error: " << db_connection.lastError();
            return;
        } else {
            qDebug() << "Connection established";
        }
    }else{
        QMessageBox::warning(nullptr, "File Status:", "Error message: File does not exist") ;
        return;
    }
    QSqlQuery query;
    query = QSqlQuery(db_connection);

    QString b_date = birthdate.toString();

    this->hide();

    if(major == "Administrator")
    {
        query.prepare("INSERT INTO admins(fullname,birthdate, gender, email, password ) VALUES('" + fullname + "','" + b_date + "','" + gender + "','" + email + "','" + password + "' )");

        if(query.exec())
        {
            Admin_Dialog* adminSignIn = new Admin_Dialog(this);
            adminSignIn->show();
        }else  {
            qDebug() << "Error: Creating a new Admin" << query.lastError().text() << query.lastQuery();
        }
    }
    else
    {
        // --- Insert statement Sign-In
        query.prepare("INSERT INTO students(course,fullname, birthdate, gender, email, password, currentGpa ) VALUES('" + major + "','" + fullname + "','" + b_date +"','" + gender +"','" + email + "','"  + password +  "', '" + curr_gpa+ "' )");
        if(query.exec())
        {
            signIn = new signIn_Dialog(this);
            signIn->show();
        }else {
            qDebug() << "Error: Creating a new Student " << query.lastError().text()   << " last query: " << query.lastQuery();
        }
    }
    db_connection.close();
}


void registration_Dialog::on_pushButton_cancel_clicked()
{

    ui->checkBox_reg_as_admin->setChecked(false);
    ui->dateEdit_birthdate->setDate(QDate::currentDate());
    ui->lineEdit_email->setText("");
    ui->lineEdit_fullname->setText("");
    ui->lineEdit_password->setText("");
    ui->comboBox_courses->setEditText("");
    ui->comboBox_gender->setEditText("");
}


void registration_Dialog::on_checkBox_reg_as_admin_clicked()
{


    // check for response when checkbox is clicked
    connect(ui->checkBox_reg_as_admin, &QCheckBox::clicked, this, []() {
        qDebug() << "Registration as Admin clicked!";
    });

    ui->comboBox_courses->setEditText("Administrator");
}

