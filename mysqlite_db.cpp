#include "mysqlite_db.h"
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <filesystem>

#define DB_FILEPATH "C:/Users/sandr/Documents/GitHub/Qt_Projects/GPA_Calculator/database/"

MySqlite_db* MySqlite_db::instance = nullptr;

MySqlite_db* MySqlite_db::get_instance() {
    if (instance == nullptr) {
        instance = new MySqlite_db();
    }
    return instance;
}

MySqlite_db::MySqlite_db() {
    this->db_connection = QSqlDatabase::addDatabase("QSQLITE");
    this->default_db_name = "db_gpa";

    this->db_connection.setDatabaseName(DB_FILEPATH + default_db_name + ".db");

    // check if file exists
    if(QFile::exists(DB_FILEPATH + this->default_db_name + ".db")){

        qDebug() << "File exists, check connection to the database";
        if (!db_connection.open()) {
            QMessageBox::critical(nullptr, "Database Connection", db_connection.lastError().text());
            return;
        }

    }else{
        QMessageBox::warning(nullptr, "File Status:", "Error message: File does not exist") ;
        return;
    }
    QSqlQuery query;
    query = QSqlQuery(db_connection);

}

MySqlite_db::~MySqlite_db() {

    delete instance;
    instance = nullptr;
}

bool MySqlite_db::connect() {
    if (!this->db_connection.open()) {
        return false ;
    }
    return true;
}

void MySqlite_db::disconnect() {
    if (this->db_connection.open()) {
        this->db_connection.close();
    }
}

int MySqlite_db::insert_student( QString& course,  QString& fullname,  QDate& birthdate,
                                 QString& gender, QString& email,  QString& password, QString& gpa) {

    static int id = -1;


    // check if file exists
    if(QFile::exists(DATABASE)){

        qDebug() << "File exists, check connection to the database";
        if (!db_connection.open()) {
            QMessageBox::critical(nullptr, "Database Connection", db_connection.lastError().text());
            qDebug() << "Error: " << db_connection.lastError();
            return -1;
        }

    }else{
        QMessageBox::warning(nullptr, "File Status:", "Error message: File does not exist") ;
        return -1;
    }
    QSqlQuery query;
    query = QSqlQuery(this->db_connection);
    QString b_date = birthdate.toString();
    query.prepare("INSERT INTO students(course,fullname, birthdate, gender, email, password, currentGpa ) VALUES('" + course + "','" + fullname + "','" + b_date +"','" + email + "','" + password + "','" + gender + "', '" + gpa+ "' )");

    query.prepare("select last_insert_rowid()");
    if(query.exec())
    {
        query.next();
        id = query.value(0).toInt();

    }else {
        qDebug() << "Adding student - return id error: " << query.lastQuery();
        qDebug() << "Error: " << query.lastError().text();
    }

    return id;
}

int MySqlite_db::insert_subject(int& student_id,  QString& subject_name, int& weights, float& ects) {
    if (!connect()) return -1;
    static int id = -1;

    QSqlQuery query;
    query.prepare("INSERT INTO subjects (subject_id, student_id, subject_name, weights, ects) "
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
    else if(choice == "all infos")
    {
        // do something
    }

}
void MySqlite_db::set_db_name(QString& name)
{
    if(this->default_db_name.isLower() == name.isLower())
    {
        qDebug() << "Database name are the same";
        return;

    }
    this->default_db_name = name;
    
}
auto filesystemToQstringPath(const fs::path& fs_path)
{
     std::string st_path =fs_path.u8string();
      return QString::fromStdString(st_path);

}

// convert string path to file system
auto MySqlite_db::toFilesystemPath(QString& txt)
{

    const fs::path fs_path{txt.toStdString()};
    if(!fs::exists(fs_path))
    {
        // create path
        fs::create_directory(fs_path);
    }
    return fs_path;
}

// search path
auto search_path(const fs::path& p) {
    if ( fs::exists(p))
        return true;

    else
            return false;
}
// set database path
void MySqlite_db::set_db_path(QString& path)
{
    // check if path already exists
    if(this->database_path == path)
    {
        qDebug() << "Path exists already";
        return;
    }
    fs::path p = toFilesystemPath(path);
    this->database_path = filesystemToQstringPath(p);
}

// get db default name
QString MySqlite_db::get_default_db_name() const
{
    return this->default_db_name;

}

// Get databas path
QString MySqlite_db::get_database_path() const
{
    return this->database_path;

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
