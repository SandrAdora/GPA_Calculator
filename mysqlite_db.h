#ifndef MYSQLITE_DB_H
#define MYSQLITE_DB_H

#include <QString>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include "administration.h"


using str = QString;

class MySqlite_db
{
public:
    MySqlite_db();

     MySqlite_db* get_instance();  // instance Method

     // Method to create the database
    void create_student_table();
    void create_subject_table();

    // funtions
    
    bool insert_student(QString&, QDate&, int&, QString&, QString&); // fullname, date, gender, email and password
    Student* get_student(int); // return the infos of a specific student
    bool delete_student(int); // id
    void update_student(int, QString); // 2nd var. should be what chould be updated
    bool insert_subject(str, int, float); // name of the subject, weights of each subject and ects.





private:
    MySqlite_db* instance; // singleton, instance
    QSqlDatabase db_connection; // database connection
};

#endif // MYSQLITE_DB_H
