#include "admin.h"
#include "student.h"


Admin::Admin() {
    this->admin_id = -1;
    this->admin_password = "ad_password";
}

Admin::Admin(QString &, QDate &, Gender &, QString &, QString &)
{
    Gender gen;
    if (g == "male" || g == "Male")
        gen = Gender::MALE;
    else if(g == "female" || g == "Female")
        gen = Gender::FEAMALE;
    else if(g == "Dont disclose" || g == "dont disclosr" || g == "Dont Disclose")
        gen = Gender::DONT_DISCLOSE;
    else
        gen = Gender::NOTHING;

}

bool Admin::admin_(str input){
    if(input == this->admin_password)
    {
        return true;
    }
    return false;
}

bool Admin::add_new_admin(str &name, QDate &b, str &g, str &e, str &pw)
{

    if( this->ptr == )




}
str Admin::get_it_admin_password() const {
    return this->admin_password;
}
