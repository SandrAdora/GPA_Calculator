#include "administration.h"


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

bool Administration::add_neww_admin(QString &fullname, QDate &d, QString &g, QString &e, QString &pw)
{
    if(this->ptr == nullptr)
    {
        this->type = MethodType::admin;
        ptr = this->create_object(type);
    }
    ptr->set_fullname(fullname);
    ptr->set_birthdate(d);
    ptr->set_gender(g);
    ptr->set_email(e);
    ptr->set_password(pw);
    //using unique pointer to handle del allocated obj
    unique_ptr<Admin> aptr(dynamic_cast<Admin*>(ptr.release()));

    // allcate the correct gender type
    int gender = -1;
    if ( g == "male" || g == "Male")
        gender = (int)Gender::MALE;
    else if ( g == "female" || g == "Feamale")
        gender = (int)Gender::FEAMALE;
    else if(g =="Dont disclose" || g == "Dont Disclos" || g == "dont disclos")
        gender = (int)Gender::DONT_DISCLOSE;
    else {
        gender = (int)Gender::NOTHING;
    }
    const QString ta_na = "admin";
    bool table_name_exits = false;


    ///check for exstance
    if(!db->check_status())
    {
        QMessageBox::warning(nullptr, "Database", "Database is not open");
        return false;
    }
    admins.push_back(move(aptr)); // pushing student into the list
    ptr.reset();

    // add admin to the database

}


bool Administration::add_student(Courses& course, QString &name, QDate &geb, QString&gen, QString& em, QString& ps){

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
    str student_course = sptr->get_course_str();
    int gender = -1;
    if (gen == "male" || "Male" )
        gender = (int)Gender::MALE;
    else if(gen == "female" || "Female")
        gender = (int)Gender::FEAMALE;
    else if(gen == "dont_disclose")
        gender  = (int)Gender::DONT_DISCLOSE;
    else
        gender = (int)Gender::NOTHING;

    // adding new student into the database
    const str table_name = "student";
    bool table_exists = false;


    if(!db->get_instance())
    {
        return false;
    }
    students.push_back(move(sptr)); // adds a new student to the vector using the same singleton pointer
    // since downcast ptr now belongst to sptr must be reseted in order to be used again
    ptr.reset();
    return db->insert_student(student_course, name, geb, gender, em, ps);

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
