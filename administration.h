#ifndef ADMINISTRATION_H
#define ADMINISTRATION_H
#include <iostream>
#include <vector>
#include <QString>
#include <QDate>
#include <memory>


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
class Factory
{
    Person* create(MethodType t)
    {
        switch (t) {
        case MethodType::admin:
            return new Admin();
        case MethodType::student:
            return new Student();
        default:
            break;
        }
    }
};

// factory method class
class Administration : public Student , Admin
{
public:
    static Administration* Instance(); // Instance

    unique_ptr<Person> FactoryMethod(); // factory method for creating different obj. like student or admin


    unique_ptr<Person> create_object(MethodType& ); // call factory method and returns requested obj


    bool add_neww_admin(QString&, QDate&, QString&, QString&, QString&); // fullname, birthdate, gender, email and password
    bool add_student(Courses& , QString &, QDate &, QString&, QString&, QString&); // vals consitsts of course of study, fullname, birithdate, gender, email and password
    void add_new_subjects(QString&, int&, double&); // name of subject, ects and weights of each subjects
    bool delete_subject(int); // id of subject to be deleted
    void view_all_subjects() const;
    bool delete_student(int &); // id of student to be deleted
    void display_all_Students() const;
    bool update_student_name(int&, QString); // id of student and what operation should be done
    bool update_subject_ect(int&, int); // id and ect
    bool update_subject_name(int&, QString&); // id and name of the object
    bool update_subject_weights(int& ,double); // id and new weights for subject
    bool add_new_admin(QString&, QDate&, QString&, QString&, QString&); // fullname, birthdate, gender, email and password
    bool update_admin_name(int&, QString); // id of an admin and new name
    bool update_admin_birthdate(int& Qdate);
    bool update_admin_email(int, QString); // id and new email

    std::vector<Student> view_all_student() const; // returns a list of all students
    std::vector<Admin> view_all_admin() const; // resturns a list of all admins
    std::vector<Subject> view_all_subject() const; //returns a ist of all subjects

    bool delete_admin(int&);


    // unequal operator





protected:
    Administration();

private:
    std::vector<std::unique_ptr<Student>>students;
    MethodType type;
    std::vector<Subject*> subjects;
    std::vector<std::unique_ptr<Admin>> admins;
    unique_ptr<Person> ptr;
    static Administration* _instance;
    MySqlite_db* db;

};


#endif // ADMINISTRATION_H
