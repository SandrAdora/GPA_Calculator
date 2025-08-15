#ifndef ADMINISTRATION_H
#define ADMINISTRATION_H
#include <iostream>
#include <vector>
#include <QString>
#include <QDate>

#include "student.h"
#include "subject.h"


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




// factory method class
class Administration : public Student
{
public:
    static Administration* Instance();


    Person* FactoryMethod(){ // Factory method as an interface for person and student

        if (type == MethodType::student){
            return new Student();
        }else if(type == MethodType::subject){
            return new Subject();
        }
        return nullptr;//other methodtype can be subsequently added if necessary
    }
    auto* create_object(MethodType& );

    void add_student(QString &, QDate &, QString&, QString&, QString&);
    void add_new_subjects(QString&, int&, double&); // name of subject, ects and weights of each subjects
    bool delete_subject(int&);
    void view_all_subjects() const;
    bool delete_student(int &);
    void display_all_Students() const;
    bool update_student_name(int&, QString);

    bool update_subject_ect(int&, int);
    bool update_subject_name(int&, QString&);
    bool update_subject_weights(int& ,double);

protected:
    Administration();





private:
    std::vector<Student*>students;
    MethodType type;
    std::vector<Subject*> subjects;
    Student* ptr;
    Subject* sub_ptr;
    static Administration* _instance;

};


#endif // ADMINISTRATION_H
