#ifndef REGISTRATION_DIALOG_H
#define REGISTRATION_DIALOG_H

#include "ui_registration_dialog.h"
#include "signin_dialog.h"
#include "administration.h"
#include "person.h"
#include "Student.h"
#include "admin_dialog.h"
#include "student_profile_dialog.h"


#include <QDialog>

namespace Ui {
class registration_Dialog;
}

class registration_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit registration_Dialog( Person* = nullptr, Administration* = nullptr,QWidget *parent = nullptr );
    ~registration_Dialog();

private slots:
    void on_pushButton_cancel_clicked();

    void on_pushButton_signUp_clicked();

    void on_checkBox_reg_as_admin_clicked();

private:
    Ui::registration_Dialog *ui;
   ;
    Person* person;

    Administration* admnistration;




    // Filling out the Combolist
    void getCoursesList();

    void populateComboCourses();
    QStringList coursesList;
    QStringList genderList;
    void getGenders();
    void populateComboGender();




};

#endif // REGISTRATION_DIALOG_H
