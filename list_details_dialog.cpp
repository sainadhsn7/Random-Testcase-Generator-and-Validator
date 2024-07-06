#include "list_details_dialog.h"
#include "ui_list_details_dialog.h"
#include <variable.h>
#include "NumericValidator.h"
#include <QMap>
#include <QListWidgetItem>
#include <QString>
#include <QVector>
#include <QMessageBox>
#include <mainwindow.h>
List_details_dialog::List_details_dialog(Data_Structure* ds, MainWindow *parent)
    : QDialog(parent)
    , ui(new Ui::List_details_dialog)
{
    ui->setupUi(this);
    setFixedSize(width(), height());
    data_structure = ds;
    par = parent;
    ui->lineEdit_max_val->setValidator(new NumericValidator(this));
    ui->lineEdit_min_val->setValidator(new NumericValidator(this));
    QVector<QString> vector_string;
    for(auto var: parent->map_variable){
        if(var->int_type){
            vector_string.push_back(var->name);
        }
    }
    vector_string.sort();
    for(auto&s:vector_string){
        ui->comboBox->addItem(s);
    }
    ui->comboBox->setCurrentIndex(0);
    ui->checkBox->hide();
    ui->lineEdit_name->setFocus();
    setTabOrder(ui->lineEdit_name, ui->lineEdit_min_val);
    setTabOrder(ui->lineEdit_min_val, ui->lineEdit_max_val);

}

List_details_dialog::~List_details_dialog()
{
    delete ui;
}

void List_details_dialog::on_radioButton_normal_toggled(bool checked)
{
    if(!checked){
        ui->label_max_val->hide();
        ui->label_min_val->hide();
        ui->lineEdit_max_val->hide();
        ui->lineEdit_min_val->hide();
        ui->checkBox->show();
    }
    else{
        ui->label_max_val->show();
        ui->label_min_val->show();
        ui->lineEdit_max_val->show();
        ui->lineEdit_min_val->show();
        ui->checkBox->hide();
    }
}


void List_details_dialog::on_buttonBox_accepted()
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

    if(ui->radioButton_normal->isChecked()){
        data_structure->L = ui->lineEdit_min_val->text().toLongLong();
        data_structure->R = ui->lineEdit_max_val->text().toLongLong();
    }
    for(auto var: par->map_variable){
        if(var->name == ui->comboBox->currentText()){
            data_structure->size_var = var;
            var->used_by.insert(data_structure->name);
        }
    }
    if(ui->radioButton_permutation->isChecked()) data_structure->ispermutation = 1;
    if(ui->checkBox->isChecked())data_structure->zero_base = 1;
}

