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

private slots:
    void on_pushButton_create_table_clicked();

    void on_commandLinkButton_create_database_clicked();

private:
    Ui::Admin_Profile_Dialog *ui;

};

#endif // ADMIN_PROFILE_DIALOG_H
