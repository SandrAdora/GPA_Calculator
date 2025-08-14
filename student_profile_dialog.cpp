#include "student_profile_dialog.h"
#include "ui_student_profile_dialog.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QIcon>
#include <QMenu>
#include <QAction>
#include <QScrollArea>
#include "signin_dialog.h"
student_profile_Dialog::student_profile_Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::student_profile_Dialog)
{
    ui->setupUi(this);
    studentMenuBar();
    studentProfile();
    studentSubjectProfile();
}

student_profile_Dialog::~student_profile_Dialog()
{
    delete ui;
}

void student_profile_Dialog::studentMenuBar()
{
    menubar = new QMenuBar(this);
    // create menus
    QMenu *fileMenus = new QMenu("more options...", this);
    signOut = new QAction(QIcon(":/icons/documentation/logos/signout.png"), "signOut", this);
    saveChanges = new QAction(QIcon(":/icons/documentation/logos/save_changes.jpg"), "saveChanges", this);
    discardChanges = new QAction(QIcon(":/icons/documentation/logos/Delete-Icon-Transparent-PNG.png"), "discardChanges", this);
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

void student_profile_Dialog::studentProfile()
{

    groupBox = new QGroupBox("Your Current information");
    QLineEdit *gpaEdit = new QLineEdit;
    gpaEdit->setPlaceholderText("Current GPA e.g. 2.5");
    /// Vetical Layout
    vlayout = new QVBoxLayout;
    QLineEdit *course = new QLineEdit;
    QLineEdit *email = new QLineEdit;
    QLineEdit *fullname = new QLineEdit;
    fullname->setPlaceholderText("Fullname");
    email->setPlaceholderText("Email");
    course->setPlaceholderText("Current course");
    vlayout->addWidget(course);
    vlayout->addWidget(fullname);
    vlayout->addWidget(email);
    vlayout->addWidget(gpaEdit);

    vlayout->addSpacing(10);


    groupBox->setLayout(vlayout);

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
    studentSubjects  = {"Mathematics", "Programming 1", "Programming 2", "Data structures" };
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
