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
QString Person::convertToString(Gender gen){

    if (gen == Gender::FEAMALE){
        return "female";
    }else if (gen == Gender::MALE){
        return "male";
    }else if(gen == Gender::DONT_DISCLOSE){
        return "dont disclose";
    }
    return ""; // return empty string if no input match
}
Gender Person::convertStringToInt(QString& gen){
    if(gen == "male")
        return Gender::MALE;
    else if(gen == "female")
        return Gender::FEAMALE;
    else
        return Gender::DONT_DISCLOSE;
    return Gender::NOTHING;
}
