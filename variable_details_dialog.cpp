#include "variable_details_dialog.h"
#include "ui_variable_details_dialog.h"
#include "variable.h"
#include "NumericValidator.h"
#include <QMessageBox>
#include <QListWidgetItem>
#include <QMap>
variable_details_dialog::variable_details_dialog(QMap<QListWidgetItem*, Variable*> *map_variable, QMap<QListWidgetItem*, Data_Structure*>*map_data_structure, Variable *var_ptr, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::variable_details_dialog)
{
    ui->setupUi(this);
    setFixedSize(width(), height());
    var = var_ptr;
    map_var = map_variable;
    map_ds = map_data_structure;
    ui->label_varname_2->hide();
    ui->lineEdit_varname_2->hide();
    ui->lineEdit_max_val->setValidator(new NumericValidator(this));
    ui->lineEdit_min_val->setValidator(new NumericValidator(this));
    ui->lineEdit_varname_2->setText("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
    ui->lineEdit_varname->setFocus();
    setTabOrder(ui->lineEdit_varname, ui->lineEdit_min_val);
    setTabOrder(ui->lineEdit_min_val, ui->lineEdit_max_val);
    setTabOrder(ui->lineEdit_max_val, ui->lineEdit_varname_2);
    setTabOrder(ui->lineEdit_varname_2, ui->buttonBox);
    setTabOrder(ui->radioButton_Integer, ui->radioButton_charecter);
    setTabOrder(ui->radioButton_charecter, ui->lineEdit_varname);
}

variable_details_dialog::~variable_details_dialog()
{
    delete ui;
}

void variable_details_dialog::on_buttonBox_accepted()
{
    var->name = ui->lineEdit_varname->text();
    if(var->name.isEmpty()){
        QMessageBox::warning(this, tr("Empty Name"), tr("Name of Var is Empty"));
        return QDialog:: reject();
    }
    bool duplicate = 0;
    for(auto &vr: *map_var){
        if(vr->name == var->name){
            duplicate = 1;break;
        }
    }
    for(auto it = map_ds->begin(); it!= map_ds->end(); it++){
        if(duplicate or it.value()->name == var->name){
            duplicate =1;
            break;
        }
    }
    if(duplicate){
        QMessageBox::warning(this, tr("Duplicate Name"), tr("Name of Variable already exits"));
        return reject();
    }
    if(ui->radioButton_Integer->isChecked()){
        var->L = ui->lineEdit_min_val->text().toLongLong();
        var->R = ui->lineEdit_max_val->text().toLongLong();
    }
    else{
        var->char_subset = ui->lineEdit_varname_2->text();
        var->int_type = 0;
    }
}




void variable_details_dialog::on_radioButton_Integer_toggled(bool checked)
{
    if(checked == true){
        ui->label_max_val->show();
        ui->label_min_val->show();
        ui->lineEdit_max_val->show();
        ui->lineEdit_min_val->show();
    }
    else{
        ui->label_max_val->hide();
        ui->label_min_val->hide();
        ui->lineEdit_max_val->hide();
        ui->lineEdit_min_val->hide();
    }
}


void variable_details_dialog::on_radioButton_charecter_toggled(bool checked)
{
    if(checked == true){
        ui->label_varname_2->show();
        ui->lineEdit_varname_2->show();
    }
    else{
        ui->label_varname_2->hide();
        ui->lineEdit_varname_2->hide();
    }
}

