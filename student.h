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


};

class Student : public Person
{
public:
    Student();
    Student(int, QString, QDate, Gender, QString, QString, Courses);
    Student(Courses, QString, QDate, Gender, QString, QString);
    Student(QString, QDate, Gender, QString, QString);


    void set_course(Courses);
    Courses get_course(QString);
    int get_id()const;
    /// Helper function Converting types str and int
    QString convertToString(Gender gen){

        if (gen == Gender::FEAMALE){
            return "female";
        }else if (gen == Gender::MALE){
            return "male";
        }else if(gen == Gender::DONT_DISCLOSE){
            return "dont disclose";
        }
        return ""; // return empty string if no input match
    }
    Gender convertStringToInt(QString& gen){
        if(gen == "male")
            return Gender::MALE;
        else if(gen == "female")
            return Gender::FEAMALE;
        else
            return Gender::DONT_DISCLOSE;
        return Gender::NOTHING;
    }

    // Redefination of methods from the super class
    void set_fullname(QString name) override { this->fullname = name;}
    void set_birthdate(QDate date) override {this->birthdate = date; }
    void set_password(QString pw) override {this->password = pw;}
    void set_email(QString em) override{this->email = em;}
    void set_gender(QString gen) override {this->gender= convertStringToInt(gen);}
    QString get_fullname() const override {return this->fullname;}
    QString get_email() const override{return this->email;}
    QString get_password() const override {return this->password;}
    QDate get_birthdate() const override{return this->birthdate;}
    Gender get_gender() const override {return this->gender;}


protected:
    int student_id;
    int course;

};

#endif // STUDENT_H
