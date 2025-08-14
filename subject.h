#ifndef SUBJECT_H
#define SUBJECT_H

#include <QString>

using str = QString;
class Subject
{
public:
    Subject();
    Subject(str, int, float);
    Subject(str, float);
    Subject(str);

    void set_subject(str);
    str get_subject() const;
    void set_ects(int);
    float get_ects()const;
    void set_weights(int);
    int get_weights() const;
    int get_sub_id() const;




private:
    str subName;
    float ects;
    int weights;
    int sub_id = -1;


};

#endif // SUBJECT_H
