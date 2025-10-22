#ifndef ADMIN_PROFILE_DIALOG_H
#define ADMIN_PROFILE_DIALOG_H

#include <QDialog>
#include <QDate>
#include <QVBoxLayout>
#include "dialog_view_tables.h"
#include "admin.h"
namespace Ui {
class Admin_Profile_Dialog;
}

class Admin_Profile_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Admin_Profile_Dialog( Admin* = nullptr , QWidget *parent = nullptr);
    ~Admin_Profile_Dialog();

private slots:
    void on_pushButton_create_table_clicked();

    void on_commandLinkButton_create_database_clicked();


    void on_pushButton_view_table_clicked();

private:
    Ui::Admin_Profile_Dialog *ui;
    QDate _date;
    Admin* admin_pro;
    QVBoxLayout* vlayout;
    Dialog_view_tables* view_tab;
    void admin_profile();

    void current_date();

};

#endif // ADMIN_PROFILE_DIALOG_H
