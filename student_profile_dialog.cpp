#include "student_profile_dialog.h"
#include "ui_student_profile_dialog.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QIcon>
#include <QMenu>
#include <QAction>
#include <QScrollArea>
#include "signin_dialog.h"
#include <QFormLayout>

student_profile_Dialog::student_profile_Dialog(Student* s, std::vector<Subject*> sub, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::student_profile_Dialog)
    , student_profile(s)
    , student_subejects(sub)
{
    ui->setupUi(this);
    Q_ASSERT(ui->label_student_name);
    Q_ASSERT(ui->verticalLayout_menuBar);
    Q_ASSERT(ui->verticalLayout_student_profile);

    studentMenuBar();
    studentProfile();
    studentSubjectProfile();
    studentSemesterProfile();
}

student_profile_Dialog::~student_profile_Dialog()
{
    delete ui;
}

void student_profile_Dialog::studentMenuBar()
{
    menubar = new QMenuBar(this);
    // create menus
    QMenu *fileMenus = new QMenu("...", this);
    signOut = new QAction(QIcon(":/icons/documentation/logos/signout.png"), "signOut", this);
    saveChanges = new QAction(QIcon(":/icons/documentation/logos/save_changes.jpg"), "saveChanges", this);
    discardChanges = new QAction(QIcon(":/icons/documentation/logos/Delete-Icon-Transparent-PNG.png"), "discardChanges", this);
    addNewSemester = new QAction(QIcon(""), "add new semester", this);

    // Connect actions to respective methods
    connect(signOut, &QAction::triggered, this, &student_profile_Dialog::on_actionsignout_triggered);
    connect(saveChanges, &QAction::triggered, this, &student_profile_Dialog::on_actionsaveChanges_triggered);
    connect(discardChanges, &QAction::triggered, this, &student_profile_Dialog::on_actiondiscardChanges_triggered);
    connect(addNewSemester, &QAction::triggered, this, &student_profile_Dialog::on_actionnewSemester_triggered);

    // Add actions to menuebar
    fileMenus->addAction(saveChanges);
    fileMenus->addAction(discardChanges);
    fileMenus->addAction(signOut);

    menubar->addMenu(fileMenus);
    // create a seprate vlayout
    QVBoxLayout *vl = new QVBoxLayout;
    vl->setMenuBar(menubar);
    ui->verticalLayout_menuBar->addLayout(vl);



}
void student_profile_Dialog::on_actionsignout_triggered(){
    hide();
    signIn_Dialog *signIn = new signIn_Dialog(this);
    signIn->show();



}
void student_profile_Dialog::on_actionsaveChanges_triggered(){}
void student_profile_Dialog::on_actiondiscardChanges_triggered(){}

void student_profile_Dialog::on_actionnewSemester_triggered()
{
    hide();
    QMessageBox::information(this, "Action add new Semester triggered", "success");
}

void student_profile_Dialog::studentProfile()
{
    qDebug() << "studentProfile() called";
    if (student_profile == nullptr) {
        QMessageBox::warning(this, "Error.", "Student could not be found!!");
        return;
    }


    Student* elem = student_profile;
    if (!elem) {
        qDebug() << "student_profile[0] is nullptr";
        return;
    }

    qDebug() << "Student name:" << elem->get_fullname();

    groupBox = new QGroupBox("Your Current Information", this);
    ui->label_student_name->setText(elem->get_course_str());

    QLineEdit* course = new QLineEdit(elem->get_course_str(), groupBox);
    QLineEdit* fullname = new QLineEdit(elem->get_fullname(), groupBox);
    QLineEdit* email = new QLineEdit(elem->get_email(), groupBox);
    QLineEdit* gpaEdit = new QLineEdit(QString::number(elem->get_gpa()), groupBox);

    course->setReadOnly(true);
    fullname->setReadOnly(true);
    email->setReadOnly(true);
    gpaEdit->setReadOnly(true);

    QFormLayout* formLayout = new QFormLayout;
    formLayout->addRow("Course:", course);
    formLayout->addRow("Full Name:", fullname);
    formLayout->addRow("Email:", email);
    formLayout->addRow("GPA:", gpaEdit);

    groupBox->setLayout(formLayout);
    ui->verticalLayout_student_profile->addWidget(groupBox);
}


void student_profile_Dialog::studentSubjectProfile()
{
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    QGroupBox *another = new QGroupBox("Subjects");
    listWidget = new QListWidget(this);
    QStringList studentSubjects;
    // will be filled from the subjects from the database

    for(auto& subjects : student_subejects)
        studentSubjects.push_back(subjects->get_subject_name());
    listWidget->addItems(studentSubjects);
    QWidget *scrollWidget = new QWidget;

    QVBoxLayout *vlSub = new QVBoxLayout;
    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollWidget);
    /// Horizontal Layout
    QHBoxLayout *horz = new QHBoxLayout;

    QPushButton *insertBtn = new QPushButton(QIcon(":/icons/documentation/logos/insert-icon-17.jpg"), "Add");
    QPushButton *deleteBtn = new QPushButton(QIcon(":/icons/documentation/logos/Delete-Icon-Transparent-PNG.png"), "Delete");
    horz->addWidget(insertBtn);
    horz->addWidget(deleteBtn);
    scrollLayout->addWidget(listWidget);


    scrollWidget->setLayout(scrollLayout);
    scrollArea->setWidget(scrollWidget);
    vlSub->addLayout(horz);
    vlSub->addWidget(scrollArea);

    another->setLayout(vlSub);
    ui->verticalLayout_studentSubject->addWidget(another);
}

void student_profile_Dialog::studentSemesterProfile()
{

    // display current semester
    QLabel* semester = new QLabel("Semester", this);


    QVBoxLayout* vl = new QVBoxLayout();
    vl->addWidget(semester);
    ui->verticalLayout_semester->addLayout(vl);



}
