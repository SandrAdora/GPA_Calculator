#ifndef ADMIN_H
#define ADMIN_H

#include "person.h"
#include "mysqlite_db.h"
#include "administration.h"
#include <QString>

using str = QString;
class Admin : public Person
{
public:
    Admin();


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


    bool admin_(str); // checks if password correspond with the it password
private:
    int admin_id;
    str admin_password;
};

#endif // ADMIN_H
