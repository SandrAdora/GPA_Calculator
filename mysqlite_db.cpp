#include "mysqlite_db.h"
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <filesystem>


// --- Singleton
MySqlite_db* MySqlite_db::instance = nullptr;




// -- Establish database connection
MySqlite_db::MySqlite_db() {

    // --- check if file exists
    if(QFile::exists(this->database_path + this->default_db_name + ".db")){
        qDebug() << "File exists, stabilizing connection to the database";
        this->connect();

    }else{
        QMessageBox::warning(nullptr, "File Status:", "Error message: File does not exist") ;
        return;
    }
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


// --- This fuction connect the datatabse with the presistance layer
void MySqlite_db::connect() {
    qDebug() << "Connecting....";
    this->db_connection = QSqlDatabase::addDatabase(this->default_db_driver);
    this->db_connection.setDatabaseName(this->database_path + default_db_name + ".db");
    qDebug() << "Connection name:" <<this->db_connection.connectionName()
             << "Driver name: " << this->db_connection.driverName();
    if(this->db_connection.open())
        qDebug() << "Database is open: ";
    else
    {
        qDebug() << "Database is still closed. Error message: " << this->db_connection.lastError().text();
    }

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
int MySqlite_db::insert_student( QString& course,  QString& fullname,  QDate& birthdate,
                                 QString& gender, QString& email,  QString& password, QString& gpa) {
    // check if file exists
    if(!this->status()){
        QMessageBox::warning(nullptr, "Database Status:", "Error message: Database does not exist or couldn't be found") ;
        return -1;
    }
    static int id = -1;
    QSqlDatabase db_conection = QSqlDatabase::addDatabase("SQLITE");
    db_conection.setDatabaseName("C:/Users/sandr/Documents/GitHub/Qt_Projects/GPA_Calculator/database/db_gpa.db");

    QSqlQuery query(db_connection);
    QString b_date = birthdate.toString();
    query.prepare("INSERT INTO students(course,fullname, birthdate, gender, email, password, currentGpa )"
                  "VALUES('" + course + "','" + fullname +"','" + b_date +"','" + email + "','" + password + "','" + gender + "', '" + gpa + "' )");
    if(!query.exec())
    {
        qDebug() << "Adding student - return id error: " << query.lastQuery();
        qDebug() << "Error: " << query.lastError().text();
    }
    while(query.next())
        id = query.value(0).toInt(); /// return the id of the student
    return id;
}


/// ---- Insert subjects -------
int MySqlite_db::insert_subject(int& student_id,  QString& subject_name, int& weights, float& ects) {
    if (!status()) return -1;


    this->db_connection = QSqlDatabase::addDatabase(this->default_db_driver);
    this->db_connection.setDatabaseName(DB_FILEPATH);


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


    if(!QFile::exists(DB_FILEPATH)) return QSqlQuery();

    this->db_connection = QSqlDatabase::addDatabase(this->default_db_driver);
    db_connection.setDatabaseName(DB_FILEPATH);

    QSqlQuery q(db_connection);
    q.prepare("DELETE course, fullname, birthdate, gender, email, password WHERE :id=id");
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
    if(!this->status())
        QMessageBox::warning(nullptr, "Database Status",  "db_connection Error()");
    this->db_connection = QSqlDatabase::addDatabase("QSQLITE");
    this->db_connection.setDatabaseName(DB_FILEPATH);
    QSqlQuery query(this->db_connection);

    query.prepare(
        "SELECT ID, course, fullname, birthdate, gender, email, password, currentGpa"
        "FROM students Where email=:email and password=:password VALUES('" + email + "'," + password + "')");

    if(!query.exec())
    {
        qDebug() <<"Get student login details error:" << query.lastError();
        qDebug() << ", last error: " << query.lastError();
    }

    return query;

}

query MySqlite_db::get_students()
{
    if (!status())
    {
        QMessageBox::warning(nullptr, "Database connection", "Failure..");
        return QSqlQuery();

    }
    QSqlQuery q =  QSqlQuery(this->db_connection);
    q.prepare("SELECT * FROM students");
    q.exec();



    return q;
}

query MySqlite_db::get_student_info(int &id, str &choice)
{
    if(!status())
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

bool MySqlite_db::email_exists(QString &em, QString& table)
{


    this->db_connection = QSqlDatabase::addDatabase("QSQLITE");
    this->db_connection.setDatabaseName(DB_FILEPATH);
    QSqlQuery q(this->db_connection);
    q.prepare("SELECT email FROM '" + table +"' WHERE :email=em");
    q.bindValue(":email", em);
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
    if (!status())
        return -1;
    static int id = -1;


    this->db_connection = QSqlDatabase::addDatabase("QSQLITE");
    this->db_connection.setDatabaseName(DB_FILEPATH);
    QSqlQuery query(this->db_connection);
    QString gdate = birthdate.toString("dd.mm.yyyy");
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
    if (!status()) return false;
    this->db_connection = QSqlDatabase::addDatabase("QSQLITE");
    this->db_connection.setDatabaseName(DB_FILEPATH);

    QSqlQuery query(this->db_connection);
        query.prepare("SELECT name FROM sqlite_master WHERE type='table' AND name=:table_name");
    query.bindValue(":table_name", table_name);
    if (query.exec() && query.next()) {
        return true;
    }
    return false;
}
