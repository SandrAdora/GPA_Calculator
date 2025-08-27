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
#include <vector>
#include <string>
#include <QMessageBox>

#include "student.h"


using str = QString;
using query = QSqlQuery;
using Db = QSqlDatabase;
using namespace std;

class MySqlite_db
{
public:


     MySqlite_db* get_instance();  // instance Method
    ~MySqlite_db();

     // dynamic Method to create the database table
    string build_create_table_sql(const vector<string>&);
    string create_tables(int ); // amount or rows the database table should have


    // Build Connection to existing database 
    void build_connection_database();
    bool check_status();

    // Operations
    bool insert_student( QString& ,QString&, QDate&, int&, QString&, QString&); // fullname, date, gender, email and password
    bool insert_subject(int&, QString&, int&, float&); // student id, name of the subject, weights of each subject and ects.

    Student* get_student(int&); // return the infos of a specific student
    bool delete_student(int&); // id
    void update_student(int&, QString&); // 2nd var. should be what chould be updated

    bool instert_new_admin(str&); // full name of a new admin

    query get_students() const;
    query get_student_info(int&, str&); // ID and what info should be retrieved
    query get_subjects() const;
    query get_student_subjects(int&, str&) const; // id and what info should be retrieved
    query get_admins() const;
    

    MySqlite_db(QString&);
private:
    static MySqlite_db* instance; // singleton, instance
    Db db_connection; // database connection
};

#endif // MYSQLITE_DB_H
