#include "administration.h"


/************************************************************************* Administration ***************************************************************************/




/// Translating Query of a Student which is then passed to the User Interface
///
/// Returns:
///
///     _sql (vector of Students)
std::vector<Student *> Administration::get_student(const QString email, const QString password)
{
    QSqlQuery qry = db->get_student_login(email, password);
    return _sql(qry); // returns query of a student


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




bool Administration::delete_subject(int id){

    return this->db->get_instance()->delete_subject(id);
}
void Administration::view_all_subjects() const{}

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

bool Administration::check_email(QString &email, QString table)
{
    if(this->db->get_instance()->email_exists(email, table))
        return true;
    return false;
}


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
        student_instance->set_password(ql.value("password").toString());
        student_instance->set_course(static_cast<Courses>(ql.value("Course").toInt()));

        _lists.push_back(student_instance);
    }
    delete student_instance;
    student_instance = nullptr;
    return _lists;
}


// subjects
