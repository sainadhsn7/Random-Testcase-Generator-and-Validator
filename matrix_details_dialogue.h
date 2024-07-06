#ifndef MATRIX_DETAILS_DIALOGUE_H
#define MATRIX_DETAILS_DIALOGUE_H

#include <QDialog>
#include "variable.h"
#include <mainwindow.h>
namespace Ui {
class matrix_details_dialogue;
}

class matrix_details_dialogue : public QDialog
{
    Q_OBJECT

public:
    explicit matrix_details_dialogue(Data_Structure* ds, MainWindow *parent);
    ~matrix_details_dialogue();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::matrix_details_dialogue *ui;
    Data_Structure* data_structure;
    MainWindow* par;

};

#endif // MATRIX_DETAILS_DIALOGUE_H
