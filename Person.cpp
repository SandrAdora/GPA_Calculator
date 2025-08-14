#include "person.h"

Person::Person(){
    this->fullname = "";
    this->email = "school@example.com";
    this->password = "xxxxxx";
    this->gender = Gender::DONT_DISCLOSE;
    this->birthdate = QDate(1990, 3, 13);

}
Person::Person(QString em, QString pw){
    this->email = em;
    this->password = pw;
}
Person::Person(QString name, QDate d, Gender g, QString em, QString pw){
    this->fullname = name;
    this->email = em;
    this->birthdate = d;
    this->gender = g;
    this->password = pw;
}
