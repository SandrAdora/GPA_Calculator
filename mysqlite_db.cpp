#include "mysqlite_db.h"
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>

MySqlite_db* MySqlite_db::instance = nullptr;

MySqlite_db* MySqlite_db::get_instance() {
    if (!instance) {
        instance = new MySqlite_db();
    }
    return instance;
}

MySqlite_db::MySqlite_db() {
    this->db_connection = QSqlDatabase::addDatabase("QSQLITE");
    this->db_connection.setDatabaseName(this->default_db_name);
    if (!this->db_connection.open()) {
        QMessageBox::critical(nullptr, "Database Error", this->db_connection.lastError().text());
    }
}

MySqlite_db::~MySqlite_db() {

    delete instance;
    instance = nullptr;
}

bool MySqlite_db::connect() {
    if (!this->db_connection.isOpen()) {
        return this->db_connection.open();
    }
    return true;
}

void MySqlite_db::disconnect() {
    if (this->db_connection.isOpen()) {
        this->db_connection.close();
    }
}


bool MySqlite_db::is_connected() {
    return this->db_connection.isValid() && this->db_connection.isOpen();
}

bool MySqlite_db::insert_student( QString& course,  QString& fullname,  QDate& birthdate,
                                 int& gender, QString& email,  QString& password, double& gpa) {
    if (!is_connected()) return false;

    QSqlQuery query;
    query.prepare("INSERT INTO student (course, fullname, birthdate, gender, email, password, gpa) "
                  "VALUES (:course, :fullname, :birthdate, :gender, :email, :password, :gpa)");
    query.bindValue(":course", course);
    query.bindValue(":fullname", fullname);
    query.bindValue(":birthdate", birthdate);
    query.bindValue(":gender", gender);
    query.bindValue(":email", email);
    query.bindValue(":password", password);
    query.bindValue(":gpa", gpa);

    return query.exec();
}

bool MySqlite_db::insert_subject(int& student_id,  QString& subject_name, int& weights, float& ects) {
    if (!is_connected()) return false;

    QSqlQuery query;
    query.prepare("INSERT INTO subject (student_id, subject_name, weights, ects) "
                  "VALUES (:student_id, :subject_name, :weights, :ects)");
    query.bindValue(":student_id", student_id);
    query.bindValue(":subject_name", subject_name);
    query.bindValue(":weights", weights);
    query.bindValue(":ects", ects);

    return query.exec();
}

query MySqlite_db::get_students()
{
    if (!is_connected())
    {
        QMessageBox::warning(nullptr, "Database connection", "Failure..");
        return QSqlQuery();

    }
    QSqlQuery q;

    if(!q.exec("Select * from students Order By (fullname)")){

        QMessageBox::warning(nullptr, "Query", "Last query error");
        qDebug() << q.lastError();
    }
    return q;
}

query MySqlite_db::get_student_info(int &id, str &choice)
{
    if(!is_connected())
    {
        QMessageBox::warning(nullptr, "Student infos", "fail");
        return QSqlQuery(); // returning an empty query
    }
    if(choice == "all subjects"){
        // so something

    }else if(choice == "gpa")
    {
        // do something

    }
    else if(choice == "sll infos")
    {
        // do something
    }

}

bool MySqlite_db::insert_new_admin( QString& fullname,  QDate& birthdate,
                                    QString& gender,  QString& email,  QString& password) {
    if (!is_connected()) return false;

    QSqlQuery query;
    query.prepare("INSERT INTO admin (fullname, birthdate, gender, email, password) "
                  "VALUES (:fullname, :birthdate, :gender, :email, :password)");
    query.bindValue(":fullname", fullname);
    query.bindValue(":birthdate", birthdate);
    query.bindValue(":gender", gender);
    query.bindValue(":email", email);
    query.bindValue(":password", password);

    return query.exec();
}

bool MySqlite_db::check_if_table_exist( QString& table_name) {
    if (!is_connected()) return false;

    QSqlQuery query("SELECT name FROM sqlite_master WHERE type='table' AND name=:table_name");
    query.bindValue(":table_name", table_name);
    if (query.exec() && query.next()) {
        return true;
    }
    return false;
}
