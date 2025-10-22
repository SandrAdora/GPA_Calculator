#ifndef SUBJECT_H
#define SUBJECT_H

#include <QString>
#include "student.h"

using str = QString;

class Subject: public Student
{
public:
    Subject(){
        subName="";
        ects=.0;
        weights=1;

    }
    Subject(str sub_name, int weights, float ects){
        subName=sub_name;
        weights=weights;
        ects=ects;
    }
    Subject(str, float);
    Subject(str);

    void set_subject(str name){
        subName = name;
    }
    str get_subject_name() const{
        return subName;
    }
    void set_ects(int e){
        ects = e;
    }
    float get_ects()const{
        return  ects;
    }
    void set_weights(int w){
        weights=w;
    }
    int get_weights() const{
        return weights;
    }
    int get_sub_id() const{
        return sub_id;
    }

void set_student_id(int std_id)
    {
    student_id=std_id;

    }
int get_student_id () const
    {
    return student_id;
    }

void set_id(int sub_id)
    {
    sub_id=sub_id;
    }


private:
    str subName;
    float ects;
    int weights;
    int sub_id= -1;
    int student_id = -1;


};

#endif // SUBJECT_H
