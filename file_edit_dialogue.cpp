#include "file_edit_dialogue.h"
#include "ui_file_edit_dialogue.h"
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
File_edit_dialogue::File_edit_dialogue(QString filename, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::File_edit_dialogue)
{
    ui->setupUi(this);
    file_name = filename;
    QFile file(file_name);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // Read the contents of the file
        QTextStream in(&file);
        QString fileContents = in.readAll();
        ui->plainTextEdit->setPlainText(fileContents);
        file.close();
        int font_size = ui->plainTextEdit->font().pointSize();
        ui->spinBox->setValue(font_size);

    } else {
        QMessageBox::warning(this, "Error", "Failed to open file: " + file_name);
    }
}

File_edit_dialogue::~File_edit_dialogue()
{
    delete ui;
}

void File_edit_dialogue::on_buttonBox_accepted()
{
    QFile file(file_name);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        // Write the text to the file
        QString text = ui->plainTextEdit->toPlainText();
        QTextStream out(&file);
        out << text;
        file.close();
    } else {
        QMessageBox::warning(this, "Error", "Failed to write in file: " + file_name);
    }
}


void File_edit_dialogue::on_spinBox_valueChanged(int arg1)
{
    QFont font = ui->plainTextEdit->font();
    font.setPointSize(arg1);
    ui->plainTextEdit->setFont(font);
}


