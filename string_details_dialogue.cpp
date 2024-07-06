#include "string_details_dialogue.h"
#include "ui_string_details_dialogue.h"
#include <QDialog>
#include <QMap>
#include "variable.h"
#include <QListWidgetItem>
#include <QMessageBox>
#include <mainwindow.h>
string_details_dialogue::string_details_dialogue(Data_Structure* ds, MainWindow *parent)
    : QDialog(parent)
    , ui(new Ui::string_details_dialogue)
{
    ui->setupUi(this);
    setFixedSize(width(), height());
    data_structure = ds;
    par = parent;
    QVector<QString> vector_string;
    for(auto var:parent->map_variable){
        if(var->int_type){
            vector_string.push_back(var->name);
        }
    }
    vector_string.sort();
    for(auto&s:vector_string){
        ui->comboBox_2->addItem(s);
    }
    ui->comboBox_2->setCurrentIndex(0);
    ui->lineEdit_char_set->setText("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
    ui->lineEdit_name_3->setFocus();
    setTabOrder(ui->lineEdit_name_3, ui->lineEdit_char_set);
}

string_details_dialogue::~string_details_dialogue()
{
    delete ui;
}


void string_details_dialogue::on_buttonBox_accepted()
{
    data_structure->name = ui->lineEdit_name_3->text();
    if(data_structure->name.isEmpty()){
        QMessageBox::warning(this, tr("Empty Name"), tr("Name of String is Empty"));
        return reject();
    }
    bool duplicate = 0;
    for(auto var: par->map_variable){
        if(var->name == data_structure->name){
            duplicate = 1;break;
        }
    }
    for(auto ds: par->map_data_structure){
        if(duplicate or ds->name == data_structure->name){
            duplicate = 1;break;
        }
    }
    if(duplicate){
        QMessageBox::warning(this, tr("Duplicate Name"), tr("Name of String already exits"));
        return reject();
    }
    for(auto var: par->map_variable){
        if(var->name == ui->comboBox_2->currentText()){
            data_structure->size_var = var;
            var->used_by.insert(data_structure->name);
        }
    }
    data_structure->char_set = ui->lineEdit_char_set->text();
}

