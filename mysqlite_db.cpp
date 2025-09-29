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
        QMessageBox::critical(nullptr, "Database Connection", this->db_connection.lastError().text());
    }else
    {
        QMessageBox::information(nullptr, "Database connection", "success");
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




int MySqlite_db::insert_student( QString& course,  QString& fullname,  QDate& birthdate,
                                 int& gender, QString& email,  QString& password, double& gpa) {
    if (!connect())
    {
        qDebug() << "Connection error: ";
        return 0;
    }
    static int id = -1;
    QString gdate = birthdate.toString("dd.mm.yyyy");
    QSqlQuery query;
    query.prepare("INSERT INTO student (student_id, course, fullname, birthdate, gender, email, password, gpa) "
                  "VALUES (null, :course, :fullname, :birthdate, :gender, :email, :password, :gpa)");
    query.bindValue(":course", course);
    query.bindValue(":fullname", fullname);
    query.bindValue(":birthdate", gdate);
    query.bindValue(":gender", gender);
    query.bindValue(":email", email);
    query.bindValue(":password", password);
    query.bindValue(":gpa", gpa);


    // execute request
    if(!query.exec())
    {
        qDebug() << "Excecution error: " << query.lastError();
        return 0;
    }
    query.prepare("select last_insert_rowid()");
    if(query.exec())
    {
        query.next();
        id = query.value(0).toInt();

    }else {
        qDebug() << "Adding student - retur id error: " << query.lastQuery();
        qDebug() << "Error: " << query.lastError();
    }

    return id;
}

int MySqlite_db::insert_subject(int& student_id,  QString& subject_name, int& weights, float& ects) {
    if (!connect()) return -1;
    static int id = -1;

    QSqlQuery query;
    query.prepare("INSERT INTO subject (subject_id, student_id, subject_name, weights, ects) "
                  "VALUES (null,:student_id,:subject_name,:weights,:ects)");
    query.bindValue(":student_id", student_id);
    query.bindValue(":subject_name", subject_name);
    query.bindValue(":weights", weights);
    query.bindValue(":ects", ects);

    if(query.exec())
    {
        query.prepare("select last_insert_rowid()");
        id = query.value(0).toInt();

    }else
    {
        qDebug() << "Add Subject Id error: " << query.lastError();
        qDebug() << "Last query before error occured: " << query.lastQuery();
    }


    return id;
}

QSqlQuery MySqlite_db::get_student_login(const QString email, const QString password)
{
    QSqlQuery query;
    query.prepare(
        "SELECT student_id, fullname, birthdate, gender, course, email, password, gpa"
        "FROM student where email=:email and password=:password");
    query.bindValue(":email", email);
    query.bindValue(":password", password);
    if(!query.exec())
    {
        qDebug() <<"Get student login details error:" << query.lastError();
        qDebug() << ", last error: " << query.lastError();
    }

    return query;

}

query MySqlite_db::get_students()
{
    if (!connect())
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
    if(!connect())
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

int MySqlite_db::insert_new_admin( QString& fullname,  QDate& birthdate,  QString& gender,  QString& email,  QString& password) {
    if (!connect())
        return -1;
    static int id = -1;


    QSqlQuery query;
    QString gdate = birthdate.toString("dd.mm.yyyy");
    query.prepare("INSERT INTO admin (admin_id,fullname, birthdate, gender, email, password) "
                  "VALUES (null,:fullname, :birthdate, :gender, :email, :password)");
    query.bindValue(":fullname", fullname);
    query.bindValue(":birthdate", gdate);
    query.bindValue(":gender", gender);
    query.bindValue(":email", email);
    query.bindValue(":password", password);
    if(!query.exec())
    {
        qDebug() << "Insert new admin error: " << query.lastError();
        return 0;
    }
    query.prepare("select last_insert_rowid()");
    if(query.exec())
        id = query.value(0).toInt();
    else
    {
        qDebug()<< "Inser Admin ID error: " << query.lastError()
                 << "Last query: " << query.lastQuery();
        return -1;
    }
    return id;

}

bool MySqlite_db::check_if_table_exist( QString& table_name) {
    if (!connect()) return false;

    QSqlQuery query("SELECT name FROM sqlite_master WHERE type='table' AND name=:table_name");
    query.bindValue(":table_name", table_name);
    if (query.exec() && query.next()) {
        return true;
    }
    return false;
}
