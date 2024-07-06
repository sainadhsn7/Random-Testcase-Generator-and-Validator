#ifndef LIST_DETAILS_DIALOG_H
#define LIST_DETAILS_DIALOG_H

#include <QDialog>
#include "variable.h"
#include <QListWidgetItem>
#include <mainwindow.h>
namespace Ui {
class List_details_dialog;
}

class List_details_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit List_details_dialog(Data_Structure* ds, MainWindow *parent);
    ~List_details_dialog();

private slots:
    void on_radioButton_normal_toggled(bool checked);

    void on_buttonBox_accepted();

private:
    Ui::List_details_dialog *ui;
    Data_Structure* data_structure;
    MainWindow *par;

};

#endif // LIST_DETAILS_DIALOG_H
