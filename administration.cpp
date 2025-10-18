#include "administration.h"


/************************************************************************* Administration ***************************************************************************/




/// Translating Query of a Student which is then passed to the User Interface
///
/// Returns:
///
///     _sql (vector of Students)
std::vector<Student *> Administration::SignInStudent(const QString& email, const QString& password)
{
    QSqlQuery qry = db->get_instance()->get_student_login(email, password);
    return _sql(qry); // returns vectpr list of a student
}

/// Registers an Administrator
///
/// Parms explaination:
///
/// f (fullname) , d (birthdate), g (gender), e (email), pw (password)
///
/// Returns:
///
/// success (True) or success (False)
bool Administration::register_admin(QString &f, QDate &d, QString &g, QString &e, QString &pw)
{
    int aid= this->db->get_instance()->insert_new_admin(f, d, g, e, pw);
    if(aid < 0){
        QMessageBox::warning(nullptr, "Register status error", "failed..ID negative");
        return false;
    }
    QMessageBox::information(nullptr, "Register Statjs", "success");
    return true;
}

std::vector<Admin *> Administration::signInAdmin(const QString email, const QString password)
{


    QSqlQuery q = this->db->get_instance()->signIn_admin(email, password) ;
    return this->A_sql(q);

}




bool Administration::delete_subject(int id){

    return this->db->get_instance()->delete_subject(id);
}
void Administration::view_all_subjects() const{


}

/// Comments to funtcion: Register student
/// @arg:
    ///course, fullname, birthdate,  gender email and password
/// @returns:
///     bool true or false according to the registration being successful or not
bool Administration::register_student(Courses& course, QString &name, QDate &geb, QString&gen, QString& em, QString& ps, QString& currGpa)
{
    // change course to string
    Student obj;
    obj.set_course(course);
    QString course_str = obj.get_course_str();

    int sid=this->db->get_instance()->insert_student(course_str,name, geb,gen,em, ps,currGpa);
    if(sid < 0)
    {
        QMessageBox::warning(nullptr, "Registration status", "failed");
        return false;
    }
    QMessageBox::information(nullptr, "Registration Status", "success");
    return true;

}
bool Administration::delete_student(int &id){
    if(id < 0 )
    {
        QMessageBox::warning(nullptr, "Error Delete student", "Invalid ID passed");
        return false;
    }
    bool ok = false;
    ok = db->delete_student(id);
    if(ok)
        return ok;


    return ok;

}


bool Administration::update_student_name(int& id, QString new_name){



}


bool Administration::update_subject_ect(int& id, double& ects){

}
bool Administration::update_subject_name(int& id, QString& new_name){

}
bool Administration::update_subject_weights(int& id ,double new_weights){


}

std::vector<Subject *> Administration::get_student_subjects(int student_id)

{
    query q = db->get_instance()->get_student_subjects(student_id);
    return S_sql(q);

}

bool Administration::check_email(QString &email, QString table)
{
    if(this->db->get_instance()->email_exists(email, table))
        return true;
    return false;
}



/// ---- translating query ---> std::vector<type>
std::vector<Student*> Administration::_sql(QSqlQuery ql)
{
    std::vector<Student*> _lists;
    Student* student_instance;

    while(ql.next())
    {
        int id = (ql.value("ID")).toInt();
        student_instance = new Student();

        student_instance->set_fullname(ql.value("fullname").toString());
        student_instance->set_birthdate(ql.value("birthdate").toDate());
        student_instance->set_gender(ql.value("gender").toString());
        student_instance->set_email(ql.value("email").toString());
        student_instance->set_course(static_cast<Courses>(ql.value("Course").toInt()));
        student_instance->set_personId(id);

        _lists.push_back(student_instance);
    }

    return _lists;
}

std::vector<Admin *> Administration::A_sql(QSqlQuery &q)
{

    // create a  vector list to save inputs
    std::vector<Admin*> _list;
    Admin* admin;
    while(q.next())
    {
        // retrieve id
        int id=q.value("ID").toInt();
        admin = new Admin();
        admin->set_fullname(q.value("fullname").toString());
        admin->set_birthdate(q.value("birthdate").toDate());
        admin->set_gender(q.value("gender").toString());
        admin->set_email(q.value("email").toString());
        admin->set_personId(id);

        _list.push_back(admin);
    }

    return _list;

}

std::vector<Subject *> Administration::S_sql(QSqlQuery q)
{
    std::vector<Subject*> list;
    Subject* subject;

    while(q.next())
    {
        subject = new Subject();
        int id = q.value("ID").toInt();
        int student_id = q.value("student_id").toInt();
        subject->set_subject(q.value("subject_name").toString());
        subject->set_ects(q.value("subject_ects").toInt());
        subject->set_weights(q.value("subject_weights").toInt());
        subject->set_id(id);
        subject->set_student_id(student_id);
        list.push_back(subject);
    }

    return list;

}


// subjects
