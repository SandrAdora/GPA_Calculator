

#include "student.h"



Student::Student() {

    this->fullname = "";
    this->email = "school@example.com";
    this->password = "xxxxxx";
    this->gender = Gender::DONT_DISCLOSE;
    this->birthdate = QDate(1990, 3, 13);
    this->student_id = -1;
    this->course = Courses::Artificial_Intelligence;

}


Student::Student(int id, QString name, QDate dat, Gender gen, QString em, QString pw, Courses cs, double gpa){
    this->fullname = name;
    this->email = em;
    this->gender = gen;
    this->birthdate = dat;
    this->student_id = id;
    this->course = cs;
    this->student_id = id;
    this->gpa = gpa;

}
Student::Student(Courses cs, QString name, QDate d, Gender g, QString em, QString pw, double gp){
    this->fullname = name;
    this->email = em;
    this->course = cs;
    this->birthdate = d;
    this->gender = g;
    this->password = pw;
    this->gpa = gp;

}
Student::Student( QString name, QDate d, Gender g, QString em, QString pw){
    this->fullname = name;
    this->email = em;
    this->course = Courses::Artificial_Intelligence; // default choice
    this->birthdate = d;
    this->gender = g;
    this->password = pw;
}


void Student::set_course(Courses cs){
    this->course = cs;

}
int Student::get_id() const {
    return this->student_id;
}
QString Student::get_course_str() const
{
    if(this->course == Courses::Architect)
        return "Architect";
    else if(this->course == Courses::Artificial_Intelligence)
        return "Artificial_Intelligence";
    else if(this->course == Courses::Biomedical_Engineering)
        return "Biomedical_Engineering";
    else if(this->course == Courses::Electronical_Engineering)
        return "Electronical_Engineering";
    else if(this->course == Courses::Engineering)
        return "Engineering";
    else if(this->course == Courses::Medical_Engineering)
        return "Medical_Engineering";
    else if(this->course == Courses::Business_Informatics)
        return "Business_Informatics";
    else if(this->course == Courses::Data_Science)
        return "Data_Science";
    else if(this->course == Courses::Human_Medicine)
        return "Human_Medicine";
    else if(this->course == Courses::Vet_Medicine)
        return "Vet_Medicine";
    else if(this->course == Courses::Technical_Informatics)
        return "Technical_Informatics";
    else if(this->course == Courses::Mathematics)
        return "Mathematics";
    else if(this->course == Courses::Administrator)
        return "Administrator";
    return "";

}
Courses Student::get_course_cour(QString& major)
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
    return Courses::Administrator;

}
