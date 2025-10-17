#include "mysqlite_db.h"
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <filesystem>


// --- Singleton
MySqlite_db* MySqlite_db::instance = nullptr;




// -- Establish database connection
MySqlite_db::MySqlite_db() {

    qDebug() << "Connecting....";
    this->db_connection = QSqlDatabase::addDatabase("QSQLITE");
    this->db_connection.setDatabaseName(this->database_path);
    qDebug() << "Connection name:" <<this->db_connection.connectionName()
             << "Driver name: " << this->db_connection.driverName();
    if(!db_connection.open())
        QMessageBox::warning(nullptr, "Database connection", " failed...");
    else
        QMessageBox::information(nullptr, "Database connection", "success...");



}

// --- This instance communicates with the business layer
MySqlite_db *MySqlite_db::get_instance()
{
    if(this->instance == nullptr)
        this->instance = new MySqlite_db();

    return this->instance;
}

MySqlite_db::~MySqlite_db() {

    delete instance;
    instance = nullptr;
}


// -- Checks status of database

bool MySqlite_db::status()
{
    if(this->db_connection.isValid() || db_connection.isOpen())
        return true;
    QMessageBox::warning(nullptr, "Database Status", "no Connection established");
    qDebug() << "Error: " << db_connection.lastError();
    return false;


}

// --- Disconnection
void MySqlite_db::disconnect() {
    if (this->db_connection.open()) {
        this->db_connection.close();
    }
}



/// ----------------------------------- GPA Student functionality ---------------------
///
/// -- insert students
int MySqlite_db::insert_student(QString& course, QString& fullname, QDate& birthdate,
                                QString& gender, QString& email, QString& password, QString& gpa) {
    QSqlQuery query(this->db_connection);

    // Format birthdate safely
    QString b_date = birthdate.toString("yyyy-MM-dd");

    // Prepare statement with placeholders
    query.prepare("INSERT INTO students(course, fullname, birthdate, gender, email, password, currentGpa) "
                  "VALUES(:course, :fullname, :birthdate, :gender, :email, :password, :gpa)");

    // Bind values
    query.bindValue(":course", course);
    query.bindValue(":fullname", fullname);
    query.bindValue(":birthdate", b_date);
    query.bindValue(":gender", gender);
    query.bindValue(":email", email);
    query.bindValue(":password", password);
    query.bindValue(":gpa", gpa);

    // Execute and handle errors
    if (!query.exec()) {
        qDebug() << "Insert student error:" << query.lastError().text();
        return -1;
    }

    // Retrieve last inserted ID
    QSqlQuery idQuery(this->db_connection);
    if (idQuery.exec("SELECT last_insert_rowid()") && idQuery.next()) {
        return idQuery.value(0).toInt();
    } else {
        qDebug() << "Failed to retrieve student ID:" << idQuery.lastError().text();
        return -1;
    }
}



/// ---- Insert subjects -------
int MySqlite_db::insert_subject(int& student_id,  QString& subject_name, int& weights, float& ects) {

    QSqlQuery query(this->db_connection);

    query.prepare(" INSERT INTO subjects( student_id,subject_name, subject_weights, subject_ects) VALUES( '" + QString::number(student_id) + "','" + subject_name +"','" + QString::number(weights) + "','" + QString::number(ects) + "')");


    if(!query.exec())
    {
        qDebug() << "Add Subject Id error: " << query.lastError();
        qDebug() << "Last query before error occured: " << query.lastQuery();

    }
    return 1;
}


/// Get specific student
/// @arg: ID as an int var
/// @returns query of requested student

QSqlQuery MySqlite_db::get_student(int &id)
{
    if(id < 1)
        QMessageBox::warning(nullptr, "ID Status", "Invalid id...try again");


    if(!QFile::exists(database_path))
        QMessageBox::warning(nullptr, "File Status", "does not exist");


    QSqlQuery q(this->db_connection);
    q.prepare("SELECT ID, course, fullname, birthdate, gender, email, password, currentGpa FROM students WHERE id=:id ");
    q.bindValue(":id",id);
    if(!q.exec())
    {
        QMessageBox::warning(nullptr, "Delete status", "Student could not be deleted..");
        qDebug() << "Error deleting student: " << q.lastError().text() << "Last Query was:"  << q.lastQuery();
    }
    return q;
}

QSqlQuery MySqlite_db::get_student_login(const QString email, const QString password)
{
    QSqlQuery query(this->db_connection);
    query.prepare("select ID, course, fullname, birthdate, gender, email, currentGpa from students where email=:email and password=:password");
    query.bindValue(":email", email);
    query.bindValue(":password", password);

    if(!query.exec())
    {
        qDebug() << "Error exection error: "<< query.lastError().text() << "Error last query: " << query.lastQuery();

    }
    return query;
}

QSqlQuery MySqlite_db::signIn_admin(const QString &em, const QString &pw)
{
    // search if email exists
    QSqlQuery q(this->db_connection);
    q.prepare("select ID, fullname, birthdate, gender, email from admins where email=:em and password=:pw");
    q.bindValue(":em", em);
    q.bindValue(":pw", pw);
    if(!q.exec())
    {
        QMessageBox::warning(nullptr, "Sign In admin status", "failed");
    }

    return q;
}

bool MySqlite_db::delete_student(int &id)
{
    QSqlQuery q;
    q.prepare("delete from students where id=:id");
    q.bindValue(":id", id);
    if(!q.exec())
        return false;
    return true;

}

bool MySqlite_db::delete_subject(int &id)
{
    if(id < 0)
    {
        QMessageBox::warning(nullptr, "Delete Subject status", "Failed....reason: Negative ID");
        return false;
    }
    QSqlQuery q(this->db_connection);
    q.prepare("DELETE FROM subjects WHERE ID=:id");
    q.bindValue(":id", id);
    if(q.exec())
    {
        QMessageBox::information(nullptr, "Delete Subject status", "success");
        return true;
    }
    return false;

}

query MySqlite_db::get_students()
{

    QSqlQuery q;
    q.prepare("SELECT ID, course, fullname, birthdate, gender, email, currentGpa  FROM students");
    if(!q.exec())
    {
        QMessageBox::warning(nullptr, "Get all Students error", q.lastError().text());
        qDebug()  << "Last query: " << q.lastQuery();

    }
    return q;
}

query MySqlite_db::get_student_info(int &id, str &choice)
{

    QSqlQuery q(this->db_connection);


    if(choice == "only subjects"){
        // so something
        q.prepare("select student_id, subject_name, subject_weights, subject_ects from subjects where student_id=:id");
        q.bindValue(":id", id);
        if(!q.exec())
            QMessageBox::warning(nullptr,q.lastError().text(), q.lastQuery());

    }
    else if(choice == "all infos")
    {
        // do something
        q.prepare("select s.ID, s.course, s.fullname, s.birthdate,s.gender,s.email, s.password,s.currentGpa From students s, subjects sub where s.ID=sub.student_id and sub.student_id=:id");
        q.bindValue(":id", id);
        if(!q.exec())
            QMessageBox::warning(nullptr, "Student Info error", q.lastError().text());
    }

    return q;

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

bool MySqlite_db::email_exists(QString &em, QString& table)
{
    QSqlQuery q;
    q.prepare("SELECT email FROM '" + table +"' WHERE email=:em");
    q.bindValue(":em", em);
    if(q.exec())
        return true;
    return false;

}

// search path
auto search_path(const fs::path& p) {
    if ( fs::exists(p))
        return true;

    else
        return false;
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


    QSqlQuery query(this->db_connection);
    QString gdate = birthdate.toString("yyyy-MM-dd");
    query.prepare("INSERT INTO admins (fullname, birthdate, gender, email, password) "
                "VALUES (:fullname, :birthdate, :gender, :email, :password)");
    query.bindValue(":fullname", fullname);
    query.bindValue(":birthdate", gdate);
    query.bindValue(":gender", gender);
    query.bindValue(":email", email);
    query.bindValue(":password", password);
    if(!query.exec())
    {
        qDebug() << "Insert new admin error: " << query.lastError();
        return -1;
    }
    QSqlQuery idquery(this->db_connection);

    if(idquery.exec("SELECT last_insert_rowid()") && idquery.next())
        return idquery.value(0).toInt();
    else
    {
        qDebug()<< "Insert Admin ID error: " << idquery.lastError()
                << "Last query: " << idquery.lastQuery();
        return -1;
    }


}

bool MySqlite_db::check_if_table_exist( QString& table_name) {
    if (!status()) return false;
    this->db_connection = QSqlDatabase::addDatabase("QSQLITE");
    this->db_connection.setDatabaseName(this->database_path);

    QSqlQuery query(this->db_connection);
        query.prepare("SELECT name FROM sqlite_master WHERE type='table' AND name=:table_name");
    query.bindValue(":table_name", table_name);
    if (query.exec() && query.next()) {
        return true;
    }
    return false;
}
