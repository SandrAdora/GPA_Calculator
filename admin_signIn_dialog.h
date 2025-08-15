#ifndef ADMIN_SIGNIN_DIALOG_H
#define ADMIN_SIGNIN_DIALOG_H

#include <QDialog>

namespace Ui {
class Admin_signIn_Dialog;
}

class Admin_signIn_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Admin_signIn_Dialog(QWidget *parent = nullptr);
    ~Admin_signIn_Dialog();

private:
    Ui::Admin_signIn_Dialog *ui;
};

#endif // ADMIN_SIGNIN_DIALOG_H
