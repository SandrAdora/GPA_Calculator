#ifndef ADMINISTRATION_H
#define ADMINISTRATION_H
#include <iostream>
#include <vector>
#include <QString>
#include <QDate>
#include <memory>
#include <QSqlQuery>

#include "student.h"
#include "subject.h"
#include "admin.h"
#include "mysqlite_db.h"



using namespace std;
using str = QString;

/*
 * @brief Class Administration uses Factory method as interface between person and student
 * @param none
 * @return an allocated memory of a student
 */
// method type to create when using factory method
enum MethodType {
    student, admin
};


// responsible for creating and returning the type of person on demand
// new features can be added if neccessary


// factory method class
class Administration : public Student , Admin, Subject
{
public:
    static Administration* Instance(); // Instance
    Administration* get_administration();
    Administration();

    unique_ptr<Person> FactoryMethod(); // factory method for creating different obj. like student or admin


    unique_ptr<Person> create_object(MethodType& ); // call factory method and returns requested obj
// get a specific student
    std::vector<Student*> view_all_student() const; // returns a list of all students
    void view_all_subjects() const;
    bool register_student(Courses& , QString &, QDate &, QString&, QString&, QString&, QString&); // vals consitsts of course of study, fullname, birithdate, gender, email, password and current gpa
    bool delete_student(int &); // id of student to be deleted
    bool update_student_name(int&, QString); // id of student and what operation should be done
    bool SignInStudent(const QString&, const QString&);
    std::vector<Student*> get_student(QString , QString);

    bool register_subject(QString&, int&, double&); // name of subject, ects and weights of each subjects
    bool delete_subject(int); // id of subject to be deleted
    bool update_subject_ect(int&, double&); // id and ect
    bool update_subject_name(int&, QString&); // id and name of the object
    bool update_subject_weights(int& ,double); // id and new weights for subject
    std::vector<Subject*> view_all_subject() const; //returns a ist of all subjects
    std::vector<Subject*> get_student_subjects(int ); // get all student subject
    std::vector<Subject* >get_subject_info(const QString); // display the info of a specific subject
    std::vector<Subject*> subjects;

    bool update_admin_birthdate(int& Qdate);
    bool register_admin(QString&, QDate&, QString&, QString&, QString&); // fullname, birthdate, gender, email and password
    bool update_admin_email(int, QString); // id and new email
    bool update_admin_name(int&, QString); // id of an admin and new name
    std::vector<Admin*> get_Admin(const QString , const QString); // get a specific admin using password
    bool signInAdmin(QString, QString); // Email not reqiured
    std::vector<Admin*> view_all_admin() const; // resturns a list of all admins
    bool delete_admin(int&);

    Courses stringToCourse(QString&);
    QString  courseToString(Courses&);
    Gender stringToGender(QString&);
    QString genderToString(Gender);

    bool check_email(QString&, QString);

    // for each view and get obj an aquivalent qsql statement is needed
    std::vector<Student*>_sql(QSqlQuery); // student vector
    std::vector<Admin*>A_sql(QSqlQuery&); // admin vector
    std::vector<Subject*>S_sql(QSqlQuery); // subject vector


    //  student register stores all students registered, making retrieving data alot faster
    Student* studentRegister(int ); // returns an obj student


    // Helper Functions
    bool check_status();

    void create_table();
protected:
    Student* student_obj;
private:
    MySqlite_db* db;
    static Administration* admin_instance;
    std::vector<std::vector<Student*>> student_REGISTER;

};


#endif // ADMINISTRATION_H
