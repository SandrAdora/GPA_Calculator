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
class Administration : public Student
{
public:
    static Administration* Instance(); // Instance

    unique_ptr<Person> FactoryMethod(); // factory method for creating different obj. like student or admin


    unique_ptr<Person> create_object(MethodType& ); // call factory method and returns requested obj

    void add_student(Courses& , QString &, QDate &, QString&, QString&, QString&); // vals consitsts of course of study, fullname, birithdate, gender, email and password
    void add_new_subjects(QString&, int&, double&); // name of subject, ects and weights of each subjects
    bool delete_subject(int); // id of subject to be deleted
    void view_all_subjects() const;
    bool delete_student(int &); // id of student to be deleted
    void display_all_Students() const;
    bool update_student_name(int&, QString); // id of student and what operation should be done
    bool update_subject_ect(int&, int); // id and ect
    bool update_subject_name(int&, QString&); // id and name of the object
    bool update_subject_weights(int& ,double); // id and new weights for subject

    // unequal operator




protected:
    Administration();

private:
    std::vector<std::unique_ptr<Student>>students;
    MethodType type;
    std::vector<Subject*> subjects;
    unique_ptr<Person> ptr;
    static Administration* _instance;

};


#endif // ADMINISTRATION_H
