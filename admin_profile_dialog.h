#ifndef ADMIN_PROFILE_DIALOG_H
#define ADMIN_PROFILE_DIALOG_H

#include <QDialog>

namespace Ui {
class Admin_Profile_Dialog;
}

class Admin_Profile_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Admin_Profile_Dialog(QWidget *parent = nullptr);
    ~Admin_Profile_Dialog();

private:
    Ui::Admin_Profile_Dialog *ui;

};

#endif // ADMIN_PROFILE_DIALOG_H
