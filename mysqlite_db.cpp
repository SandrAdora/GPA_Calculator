#include "mysqlite_db.h"
#include <QFile>
#include <QMessageBox>

MySqlite_db* MySqlite_db::instance = nullptr;

MySqlite_db* MySqlite_db::get_instance() {
    if(this->instance == nullptr){
        try {
            instance = new MySqlite_db();

        }catch(std::bad_alloc& exception){
            std::cerr << "Bad Alloc detected: " << exception.what();

        }
    }
    return this->instance;
}
MySqlite_db::~MySqlite_db(){
    if(instance != nullptr){
        delete instance;
        instance = nullptr;
    }
}

// Dynamically creating sql statements for creating tables
std::string MySqlite_db::build_create_table_sql(const std::vector<std::string>& schema) {
    if (schema.size() < 3 || schema.size() % 2 == 1) return "";

    std::string table_name = schema[0];
    std::string sql = "CREATE TABLE " + table_name + " (\n";
    std::vector<std::string> foreign_keys;

    for (size_t i = 1; i < schema.size(); i += 2) {
        std::string col_name = schema[i];
        std::string col_type = schema[i + 1];

        std::string col_def = "    " + col_name + " " + col_type;

        // Check for optional key specifier
        if (i + 2 < schema.size()) {
            std::string key_spec = schema[i + 2];
            if (key_spec == "primary key") {
                col_def += " PRIMARY KEY AUTOINCREMENT";
                i++; // Skip key spec
            } else if (key_spec == "foreign key") {
                // Collect foreign key separately
                foreign_keys.push_back("    FOREIGN KEY (" + col_name + ") REFERENCES other_table(other_column)");
                i++; // Skip key spec
            }
        }

        sql += col_def + ",\n";
    }

    // Append foreign keys
    for (const auto& fk : foreign_keys) {
        sql += fk + ",\n";
    }

    // Remove trailing comma and newline
    if (sql.size() >= 2) {
        sql.pop_back();
        sql.pop_back();
    }

    sql += "\n);";
    return sql;
}

string MySqlite_db::create_tables(int rows)
{
    string row_name{""};
    string table_name {""};
    string var_type{""};

    vector<string> table_schema_parts;

    //Keywords

    string primary_key = "primary key AUTOINCREMENT";
    string foreign_key = "foreign key";


    // Beginn of user Input
    cout << "Enter table name: ";
    getline(std::cin, table_name);
    table_schema_parts.push_back(table_name);


    for (int i= 0; i < rows; i++)
    {
        string prim_key_ = "";
        string forg_key_ = "";
        std::cout << "Enter row name: ";
        std::cin >> row_name;

        cout << "\nEnter row type (eg. integer, varchar(10))s or text: ";
        getline(cin, var_type);
        table_schema_parts.push_back(row_name);
        table_schema_parts.push_back(var_type);
        cout <<"\n Should "<< row_name << " be a primary key? yes [y] or no [n]: ";
        getline(std::cin, prim_key_);

        if (prim_key_ == "y" || prim_key_ == "yes")
        {

            table_schema_parts.push_back(primary_key);


        }else if(prim_key_ == "n" || prim_key_ == "no")
        {

            cout << "\nShould" << row_name<<" be a foreign key instead?: yes[y] or no[n] ";
            getline(std::cin, forg_key_) ;
            if(forg_key_ == "y" || forg_key_ == "yes")
            {
                table_schema_parts.push_back(foreign_key);
            }

        }

    }
    return build_create_table_sql(table_schema_parts);
}

bool MySqlite_db::build_table(QStringList & sql_str, str& name_of_table, str reference)
{
    this->default_db_name = name_of_table;
    str sql = "CREATE TABLE " + this->default_db_name + " (\n";
    for (const str& line : sql_str)
        sql += " " + line + ",\n";

    sql.chop(2); // removing last comma and newline
    sql += "\n)";

    QSqlQuery q;
    q.prepare(sql);
    if(!q.exec())
    {
        qDebug() << "SQL Error:" << q.lastError().text();
        return false;
    }


    return true;
}

MySqlite_db::MySqlite_db()

{

    this->default_db = "QSQLITE";
    this->default_db_name = "gpa_calculator.db";
    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        QSqlDatabase::removeDatabase("qt_sql_default_connection");
    }
    this->db_connection = QSqlDatabase::addDatabase(this->default_db);
    this->db_connection.setDatabaseName(this->default_db_name);
    this->db_connection.open();

}

MySqlite_db::MySqlite_db(QString& db_, QString db_name)
{
    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        QSqlDatabase::removeDatabase("qt_sql_default_connection");
    }
    this->default_db = db_;
    this->db_connection = QSqlDatabase::addDatabase(this->default_db );

    if (db_name != "")
        this->default_db_name = db_name;
    QString db_fullpath = "C:/Users/sandr/Desktop/database/"+ this->default_db_name + ".db";



    this->db_connection.setDatabaseName(db_fullpath); // Path to the database
    bool ok = this->db_connection.open();

    if(ok)
        QMessageBox::information(nullptr, "Database Connection Status", "Connection was successfull....");

}
bool MySqlite_db::check_status()
{
    if(!db_connection.isValid() || !db_connection.isOpen())
    {
        QMessageBox::warning(nullptr, "Database", "No connection to the database");
        return false;
    }
    return true;
}

// When Admin clicks on disconnect, this is the function that will be called
void MySqlite_db::disconnect_db()
{
     this->db_connection.close();
}
/*Help Funtion
 * Checks if a specific table exists in the database, returns true if found and flase if not*/

bool check_if_table_exist(str table_name)
{
    query q("SELECT name FROM sqlite_schema WHERE type='table' ORDER BY name");
    while(q.next())
    {
        str table_name_from_database = q.value(0).toString();
        if(table_name == table_name_from_database)
        {
            return true;
        }
    }
    return false;
}

// Student
bool MySqlite_db::insert_student(str& course,
                                 str& fullname,
                                 QDate& birthdate,
                                 int& gender,
                                 str& email,
                                 str& password)
{

    if(!this->check_status())
    {
        QMessageBox::warning(nullptr, "Database Status", "No connection to database...");
        return false;
    }
    QSqlQuery qur;
    qur.prepare("INSERT INTO student (course, fullname, birthdate, gender, email, password)"
                "VALUES(:kurs, :name, :geburtstag, :email, :passwort )");
    qur.bindValue(":kurs", course);
    qur.bindValue(":name", fullname);
    qur.bindValue(":geburtstag", birthdate);
    qur.bindValue(":email", email);
    qur.bindValue(":passwort", password);

        return qur.exec();

}
// subject
bool MySqlite_db::insert_subject(int& student_id, QString& subject_name, int& weights, float& ects )
{
    if(!this->check_status())
    {
        QMessageBox::warning(nullptr, "Database Error", "Database could not open");
        return false;
    }



    // str == QString
    QSqlQuery q;
    str qr_str = "INSERT INTO  subject (sudent_id, subject_name, weights, ects)"
                                               "VALUES (:stud_id, :sub_n, :wei, :ect)";

    q.prepare(qr_str);
    q.bindValue(":stud_id", student_id);
    q.bindValue(":sub_n", subject_name);
    q.bindValue(":wei", weights);
    q.bindValue(":ects", ects);

    return q.exec();
}

bool MySqlite_db::instert_new_admin(str &f, QDate &d, str &g, str &e, str &p)
{
    if(!this->check_status())
    {
        QMessageBox::warning(nullptr, "Database", "Database open failure");
        return false;
    }
    QSqlQuery q;
    str q_str =
        "INSERT INTO admin (fullname, birhdate, gender, email, password)"
        "VALUES (:f, :d, :g, :e, :p)";
    q.prepare(q_str);
    q.bindValue(":f", f);
    q.bindValue(":e", e);
    q.bindValue(":p", p);
    q.bindValue(":g", g);
    q.bindValue(":d", d);
    bool success = q.exec();
    if(success)
        return success;
    else {
        QMessageBox::warning(nullptr, "Database table", "failure");
    }
    return false;

}
