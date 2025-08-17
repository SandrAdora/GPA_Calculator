#ifndef ADMIN_H
#define ADMIN_H

#include "person.h"



#include <QString>

using str = QString;
class Admin : public Person
{
public:
    Admin();
    // methods from super class
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


    // Getter methods
    str get_it_admin_password() const;
    int get_admin_id() const;
    bool admin_(str); // checks if password correspond with the IT password

protected:
    int admin_id;
    str admin_password; // IT password which is already fix
};

#endif // ADMIN_H
