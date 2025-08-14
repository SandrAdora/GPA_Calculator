#ifndef ADMINISTRATION_H
#define ADMINISTRATION_H
#include <iostream>
#include <vector>
#include <QString>
#include <QDate>
#include "student.h"
#include <QString>

using namespace std;
using str = QString;
/*
 * @brief Class Administration uses Factory method as interface between person and student
 * @param none
 * @return an allocated memory of a student
 */
// method type to create when using factory method
enum MethodType {
    student, admin, worker_student, subject
};



class Subject: public Student
{
public:
    Subject();
    Subject(str, int, float);
    Subject(str, float);
    Subject(str);

    void set_subject(str);
    str get_subject() const;
    void set_ects(int);
    float get_ects()const;
    void set_weights(int);
    int get_weights() const;
    int get_sub_id() const;

private:
    str subName;
    float ects;
    int weights;
    int sub_id;

};

// factory method class
class Administration : public Subject
{
public:
    Administration();
    Student* FactoryMethod(){ // Factory method as an interface for person and student

        if (type == MethodType::student){
            return new Student();
        }else if(type == MethodType::subject){
            return new Subject();
        }
        return nullptr;//other methodtype can be subsequently added if necessary
    }
    auto* create_object(MethodType& );

    void add_student(QString &, QDate &, QString&, QString&, QString&);
    void add_new_subjects(QString, int, double); // name of subject, ects and weights of each subjects
    bool delete_subject(int);
    void view_all_subjects() const;
    bool delete_student(int &);
    void display_all_Students() const;
    bool update_student_name(int&, QString);

    bool update_subject_ect(int&, int);
    bool update_subject_name(int&, QString&);
    bool update_subject_weights(int& ,double);




private:
    std::vector<Student*>students;
    MethodType type;
    std::vector<Subject*> subjects;
    Student* ptr;
    Subject* sub_ptr;

};


#endif // ADMINISTRATION_H
