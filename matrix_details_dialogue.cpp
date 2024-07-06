#include "matrix_details_dialogue.h"
#include "ui_matrix_details_dialogue.h"
#include "variable.h"
#include <QMap>
#include <QListWidgetItem>
#include <NumericValidator.h>
#include <QMessageBox>
#include <mainwindow.h>
matrix_details_dialogue::matrix_details_dialogue(Data_Structure* ds, MainWindow *parent)
    : QDialog(parent)
    , ui(new Ui::matrix_details_dialogue)
{
    ui->setupUi(this);
    setFixedSize(width(), height());
    data_structure = ds;
    ui->lineEdit_name->setFocus();
    ui->lineEdit_max_val->setValidator(new NumericValidator(this));
    ui->lineEdit_min_val->setValidator(new NumericValidator(this));
    setTabOrder(ui->lineEdit_name, ui->lineEdit_min_val);
    setTabOrder(ui->lineEdit_min_val, ui->lineEdit_max_val);
    setTabOrder(ui->lineEdit_max_val, ui->buttonBox);
    QVector<QString> vector_string;
    for(auto var: parent->map_variable){
        if(var->int_type){
            vector_string.push_back(var->name);
        }
    }
    vector_string.sort();
    for(auto str: vector_string){
        ui->comboBox_rows->addItem(str);
    }
    for(auto str:vector_string){
        ui->comboBox_columns->addItem(str);
    }
    ui->comboBox_rows->setCurrentIndex(0);
    ui->comboBox_columns->setCurrentIndex(0);
}

matrix_details_dialogue::~matrix_details_dialogue()
{
    delete ui;
}

void matrix_details_dialogue::on_buttonBox_accepted()
{
    data_structure->name = ui->lineEdit_name->text();
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
    data_structure->L = ui->lineEdit_min_val->text().toLongLong();
    data_structure->R = ui->lineEdit_max_val->text().toLongLong();
    int cnt=0;
    for(auto var: par->map_variable){
        if(var->name == ui->comboBox_rows->currentText()){
            data_structure->size_var = var;
            cnt++;
        }
        if(var->name == ui->comboBox_columns->currentText()){
            data_structure->size_var_2 = var;
            cnt++;
        }
    }
    if(cnt!=2){
        return reject();
    }
}

