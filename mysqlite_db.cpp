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
MySqlite_db::MySqlite_db(){
    this->db_connection = QSqlDatabase::addDatabase("QSQLITE" );
    this->db_connection.setDatabaseName("C:/Users/sandr/Desktop/database/gpa_calculator.db"); // Path to the database

    if(this->db_connection.open()){
        qDebug()<< "Connection was successefull...";
    }else{
        qDebug() << "Connection was not successfull...failed to open the database...";
    }
}
