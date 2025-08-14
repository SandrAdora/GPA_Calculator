#include "administration.h"
#include "mysqlite_db.h"

Subject::Subject() {

    this->ects = .0;
    this->weights= -1;
    this->subName = "";
    this->sub_id = -1;
}

Subject::Subject(str name){
    this->subName = name;
}
Subject::Subject(str nn, int w, float e){
    this->ects = e;
    this->weights = w;
    this->subName = nn;
}
Subject::Subject(str nn, float w){
    this->subName = nn;
    this->weights = w;
}

int Subject::get_sub_id() const {
    return this->sub_id;
}
float Subject::get_ects() const {return this->ects;}
void Subject::set_ects(int e){this->ects = e; }
void Subject::set_subject(str sub){this->subName = sub;}
str Subject::get_subject() const {return this->subName;}
void Subject::set_weights(int w) {this->weights = w;}
int Subject::get_weights() const { return this->weights; }

/************************************************************************* Administration ***************************************************************************/

Administration::Administration() {}

auto* Administration::create_object(MethodType& t){
    this->type = t;
    return this->FactoryMethod();
}

void Administration::add_student(QString &name, QDate &geb, QString&gen, QString& em, QString& ps){

    if(ptr == nullptr){
        this->type = MethodType::student;
        ptr = this->create_object(type);
    }
    ptr->set_fullname(name);
    ptr->set_birthdate(geb);
    ptr->set_email(em);
    ptr->set_password(ps);
    ptr->set_gender(gen);

    // adding new student into the database
    const str table_name = "student";
    bool table_exists = false;
    MySqlite_db* db;

    if(db->get_instance())
    {
        qDebug() << "Do something";
    }else {
        qDebug() << "Do somethin else";
    }



    students.push_back( new Student(*ptr)); // adds a new student to the vector using the same singleton pointer



}
void Administration::add_new_subjects(QString name, int e, double w){
    Subject *sub = new Subject(name, e, w);

    // add the new obj in the vector list
} // name of subject, ects and weights of each subjects
bool Administration::delete_subject(int id){}
void Administration::view_all_subjects() const{}
bool Administration::delete_student(int &id){}
void Administration::display_all_Students() const{}
bool Administration::update_student_name(int& id, QString new_name){}

bool Administration::update_subject_ect(int& id, int new_name){}
bool Administration::update_subject_name(int& id, QString& new_name){}
bool Administration::update_subject_weights(int& id ,double new_weights){}


// subjects
