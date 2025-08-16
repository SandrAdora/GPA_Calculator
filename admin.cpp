#include "admin.h"



Admin::Admin() {
    this->admin_id = -1;
    this->admin_password = "IT_admin";
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
