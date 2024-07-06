#include "graph_dialogue.h"
#include "ui_graph_dialogue.h"
#include <mainwindow.h>
#include <variable.h>
#include <QMap>
#include <QListWidgetItem>
#include <QMessageBox>
graph_dialogue::graph_dialogue(Data_Structure* data_structure, MainWindow *parent)
    : QDialog(parent)
    , ui(new Ui::graph_dialogue)
{
    ui->setupUi(this);
    setFixedSize(width(), height());
    ds = data_structure;
    par = parent;
    ui->lineEdit_name->setFocus();
    QVector<QString> v;
    for(auto var: par->map_variable){
        if(var->int_type){
            v.push_back(var->name);
        }
    }
    v.sort();
    for(auto &s: v){
        ui->comboBox_vertices->addItem(s);
        ui->comboBox_edges->addItem(s);
    }
    setTabOrder(ui->lineEdit_name, ui->checkBox_weighted);
    setTabOrder(ui->checkBox_weighted, ui->checkBox_zero_index);
    setTabOrder(ui->checkBox_zero_index, ui->checkBox_connected);
    setTabOrder(ui->checkBox_connected, ui->checkBox_multi_edge);
    setTabOrder(ui->checkBox_multi_edge, ui->checkBox_self_loop);
    setTabOrder(ui->checkBox_self_loop, ui->buttonBox);
    ui->comboBox_edges->setCurrentIndex(0);
    ui->comboBox_edges->setCurrentIndex(0);
    ui->label_max_val->hide();
    ui->label_min_val->hide();
    ui->checkBox_connected->hide();
    ui->checkBox_multi_edge->hide();
    ui->checkBox_self_loop->hide();
    ui->lineEdit_max_val->hide();
    ui->lineEdit_min_val->hide();
    ui->comboBox_edges->hide();
    ui->label_edges->hide();
    ui->label_name->setText(" Tree Name");
}

graph_dialogue::~graph_dialogue()
{
    delete ui;
}

void graph_dialogue::on_buttonBox_accepted()
{
    ds->name = ui->lineEdit_name->text();
    if(ds->name.isEmpty()){
        QMessageBox::warning(this, tr("Empty Name"), tr("Name of graph is Empty"));
        return reject();
    }
    bool duplicate = 0;
    for(auto var: par->map_variable){
        if(var->name == ds->name){duplicate =1;break;}
    }
    for(auto dss: par->map_data_structure){
        if(duplicate or dss->name == ds->name){
            duplicate = 1;break;
        }
    }
    if(duplicate){
        QMessageBox::warning(this, tr("Duplicate Name"), tr("Name of graph already exits"));
        return reject();
    }
    for(auto var: par->map_variable){
        if(var->name == ui->comboBox_vertices->currentText()){
            ds->size_var = var;
            var->used_by.insert(ds->name);
        }
        if(!(ui->radioButton_tree->isChecked()) and var->name == ui->comboBox_edges->currentText()){
            ds->size_var_2 = var;
            var->used_by.insert(ds->name);
        }
    }
    if(ui->checkBox_weighted->isChecked()){
        ds->weighted = 1;
        ds->L = ui->lineEdit_min_val->text().toLongLong();
        ds->R = ui->lineEdit_max_val->text().toLongLong();
    }
    if(ui->checkBox_zero_index->isChecked()){
        ds->zero_base = 1;
    }
    if(ui->radioButton_tree->isChecked()){
        ds->connected = 1;
        ds->istree = 1;
    }
    else{
        if(ui->checkBox_connected)ds->connected = 1;
        if(ui->checkBox_multi_edge)ds->multi_edge = 1;
        if(ui->checkBox_self_loop)ds->self_loop = 1;
    }
}


void graph_dialogue::on_radioButton_tree_toggled(bool checked)
{
    if(checked){
        ui->checkBox_connected->hide();
        ui->checkBox_multi_edge->hide();
        ui->checkBox_self_loop->hide();
        ui->comboBox_edges->hide();
        ui->label_edges->hide();
        ui->label_name->setText(" Tree Name");
    }
    else{
        ui->checkBox_connected->show();
        ui->checkBox_multi_edge->show();
        ui->checkBox_self_loop->show();
        ui->comboBox_edges->show();
        ui->label_edges->show();
        ui->label_name->setText("Graph Name");
    }
}


void graph_dialogue::on_checkBox_weighted_toggled(bool checked)
{
    if(checked){
        ui->lineEdit_max_val->show();
        ui->lineEdit_min_val->show();
        ui->label_max_val->show();
        ui->label_min_val->show();
    }
    else{
        ui->lineEdit_max_val->hide();
        ui->lineEdit_min_val->hide();
        ui->label_max_val->hide();
        ui->label_min_val->hide();
    }
}

