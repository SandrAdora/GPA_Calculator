#include "student.h"



Student::Student() {

    this->fullname = "";
    this->email = "school@example.com";
    this->password = "xxxxxx";
    this->gender = Gender::DONT_DISCLOSE;
    this->birthdate = QDate(1990, 3, 13);
    this->student_id = -1;
    this->course = Courses::Artificial_Intelligence;

}
Student::Student(int id, QString name, QDate dat, Gender gen, QString em, QString pw, Courses cs){
    this->fullname = name;
    this->email = em;
    this->gender = gen;
    this->birthdate = dat;
    this->student_id = id;
    this->course = cs;
    this->student_id = id;

}
Student::Student(Courses cs, QString name, QDate d, Gender g, QString em, QString pw){
    this->fullname = name;
    this->email = em;
    this->course = cs;
    this->birthdate = d;
    this->gender = g;
    this->password = pw;

}
Student::Student( QString name, QDate d, Gender g, QString em, QString pw){
    this->fullname = name;
    this->email = em;
    this->course = Courses::Artificial_Intelligence; // default choice
    this->birthdate = d;
    this->gender = g;
    this->password = pw;

}


void Student::set_course(Courses cs){
    this->course = cs;

}
int Student::get_id() const {
    return this->student_id;
}

