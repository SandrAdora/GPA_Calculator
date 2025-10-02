#include "administration.h"


/************************************************************************* Administration ***************************************************************************/

using dbug = QDebug;
Administration* Administration::_instance = nullptr;
Administration::Administration() {
    ptr = nullptr;
    this->db = this->db->get_instance(); // initialize the db

}


Administration *Administration::get_administration()
{

    if(this->_instance == nullptr)
    {
        try {
            this->_instance = new Administration();
            {

            }

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
    else if(g =="Dont disclose" || g == "Dont Disclos" || g == "dont disclos")
        gender = (int)Gender::DONT_DISCLOSE;
    else {
        gender = (int)Gender::NOTHING;
    }
    admins.push_back(move(aptr)); // pushing student into the list
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

bool Administration::register_student(Courses& course, QString &name, QDate &geb, QString&gen, QString& gpa, QString& em, QString& ps)
{
    if(ptr == nullptr){
        this->type = MethodType::student;
        ptr = this->create_object(type);
    }
    // check if email already exists

    if( this->check_email(em))
    {
        qDebug() << "Email already exists. Please register with a new emailadress";
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
    const str table_name = "students";
    bool table_exists = false;

    students.push_back(move(sptr)); // adds a new student to the vector using the same singleton pointer
    // since downcast ptr now belongst to sptr must be reseted in order to be used again
    ptr.reset();
    double d_gpa;
    if(gpa == "")
        d_gpa=.00;
    else
    d_gpa=(double)gpa.toDouble();
    int id =  db->get_instance()->insert_student(student_course, name, geb, gender, em, ps, d_gpa);

    if(id < 0)
    {
        qDebug() << "Error creating a new student";
        return false;
    }
    return true;

}
bool Administration::delete_student(int &id){

    QSqlQuery q;
    q.prepare("select student_id, fullname, course, gender, gpa, email, password, birtdate FROM students WHERE student_id=:id ");
    q.bindValue(":id", id);
    if(q.exec())
    {
        QMessageBox::information(nullptr, "Delete Student Status", "Success");
        return true;
    }
    else {
        qDebug() << "Delete Status failed:" << q.lastError();
    }

    return false;
}


bool Administration::update_student_name(int& id, QString new_name){

    QSqlQuery q;
    q.prepare("UPDATE students SET fullname = :fullname WHERE student_id=:id");
    q.bindValue(":id", id);
    q.bindValue(":fullname",new_name);
    if(q.exec())
    {
        qDebug() << "Update student fullname success.";
        qDebug() << "updated to " << new_name;

    }else{
        qDebug() << "Error: Updating fullname fail:" << q.lastError();
        return false;
    }
    return true;

}

bool Administration::update_subject_ect(int& id, double& ects){
    QSqlQuery q;
    q.prepare("UPDATE subjects SET ects=:ects WHERE subject_id=:id");
    q.bindValue(":id", id);
    q.bindValue(":sub_name",ects);
    if(q.exec())
    {
        qDebug() << "Update subject etcs success.";
        qDebug() << "updated to " << ects;

    }else{
        qDebug() << "Error: Updating subject ects fail:" << q.lastError();
        return false;
    }
    return true;
}
bool Administration::update_subject_name(int& id, QString& new_name){
    QSqlQuery q;
    q.prepare("UPDATE subjects SET subject_name=:sub_name WHERE subject_id=:id");
    q.bindValue(":id", id);
    q.bindValue(":sub_name",new_name);
    if(q.exec())
    {
        qDebug() << "Update subject name success.";
        qDebug() << "updated to " << new_name;

    }else{
        qDebug() << "Error: Updating subject name fail:" << q.lastError();
        return false;
    }
    return true;
}
bool Administration::update_subject_weights(int& id ,double new_weights){

    QSqlQuery q;
    q.prepare("UPDATE subjects SET subject_weights=sub_weights WHERE subject_id=:id");
    q.bindValue(":id", id);
    q.bindValue(":sub_weights",new_weights);
    if(q.exec())
    {
        qDebug() << "Update subject weights success.";
        qDebug() << "updated to " << new_weights;

    }else{
        qDebug() << "Error: Updating subject weights fail:" << q.lastError();
        return false;
    }
    return true;
}

bool Administration::check_email(QString &email)
{
    QSqlQuery ql;
    ql.prepare("select email from students where email=:email");
    ql.bindValue(":email", email);
    if(ql.exec())
        return true;
    return false;
}

std::vector<Student*> Administration::_sql(QSqlQuery ql)
{
    std::vector<Student*> _lists;

    while(ql.next())
    {
        int id = (ql.value("student_id")).toInt();
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
