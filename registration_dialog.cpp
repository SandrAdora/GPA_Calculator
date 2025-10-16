#include "registration_dialog.h"
#include "ui_registration_dialog.h"
#include "signin_dialog.h"

#include <QMessageBox>


registration_Dialog::registration_Dialog(Person*p, Administration* admin, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::registration_Dialog)
    , person(p)
    , admnistration(admin)

{

    ui->setupUi(this);
    this->admnistration = new Administration();
    setWindowTitle("Registration");
    ui->widget->setEnabled(true);
    ui->comboBox_courses->setEditable(true);
    ui->comboBox_gender->setEditable(true);
    populateComboCourses();
    populateComboGender();
}

registration_Dialog::~registration_Dialog()
{
    delete ui;
    for(auto student : students)
        delete student;
    students.clear();
    delete this->admnistration;

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
    QString curr_gpa = ui->lineEdit_gpa->text();;

    bool success = false;
    this->hide();

    if(major == "Administrator")
    {
        success=this->admnistration->register_admin(fullname,birthdate,gender,email,password);
        if(success)
        {

        Admin_Dialog* adminSignIn= new Admin_Dialog();
        adminSignIn->show();
        }
        else{
            QMessageBox::warning(this, "Admin Registration status", "failed");
            return;
        }
    }
    else
    {
        Student obj;
        Courses course = obj.get_course_cour(major);
        success=this->admnistration->register_student(course, fullname, birthdate, gender, email, password, curr_gpa);
        if(success){
            signIn_Dialog *signIn = new signIn_Dialog(this);
            signIn->show();
        }else{
            QMessageBox::warning(this,"Student Registration Status", "Failed");
            return;
        }
    }

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

