#ifndef MYSQLITE_DB_H
#define MYSQLITE_DB_H

#include <QString>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <exception>
#include <iostream>
#include <qsqlquery.h>

#include "student.h"


using str = QString;
using sql = QSqlQuery;
using Db = QSqlDatabase;

class MySqlite_db
{
public:


     MySqlite_db* get_instance();  // instance Method
    ~MySqlite_db();

     // Method to create the database
    void create_student_table();
    void create_subject_table();


    // Build Connection to existing database 
    void build_connection_database();
    bool check_status(); 

    // Operations 
    bool insert_student(QString&, QDate&, int&, QString&, QString&); // fullname, date, gender, email and password
    sql get_student_infos(int); // return the infos of a specific student
    bool delete_student(int); // id
    book update_student(int, QString); // id and 2nd var. should be what chould be updated
    bool insert_subject(str, int, float); // name of the subject, weights of each subject and ects.
    bool instert_new_admin(str&); // full name of a new admin

    sql get_students() const;
    sql get_student(int&);
    sql get_subjects() const;
    sql get_student_subjects() const;
    sql get_admins() const;
    sql get_subject_infos(int&) const;



protected:
    MySqlite_db();
private:
    static MySqlite_db* instance; // singleton, instance
    Db db_connection; // database connection
};

#endif // MYSQLITE_DB_H
