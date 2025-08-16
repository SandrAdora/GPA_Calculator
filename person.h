#ifndef PERSON_H
#define PERSON_H



// Include libs
#include <QString>
#include <QDate>

enum Gender{

    MALE, FEAMALE, DONT_DISCLOSE, NOTHING
};

// Factory method
class Person{ // Super class

public:
    // Constructors
    Person();
    Person(QString em, QString pw);
    Person(QString, QDate, Gender, QString, QString);

    QString convertToString(Gender gen);
    Gender convertStringToInt(QString& gen);



    // Getter & Setter Methods
    virtual void set_fullname(QString) = 0;
    virtual void set_birthdate(QDate) = 0;
    virtual void set_email(QString) = 0;
    virtual void set_password(QString) = 0;
    virtual void set_gender(QString)  = 0; // Will need a helper function to convert string to int

    virtual QString get_fullname() const  = 0;
    virtual QString get_email()  const  = 0;
    virtual QString get_password() const  = 0;
    virtual QDate get_birthdate() const  = 0;
    virtual  Gender get_gender() const = 0;

protected:

    QString fullname;
    QDate birthdate;
    Gender gender;
    QString email;
    QString password;

};
#endif // PERSON_H
