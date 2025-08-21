#ifndef ADMIN_DIALOG_H
#define ADMIN_DIALOG_H

#include <QDialog>
#include "admin.h"
#include "registration_dialog.h"
#include "admin_profile_dialog.h"

namespace Ui {
class Admin_Dialog;
}

class Admin_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Admin_Dialog(QWidget *parent = nullptr);
    ~Admin_Dialog();

private slots:
    void on_lineEdit_admin_returnPressed();

    void on_checkBox_new_admin_clicked();

    void on_pushButton_admin_ok_clicked();

private:
    Ui::Admin_Dialog *ui;
    Admin* admin;
    registration_Dialog* reg;
    Admin_Profile_Dialog* admin_profile;
};

#endif // ADMIN_DIALOG_H
