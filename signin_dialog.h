#ifndef SIGNIN_DIALOG_H
#define SIGNIN_DIALOG_H

#include <QDialog>
#include "student_profile_dialog.h"
#include "administration.h"
namespace Ui {
class signIn_Dialog;
}

class signIn_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit signIn_Dialog(QWidget *parent = nullptr);
    ~signIn_Dialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_signIn_canceled_clicked();

private:
    Ui::signIn_Dialog *ui;
    student_profile_Dialog *pro;
    Administration* admin_class;
    std::vector<Student*> student_vec;

};

#endif // SIGNIN_DIALOG_H
