#ifndef ADMIN_DIALOG_H
#define ADMIN_DIALOG_H

#include <QDialog>
#include "admin.h"

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

private:
    Ui::Admin_Dialog *ui;
    Admin* admin;
};

#endif // ADMIN_DIALOG_H
