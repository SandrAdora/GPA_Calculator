#include "calculate_gpa_dialog.h"
#include "ui_calculate_gpa_dialog.h"
#include <vector>
#include <QMessageBox>
Calculate_GPA_Dialog::Calculate_GPA_Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Calculate_GPA_Dialog)
{
    ui->setupUi(this);
    calculate_gpa();
}

Calculate_GPA_Dialog::~Calculate_GPA_Dialog()
{
    delete ui;
    delete this->enter_ects;
    delete this->enter_result;
    delete this->enter_subject_amount;
    delete this->enter_weights;
}

void Calculate_GPA_Dialog::calculate_gpa()
{

    double gpa = .0;
    int it = 0;
    // calculate GPA
    for(auto& elem : results_v)
    {

        gpa +=elem*weights_v[it];
        ++it;

    }
    gpa = (double)(gpa/n);
    QString gpa_str = QString::number(gpa);

    this->gpa= new QLineEdit();
    this->gpa->setText(gpa_str);

    QMessageBox::information( this, "Calculated", gpa_str);





}

void Calculate_GPA_Dialog::setup_gpa_caculation()
{

    this->enter_subject_amount = new QLabel();
    QLineEdit* enter_amount = new QLineEdit("How many results to calculate", this);


    // iterate through the amount given
    n = enter_amount->text().toInt();
    for(int i= 0; i < n; ++i)
    {
        this->enter_result = new QLabel(this);

        this->enter_weights = new QLabel(this);

        QLineEdit* result =  new QLineEdit(this);

        QLineEdit* weight = new QLineEdit(this);

        results_v.push_back(enter_result->text().toDouble());
        weights_v.push_back(enter_weights->text().toInt());
    }


}
