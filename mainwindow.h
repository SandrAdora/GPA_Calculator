#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QToolBar>
#include "registration_dialog.h"
#include "signin_dialog.h"
#include "admin_dialog.h"
#include <QtSql>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:

// menu bar
    void on_pushButton_calculate_gpa_clicked();

    void on_actiondelete_triggered();

    void on_actionsignIn_triggered();

    void on_actionregistration_triggered();

    void on_action_password_triggered();

private:
    Ui::MainWindow *ui;
    signIn_Dialog *signIn;
    registration_Dialog *reg;
    Admin_Dialog* admin;




};
#endif // MAINWINDOW_H
