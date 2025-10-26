#include "administration.h"


/************************************************************************* Administration ***************************************************************************/



/// ---- Singleton
Administration* Administration::admin_instance = nullptr;

Administration *Administration::get_administration()

{
    if (this->admin_instance == nullptr)
    {
        try {
            this->admin_instance = new Administration();
            {

            }
        }  catch (const std::exception& e) {
            qDebug() <<e.what();
        }
    }
    return admin_instance;
}

Administration::Administration()
{
    db = db->get_instance();
}

/// Translating Query of a Student which is then passed to the User Interface
///
/// Returns:
///
///     _sql (vector of Students)
bool Administration::SignInStudent(const QString& email, const QString& password)
{

    qDebug() << "SignIn Student called with email:" << email << "and password:" << password;
    QSqlQuery qry = db->get_students();
    while (qry.next()) {
        QString db_email = qry.value("email").toString();
        QString db_password = qry.value("password").toString();
        if (email == db_email && password == db_password) {
            qDebug() << "Success....student exists in the database...";
            return true;
        }
    }

    return false;

}

std::vector<Student *> Administration::get_student(QString em, QString pw)
{
    qDebug() << "Called Get Student function";
    QSqlQuery qry = db->signIn_student(em, pw);
    qDebug() << "Returning  a vector of Student details";
    return _sql(qry);

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
    int aid= this->db->insert_new_admin(f, d, g, e, pw);
    if(aid < 0){
        QMessageBox::warning(nullptr, "Register status error", "failed..ID negative");
        return false;
    }
    QMessageBox::information(nullptr, "Register Statjs", "success");
    return true;
}

std::vector<Admin *> Administration::get_Admin(const QString email, const QString password)
{

    qDebug() << "Called Get admin Function";
    QSqlQuery q = this->db->signIn_admin(email, password) ;
    qDebug() << "Returning  a vector of Admin details";
    return this->A_sql(q);
}

/// Sign In Admin
/// @param:
///     user name (string)
///     user password ( string )
/// @returns:
///     TRUE or FALSE

bool Administration::signInAdmin( QString email, QString user_password)
{

    QSqlQuery qry = this->db->get_admins();
    while(qry.next())
    {

        QString pw = qry.value("password").toString();
        QString em = qry.value("email").toString();

        if( em == email && pw == user_password )
            return true;

    }
    return false;

}

Courses Administration::stringToCourse(QString &major)
{


    if(major == "Architect")
        return Courses::Architect;
    else if (major == "Artificial Intelligence")
        return Courses::Artificial_Intelligence;
    else if (major == "Biomedical Engineering")
        return Courses::Biomedical_Engineering;
    else if(major == "Electionical Engineering")
        return Courses::Electronical_Engineering;
    else if (major == "Human Medicine")
        return Courses::Human_Medicine;
    else if (major == "Engineering")
        return Courses::Engineering;
    else if(major == "Vet Medicine")
        return Courses::Vet_Medicine;
    else if (major == "Technical Informatics")
        return Courses::Technical_Informatics;
    else if (major == "Data Science")
        return Courses::Data_Science;
    else if (major == "Mathematics")
        return Courses::Mathematics;
    else if (major == "Business Informatics")
        return Courses::Business_Informatics;
    else
        return Courses::NO_INPUT;
}

QString Administration::courseToString(Courses & course)
{
    if(course == Courses::Architect)
        return "Architect";
    else if(course == Courses::Artificial_Intelligence)
        return "Artificial Intelligence";
    else if(course == Courses::Biomedical_Engineering)
        return "Biomedical Engineering";
    else if (course== Courses::Electronical_Engineering)
        return "Electronical Engineering";
    else if(course == Courses::Engineering)
        return "Engineering";
    else if(course == Courses::Medical_Engineering)
        return "Medical Engineering";
    else if(course == Courses::Business_Informatics)
        return "Business Informatics";
    else if (course == Courses::Data_Science)
        return "Data Science";
    else if(course == Courses::Informatics)
        return "Informatics";
    else if (course == Courses::Mathematics)
        return "Mathematics";
    else if (course == Courses::Human_Medicine)
        return "Human Medicine";
    else if(course == Courses::Vet_Medicine)
        return "Vet Medicine";
    else if (course  == Courses::Technical_Informatics)
        return "Technicsl Informatics";
    else if (course == Courses::Medical_Engineering)
        return "Medical Engineering";
    else
        return "No Input";

}

Gender Administration::stringToGender(QString &gender)
{
    if(gender == "male" || gender == "Male")
        return Gender::MALE;
    else if(gender == "female" || gender == "Female")
        return Gender::FEAMALE;
    else if(gender == "other" || gender == "Other")
        return Gender::NOTHING;
    else
        return Gender::NO_USER_INPUT;
}

QString Administration::genderToString(Gender gender)
{
    if(gender == Gender::FEAMALE)
        return "female";
    else if(gender == Gender::MALE)
        return "male";
    else if(gender== Gender::NOTHING)
        return "undefined";
    else
        return " No Gender input";
}




bool Administration::delete_subject(int id){

    return this->db->delete_subject(id);
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
    QString course_str = this->courseToString(course);

    int sid=this->db->insert_student(course_str,name, geb,gen,em, ps,currGpa);
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


    if(id < 0)
    {
        QMessageBox::warning(nullptr, "Update Student name", "Invalid ID");
        return false;
    }

    if(this->db->update_student_name(id, new_name))
        return true;
    return false;

}


bool Administration::update_subject_ect(int& id, double& ects){

    if(id < 0)
    {
        QMessageBox::warning(nullptr, "Update Subject ects", "Invalid ID");
        return false;
    }

    if(this->db->update_subject_ect(id, ects));
        return true;
    return false;
}
bool Administration::update_subject_name(int& id, QString& new_name){



}
bool Administration::update_subject_weights(int& id ,double new_weights){

    if(id < 0)
    {
        QMessageBox::warning(nullptr, "Update Subject weights", "Invalid ID");
        return false;
    }

    if(this->db->update_subject_weights(id, new_weights))
        return true;
    return false;

}

std::vector<Subject *> Administration::get_student_subjects(int student_id)

{
    query q = db->get_student_subjects(student_id);
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
    qDebug() << "Calling _sql translation Query and passing output in a vector" ;
    while(ql.next())
    {
        Student* student_instance= new Student();
        int id = (ql.value("ID")).toInt();
        double gpa = (ql.value("currentGPA").toDouble());

        student_instance->set_course(static_cast<Courses>(ql.value("course").toInt()));
        student_instance->set_fullname(ql.value("fullname").toString());
        student_instance->set_birthdate(ql.value("birthdate").toDate());
        student_instance->set_gender(ql.value("gender").toString());
        student_instance->set_email(ql.value("email").toString());
        student_instance->set_password(ql.value("password").toString());
        student_instance->set_gpa(gpa);
        student_instance->set_personId(id);

        _lists.push_back(student_instance);
    }
    this->student_REGISTER.push_back(_lists);
    if (_lists.empty()) {
        qDebug() << "No students found in query result.";
        ;
    }
    return _lists;
}

std::vector<Admin *> Administration::A_sql(QSqlQuery &q)
{
    // create a  vector list to save inputs
    qDebug() << "Admin SQL Query translator us running";
    std::vector<Admin*> _list;
    while(q.next())
    {
        // retrieve id
        int id=q.value("admin_id").toInt();
        Admin* admin= new Admin();
        admin->set_fullname(q.value("fullname").toString());
        admin->set_birthdate(q.value("birthdate").toDate());
        admin->set_gender(q.value("gender").toString());
        admin->set_email(q.value("email").toString());
        admin->set_password(q.value("password").toString());
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

Student* Administration::studentRegister(int id)
{
    if(student_REGISTER.empty())
        return nullptr;
    for (const auto& student : student_REGISTER)
    {
        if (student[0]->get_id() == id)
        {
            return student[0];
        }
    }
    return nullptr;
}

bool Administration::check_status()
{
    return this->db->Connection();
}

void Administration::create_table()
{
    //this->db->build_create_table_sql();
}
