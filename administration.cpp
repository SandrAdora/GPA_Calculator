#include "administration.h"


/************************************************************************* Administration ***************************************************************************/

using dbug = QDebug;
Administration* Administration::_instance = nullptr;
Administration::Administration() {
    this->db->get_instance();
    ptr = nullptr;



}


Administration *Administration::get_administration()
{

    if(this->_instance == nullptr)
    {
        try {
            this->_instance = new Administration();

        }catch(const std::exception& err) {
            qDebug() << err.what();
        }
    }
    return this->_instance;
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

std::vector<Student *> Administration::get_student(const QString email, const QString password)
{
    QSqlQuery qry = db->get_student_login(email, password);
    return _sql(qry);


}

bool Administration::register_admin(QString &fullname, QDate &d, QString &g, QString &e, QString &pw)
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
    else if(g =="other" )
        gender = (int)Gender::NOTHING;
    else {
        gender = (int)Gender::NO_USER_INPUT;
    }
    admins.push_back(std::move(aptr)); // pushing student into the list
    ptr.reset();

    int id = this->db->get_instance()->insert_new_admin(fullname, d, g, e, pw);

    if(id < 0)
    {
        qDebug() <<"Register new Admin error";
        return false;
    }
    return true;
}




bool Administration::delete_subject(int id){}
void Administration::view_all_subjects() const{}

/// Comments to funtcion: Register student
/// @arg: course, fullname, birthdate, gender email and password
/// @returns: bool true or false according to the registration being successful or not
bool Administration::register_student(Courses& course, QString &name, QDate &geb, QString&gen, QString& em, QString& ps)
{

    if(ptr == nullptr){
        this->type = MethodType::student;
        ptr = this->create_object(type);
    }
    // check if email already exists
    QString table = "students";

    if( this->db->get_instance()->email_exists(em, table ));
    {
        qDebug() << "Email already exists. Please register with a new email address";
        QMessageBox::warning(nullptr, " Register Student", "Failed....email exists");
        return false;
    }

    ptr->set_fullname(name);
    ptr->set_birthdate(geb);
    ptr->set_email(em);
    ptr->set_password(ps);
    ptr->set_gender(gen);
    unique_ptr<Student> sptr(dynamic_cast<Student*>(ptr.release())); //Safe downcast: because student inheritsfrom person, using dynamic cast on the pointer and wrapp it aoround an new unique pointer
    sptr->set_course(course);
    str student_course = sptr->get_course_str();

    students.push_back(move(sptr)); // adds a new student to the vector using the same singleton pointer
    // since downcast ptr now belongst to sptr must be reseted in order to be used again
    double curr_gpa = 1.0;
    QString curr_gpa_str = QString::number(curr_gpa);
    sptr->set_gpa(curr_gpa_str);
    MySqlite_db* db = new MySqlite_db();
    int id =  db->get_instance()->insert_student(student_course, name, geb, gen, curr_gpa_str, em, ps);

    if(id < 0)
    {
        qDebug() << "Administration: Error creating a new student";
        return false;
    }
    return true;

}
bool Administration::delete_student(int &id){


}


bool Administration::update_student_name(int& id, QString new_name){



}

bool Administration::update_subject_ect(int& id, double& ects){

}
bool Administration::update_subject_name(int& id, QString& new_name){

}
bool Administration::update_subject_weights(int& id ,double new_weights){


}

bool Administration::check_email(QString &email, QString table)
{
    if(this->db->get_instance()->email_exists(email, table))
        return true;
    return false;
}


std::vector<Student*> Administration::_sql(QSqlQuery ql)
{
    std::vector<Student*> _lists;

    while(ql.next())
    {
        int id = (ql.value("ID")).toInt();
        student_instance = new Student();

        student_instance->set_fullname(ql.value("fullname").toString());
        student_instance->set_birthdate(ql.value("birthdate").toDate());
        student_instance->set_gender(ql.value("gender").toString());
        student_instance->set_email(ql.value("email").toString());
        student_instance->set_password(ql.value("password").toString());
        student_instance->set_course(static_cast<Courses>(ql.value("Course").toInt()));

        _lists.push_back(student_instance);
    }
    return _lists;
}


// subjects
