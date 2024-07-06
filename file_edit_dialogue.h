#ifndef FILE_EDIT_DIALOGUE_H
#define FILE_EDIT_DIALOGUE_H

#include <QDialog>
#include <QString>
#include <QWheelEvent>

namespace Ui {
class File_edit_dialogue;
}

class File_edit_dialogue : public QDialog
{
    Q_OBJECT

public:
    explicit File_edit_dialogue(QString filename, QWidget *parent = nullptr);
    ~File_edit_dialogue();

private slots:
    void on_buttonBox_accepted();

    void on_spinBox_valueChanged(int arg1);

private:
    Ui::File_edit_dialogue *ui;
    QString file_name;
};

#endif // FILE_EDIT_DIALOGUE_H
