#ifndef MYSQLITE_DB_H
#define MYSQLITE_DB_H

#include <QString>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <qsqlquery.h>
#include <vector>
#include <string>
#include <QMessageBox>
#include <cstdarg>
#include <QVariantList>
#include <iostream>
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
     MySqlite_db(QString&, QString = ""); // constructor with names for creating new database or inserting into existing one in another table
     MySqlite_db(); // default constructor

     // dynamic Method to create the database table
    string build_create_table_sql(const vector<string>&);
    string create_tables(int ); // amount or rows the database table should have
    bool build_table(QStringList&, str&, str = ""); // list of sql statements & name of the table and references if available
    bool check_if_table_exist(str&); // searches for table existance


    // Build Connection to existing database
    void disconnect();
    bool connect();

    // Operations
    int insert_student( QString& ,QString&, QDate&, int&, QString&, QString&, double&); // fullname, date, gender, email and password...--> if more args needed

    int insert_subject(int&, QString&, int&, float&); // student id, name of the subject, weights of each subject and ects,
    QSqlQuery get_student(int&); // return the infos of a specific student
    QSqlQuery get_student_login(const QString, const QString);

    bool delete_student(int&); // id
    bool delete_subject(int&); // sub. id
    bool delete_admin(int&); // admin id
    bool update_student_gpa(const int&, const float) ; // student id, new gpa
    bool update_student_name(const int&, const QString&); // student id, new student name
    bool update_student_email(const int&, const QString&); // student id, new email
    bool update_student_password(const int&, const QString&); // student id, new password
    bool update_subject_name(const int&, const QString&); // subject id, new subject name
    bool update_subject_ect(const int&, const float&); // subject id, new ects
    bool update_subject_weights(const int&, const int&); // subject id, new weights

    bool update_admin_name(const int&, const QString&); // admin id, new admin name
    bool update_admin_email(const int&, const QString&); // admin id, new  admin email
    bool update_admin_password(const int&, const QString&); // admin id, new admin password

    int insert_new_admin(str&, QDate&, str&, str&, str&); // full name of a new admin, date , gender, email and password

    int& get_sudent_id(const QString& ); // student name
    int& get_subject_id(const QString& ); // subject name
    int& get_admin_id(const QString& ); // admin's name

    query get_students() ;
    query get_student_info(int&, str&); // ID and what info should be retrieved
    query get_subjects() const;
    query get_student_subjects(int&, str&) ; // id and what info should be retrieved
    query get_admins() ;

     bool create_db(QString&); // name of database to create
     void set_db_name(QString&); 
    


private:
    static MySqlite_db* instance; // singleton, instance
    Db db_connection; // database connection
    QString default_db; // available database driver default is sqlite
    QString default_db_name = "gpa_student"; // name of the database table
    QString database_path = "C:/Database/database";
};

#endif // MYSQLITE_DB_H
