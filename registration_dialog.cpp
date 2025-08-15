#include "registration_dialog.h"
#include "ui_registration_dialog.h"
#include "signin_dialog.h"
#include "administration.h"
#include <QMessageBox>

registration_Dialog::registration_Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::registration_Dialog)
{
    ui->setupUi(this);
    populateComboCourses();
    populateComboGender();
}

registration_Dialog::~registration_Dialog()
{
    delete ui;
}

void registration_Dialog::on_pushButton_clicked()
{
    QMessageBox::information(this, "Registration", "was successfull");

    QString major = ui->comboBox_courses->currentText();
    QString fullname = ui->lineEdit_fullname->text();
    QString gender = ui->comboBox_gender->currentText();
    QString email = ui->lineEdit_email->text();
    QString password = ui->lineEdit_password->text();





    signIn = new signIn_Dialog(this);
    signIn->show();



}


// Populating Comboboxes
void registration_Dialog::getCoursesList()
{
    coursesList = {

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
        " ",
        "Male",
        "Female",
        "Dont want to Disclose",
        "nothing"
    };

}

void registration_Dialog::populateComboGender()
{
    getGenders();
    ui->comboBox_gender->addItems(genderList);
}

