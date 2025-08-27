#include "mysqlite_db.h"
#include <QMessageBox>

MySqlite_db* MySqlite_db::instance = nullptr;

MySqlite_db* MySqlite_db::get_instance() {
    if(this->instance == nullptr){
        try {
            this->instance = new MySqlite_db();

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


MySqlite_db::MySqlite_db(QString& db_name){
    this->db_connection = QSqlDatabase::addDatabase(db_name );
    this->db_connection.setDatabaseName("C:/Users/sandr/Desktop/database/gpa_calculator.db"); // Path to the database
    bool ok = this->db_connection.open();

    if(ok){
        QMessageBox::information(nullptr, "Database Connection Status", "Connection was successfull....");



    }else{
        QMessageBox::warning(nullptr, "Database Connection Status", "Connection was not successfull...failed to open the database...");
        // create database if not created
    }
}
bool MySqlite_db::check_status()
{
    if(!db_connection.isValid() || !db_connection.isOpen())
    {
        QMessageBox::warning(nullptr, "Database", "No connection to the database");
        return 0;
    }
    return 1;
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
bool MySqlite_db::insert_student(str& course, str& fullname, QDate& birthdate, int& gender, str& email, str& password)
{

    str new_table  = "student";
    bool creation_completed = false; // check if table should be created
    query createQuery; // query --> QSqlQuery
    if (!check_status()) // database should be open
    {

        return false;

    }else {
        // Create database if table_name not existant
        bool table_exists = check_if_table_exist(new_table);
        if(!table_exists)
        {

            // creating database
            // str --> QString


            str query_str = str::fromStdString( this->create_tables(6)); // create_tables create a table consisting of 6 columns
            createQuery.exec(query_str);
            table_exists = check_if_table_exist(new_table);
        }

        if(table_exists)
        {
            // Insert elements to the database
            str inserQuery = "INSERT INTO "+ new_table +
                             "(course, fullname, birthdate, gender, email, password) "
                                                          "VALUES("
                                                          ":cors, :fulln, :geb, :gen, :em, :pw"
                                                          ")";

            createQuery.prepare(inserQuery);
            createQuery.bindValue(":cors", course);
            createQuery.bindValue(":fulln", fullname);
            createQuery.bindValue(":geb", birthdate);
            createQuery.bindValue(":gen", gender);
            createQuery.bindValue(":em", email);
            createQuery.bindValue(":pw", password);
            return createQuery.exec();

        }else{
            QMessageBox::warning(nullptr, "Database Error", "Database table could not be created"); //nullptr since MySqlite_db isnt inheriting from QWidget
            return false;

        }
    }
}
// subject
bool MySqlite_db::insert_subject(int& student_id, QString& subject_name, int& weights, float& ects )
{
    if(!this->check_status())
    {
        QMessageBox::warning(nullptr, "Database Error", "Database could not open");
        return false;
    }
    str table_name = "subject";
    bool table_exist = check_if_table_exist(table_name);
    if(!table_exist)
    {
        // get student Id

        // Create new table with name subject if table cant be found in database
        // str == QStrin
        str query_str = str::fromStdString(this->create_tables(4));



    }
    // str == QString
    str qr_str = "INSERT INTO "+ table_name + "(sudent_id, subject_name, weights, ects)"
                                               "VALUES (:stud_id, :sub_n, :wei, :ect)";
}
