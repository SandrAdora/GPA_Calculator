#include "subject.h"

Subject::Subject() {

    this->ects = .0;
    this->weights= -1;
    this->subName = "";
    this->sub_id = -1;
}

Subject::Subject(str name){
    this->subName = name;
}
Subject::Subject(str nn, int w, float e){
    this->ects = e;
    this->weights = w;
    this->subName = nn;
}
Subject::Subject(str nn, float w){
    this->subName = nn;
    this->weights = w;
}

int Subject::get_sub_id() const {
    return this->sub_id;
}
float Subject::get_ects() const {return this->ects;}
void Subject::set_ects(int e){this->ects = e; }
void Subject::set_subject(str sub){this->subName = sub;}
str Subject::get_subject() const {return this->subName;}
void Subject::set_weights(int w) {this->weights = w;}
int Subject::get_weights() const { return this->weights; }
