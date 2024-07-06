#ifndef VARIABLE_DETAILS_DIALOG_H
#define VARIABLE_DETAILS_DIALOG_H

#include <QDialog>
#include "variable.h"
#include <QListWidgetItem>
#include <QMap>
namespace Ui {
class variable_details_dialog;
}

class variable_details_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit variable_details_dialog(QMap<QListWidgetItem*, Variable*> *map_variable, QMap<QListWidgetItem*, Data_Structure*>*map_data_structure, Variable *var_ptr, QWidget *parent = nullptr);
    ~variable_details_dialog();

private slots:
    void on_buttonBox_accepted();

    void on_radioButton_Integer_toggled(bool checked);

    void on_radioButton_charecter_toggled(bool checked);

private:
    Ui::variable_details_dialog *ui;
    Variable *var;
    QMap<QListWidgetItem*, Variable*> *map_var;
    QMap<QListWidgetItem*, Data_Structure*>*map_ds;
};

#endif // VARIABLE_DETAILS_DIALOG_H
