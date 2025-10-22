#ifndef STUDENT_PROFILE_DIALOG_H
#define STUDENT_PROFILE_DIALOG_H


#include <QDialog>
#include <QGroupBox>

#include <QVBoxLayout>
#include <QLineEdit>
#include <QMenuBar>
#include <QListWidget>
#include "student.h"
#include "subject.h"

namespace Ui {
class student_profile_Dialog;
}

class student_profile_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit student_profile_Dialog(Student*, std::vector<Subject*>  ,QWidget *parent = nullptr);
    ~student_profile_Dialog();

private slots:
    void on_actionsignout_triggered();
    void on_actionsaveChanges_triggered();
    void on_actiondiscardChanges_triggered();
    void on_actionnewSemester_triggered();

private:
    Ui::student_profile_Dialog *ui;

    QListWidget *listWidget;
    QGroupBox *groupBox;
    QVBoxLayout *vlayout;
    QAction *signOut;
    QAction *saveChanges;
    QAction *discardChanges;
    QAction* addNewSemester;

    Student* student_profile;
    std::vector<Subject*> student_subejects;

    // adding a new menu to the dialog
    QMenuBar *menubar;
    void studentMenuBar();
    void studentProfile();
    void studentSubjectProfile();
    void studentSemesterProfile();
};

#endif // STUDENT_PROFILE_DIALOG_H
