#ifndef STUDENT_H
#define STUDENT_H

#include "person.h"

#include <QString>
#include <QDate>


// Available courses
enum Courses{

    Mathematics
    , Informatics
    , Medical_Informatics
    , Technical_Informatics
    , Business_Informatics
    , Human_Medicine
    , Vet_Medicine // vet doctor
    , Engineering
    , Data_Science
    , Artificial_Intelligence
    , Biomedical_Engineering
    , Medical_Engineering
    , Electronical_Engineering
    , Architect
    , Administrator


};

class Student : public Person
{
public:
    Student();
    Student(int, QString, QDate, Gender, QString, QString, Courses);
    Student(Courses, QString, QDate, Gender, QString, QString);
    Student(QString, QDate, Gender, QString, QString);


    void set_course(Courses);
    QString get_course_str() const;
    Courses get_course_cour(QString& major) ;
    int get_id()const;


    // Redefination of methods from the super class
    void set_fullname(QString name) override { fullname = name;}
    void set_birthdate(QDate date) override {birthdate = date; }
    void set_password(QString pw) override {password = pw;}
    void set_email(QString em) override{email = em;}
    void set_gender(QString gen) override {gender= convertStringToInt(gen);}
    QString get_fullname() const override {return fullname;}
    QString get_email() const override{return email;}
    QString get_password() const override {return password;}
    QDate get_birthdate() const override{return birthdate;}
    Gender get_gender() const override {return gender;}


protected:
    int student_id;
    int course;

};

#endif // STUDENT_H
