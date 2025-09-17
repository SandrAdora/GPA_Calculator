#include "admin.h"
#include "student.h"


Admin::Admin() {
    this->admin_id = -1;
    this->admin_password = "ad_password";
}

QString Admin::password_generator() {
    std::vector<int> random_num_list;
    int random_pw_length = 5;
    std::string password;

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    for (int i = 0; i < random_pw_length; ++i)
        random_num_list.push_back(std::rand() % 10); // 0-9 digits

    for (auto& e: random_num_list)
        password += std::to_string(e);

    this->admin_password = QString::fromStdString(password);

    return this->admin_password;
}

Admin::Admin(QString &fullname, QDate &d, QString &g, QString &e)
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

    this->fullname = fullname;
    this->birthdate = d;
    this->email = e;



}

bool Admin::admin_(str input){
    if(input == this->admin_password)
    {
        return true;
    }
    return false;
}

str Admin::get_it_admin_password() const {
    return this->admin_password;
}
