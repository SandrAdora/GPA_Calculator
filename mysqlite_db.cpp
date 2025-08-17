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
    if (schema.empty()) return "";

    std::string table_name = schema[0];
    std::string sql = "CREATE TABLE " + table_name + " (\n";

    for (size_t i = 1; i < schema.size(); i += 2) {
        std::string col_name = schema[i];
        std::string col_type = (i + 1 < schema.size()) ? schema[i + 1] : "TEXT";
        std::string col_def = "    " + col_name + " " + col_type;

        if (i + 2 < schema.size() &&
            (schema[i + 2] == "primary key" || schema[i + 2] == "foreign key")) {
            col_def += " " + schema[i + 2];
            i++; // Skip key entry
        }

        sql += col_def + ",\n";
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

    string primary_key = "primary key";
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

MySqlite_db::MySqlite_db(){
    this->db_connection = QSqlDatabase::addDatabase("QSQLITE" );
    this->db_connection.setDatabaseName("C:/Users/sandr/Desktop/database/gpa_calculator.db"); // Path to the database
    bool ok = this->db_connection.open();

    if(ok){
        qDebug()<< "Connection was successefull...";
        cout << "A list of all the available tables will be displayed";
        query q("SELECT name FROM sqlite_schema WHERE type='table' ORDER BY name");
        while(q.next())
        {
            str tableName = q.value(0).toString();
            qDebug() << "Table: " << tableName;
        }


    }else{
        qDebug() << "Connection was not successfull...failed to open the database...";
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
