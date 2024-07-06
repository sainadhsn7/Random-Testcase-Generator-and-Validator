#ifndef STRING_DETAILS_DIALOGUE_H
#define STRING_DETAILS_DIALOGUE_H

#include <QDialog>
#include "variable.h"
#include <mainwindow.h>
namespace Ui {
class string_details_dialogue;
}

class string_details_dialogue : public QDialog
{
    Q_OBJECT

public:
    explicit string_details_dialogue(Data_Structure* ds, MainWindow *parent);
    ~string_details_dialogue();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::string_details_dialogue *ui;
    Data_Structure* data_structure;
    MainWindow *par;
};

#endif // STRING_DETAILS_DIALOGUE_H
