#ifndef CALCULATE_GPA_DIALOG_H
#define CALCULATE_GPA_DIALOG_H

#include <QDialog>
#include <QAction>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
namespace Ui {
class Calculate_GPA_Dialog;
}

class Calculate_GPA_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Calculate_GPA_Dialog(QWidget *parent = nullptr);
    ~Calculate_GPA_Dialog();

private:
    Ui::Calculate_GPA_Dialog *ui;

    // add wigets for calculate
    static int n;
    QLabel* enter_result;
    QLabel* enter_ects;
    QLabel* enter_subject_amount;
    QLabel* enter_weights;


    static std::vector<int> weights_v;
    static std::vector<double> results_v;

    QLineEdit* gpa;



    void calculate_gpa();
    void setup_gpa_caculation();

};

#endif // CALCULATE_GPA_DIALOG_H
