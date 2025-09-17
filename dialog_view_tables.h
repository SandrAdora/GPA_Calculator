#ifndef DIALOG_VIEW_TABLES_H
#define DIALOG_VIEW_TABLES_H

#include <QDialog>
#include <QAction>
#include <QPushButton>

namespace Ui {
class Dialog_view_tables;
}

class Dialog_view_tables : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_view_tables(QWidget *parent = nullptr);
    ~Dialog_view_tables();

private slots:
    void on_pushButton_load_table_clicked();
    void on_actiongoback_triggered();

private:
    Ui::Dialog_view_tables *ui;
    void goback_button();
    QPushButton* goback;

};

#endif // DIALOG_VIEW_TABLES_H
