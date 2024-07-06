#ifndef GRAPH_DIALOGUE_H
#define GRAPH_DIALOGUE_H

#include <QDialog>
#include <mainwindow.h>
#include <variable.h>
namespace Ui {
class graph_dialogue;
}

class graph_dialogue : public QDialog
{
    Q_OBJECT

public:
    explicit graph_dialogue(Data_Structure *data_structure, MainWindow *parent = nullptr);
    ~graph_dialogue();

private slots:
    void on_buttonBox_accepted();

    void on_radioButton_tree_toggled(bool checked);

    void on_checkBox_weighted_toggled(bool checked);

private:
    Ui::graph_dialogue *ui;
    MainWindow *par;
    Data_Structure *ds;
};

#endif // GRAPH_DIALOGUE_H
