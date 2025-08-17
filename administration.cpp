#include "administration.h"
#include "mysqlite_db.h"


/************************************************************************* Administration ***************************************************************************/

Administration::Administration() {
    ptr = nullptr;

}


unique_ptr<Person> Administration::FactoryMethod()
{
    switch (this->type) {
    case MethodType::admin:
        return make_unique<Admin>();
    case MethodType::student:
        return make_unique<Student>();
    default:
        break;
    }
}
unique_ptr<Person> Administration::create_object(MethodType& t){
    this->type = t;
    return this->FactoryMethod();
}


void Administration::add_student(Courses& course, QString &name, QDate &geb, QString&gen, QString& em, QString& ps){

    if(ptr == nullptr){
        this->type = MethodType::student;     
        ptr = this->create_object(type);
    }
    ptr->set_fullname(name);
    ptr->set_birthdate(geb);
    ptr->set_email(em);
    ptr->set_password(ps);
    ptr->set_gender(gen);

    unique_ptr<Student> sptr(dynamic_cast<Student*>(ptr.release())); //Safe downcast: because student inheritsfrom person, using dynamic cast on the pointer and wrapp it aoround an new unique pointer
    sptr->set_course(course);

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



    students.push_back(move(sptr)); // adds a new student to the vector using the same singleton pointer
    // since downcast ptr now belongst to sptr must be reseted in order to be used again
    ptr.reset();

}
void Administration::add_new_subjects(QString& name, int& e, double& w){
  //  Subject *sub = new Subject(name, e, w);

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
