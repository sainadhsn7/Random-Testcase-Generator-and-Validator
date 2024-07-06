#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFile"
#include "QFileDialog"
#include "file_edit_dialogue.h"
#include <QMessageBox>
#include <QFileInfo>
#include "variable_details_dialog.h"
#include "variable.h"
#include "list_details_dialog.h"
#include "string_details_dialogue.h"
#include "matrix_details_dialogue.h"
#include "graph_dialogue.h"
#include "runner_dialogue.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(width(), height());
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
    file_filter = "C++ file (*.cpp);;Python file (*.py)";
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_action_Fast_solution_triggered()
{
    fast_sol_file = QFileDialog :: getOpenFileName(this, "Fast solution File", QDir::homePath(), file_filter);
    ui->line_fast_sol->setText(fast_sol_file);
}


void MainWindow::on_action_Slow_soluion_triggered()
{
    slow_sol_file = QFileDialog :: getOpenFileName(this, "Slow solution File", QDir::homePath(), file_filter);
    ui->line_slow_sol->setText(slow_sol_file);
}


void MainWindow::on_pushButton_fast_sol_clicked()
{
    fast_sol_file = QFileDialog :: getOpenFileName(this, "Fast solution File", QDir::homePath(), file_filter);
    ui->line_fast_sol->setText(fast_sol_file);
}


void MainWindow::on_pushButton_slow_sol_clicked()
{
    slow_sol_file = QFileDialog :: getOpenFileName(this, "Slow solution File", QDir::homePath(), file_filter);
    ui->line_slow_sol->setText(slow_sol_file);
}

void MainWindow::trigger_file_edit_dialogue(QString filename){
    QString dirPath = QFileInfo(filename).absolutePath();

    // Check if the directory exists
    QDir dir(dirPath);
    if (!dir.exists() or filename.isEmpty()) {
        QMessageBox::critical(nullptr, "Error", "Folder does not exist: " + dirPath);
        return;
    }

    // Check if the file exists
    QFile file(filename);
    if (!file.exists()) {
        // Create the file if it doesn't exist
        if (file.open(QIODevice::WriteOnly)) {
            file.close();
        } else {
            QMessageBox::critical(nullptr, "Error", "Failed to create file: " + filename);
            return;
        }
    }
    File_edit_dialogue *file_edit_dialogue = new File_edit_dialogue(filename, this);
    file_edit_dialogue->show();
}
void MainWindow::on_pushButton_fast_sol_edit_clicked()
{
    QString filename = ui->line_fast_sol->text();
    trigger_file_edit_dialogue(filename);
}


void MainWindow::on_pushButton_slow_sol_edit_clicked()
{
    QString filename = ui->line_slow_sol->text();
    trigger_file_edit_dialogue(filename);
}



void MainWindow::on_pushButton_add_clicked()
{
    QString name = "Variable1";
    QString type = "Integer";
    QString constraints = "Range: [ ";
    type = ui->comboBox_options->currentText();
    Variable *var = new Variable;
    Data_Structure *ds = new Data_Structure;
    if(type == "Variable"){
        variable_details_dialog *var_dialogue = new variable_details_dialog(&map_variable, &map_data_structure, var, this);
        if(var_dialogue->exec() == QDialog::Rejected){
            delete var;
            delete ds;
            delete var_dialogue;
            return;
        }
        delete var_dialogue;
        name = var->name;
        if(var->int_type){
            type = "Integer";
            constraints += QString::number(var->L);
            constraints += ",  ";
            constraints += QString::number(var->R);
        }
        else{
            constraints += var->char_subset;
            type = "Charecter";
        }
        constraints += " ]";
    }
    else{
        bool contains_intvar = false;
        for(auto var: map_variable){
            if(var->int_type){
                contains_intvar = true;
                break;
            }
        }
        if(!contains_intvar){
            QMessageBox::critical(this, "Error", "Please add atleast one Integer Variable");
            delete var;
            delete ds;
            return;
        }
        if(type == "List"){
            List_details_dialog *list_dialog = new List_details_dialog(ds, this);
            if(list_dialog->exec() == QDialog::Rejected){
                delete var;
                delete ds;
                delete list_dialog;
                return;
            }
            delete list_dialog;
            name = ds->name;
            type = "List";
            if(ds->ispermutation){
                constraints = "Permutation";
                if(ds->zero_base){
                    constraints += ", zero index";
                }
            }
            else{
                constraints += QString::number(ds->L);
                constraints += ",  ";
                constraints += QString::number(ds->R);
                constraints += " ]";
            }
            constraints.prepend("Size: " + ds->size_var->name + ", ");
        }
        else if(type == "String"){
            string_details_dialogue *string_dialogue = new string_details_dialogue(ds, this);
            if(string_dialogue->exec() == QDialog::Rejected){
                delete var;
                delete ds;
                delete string_dialogue;
                return;
            }
            delete string_dialogue;
            name = ds->name;
            type = "String";
            constraints.prepend("Size: " + ds->size_var->name + ", ");
            constraints.append(ds->char_set + " ]");
        }
        else if(type == "Matrix"){
            matrix_details_dialogue *matrix_dialogue = new matrix_details_dialogue(ds, this);
            if(matrix_dialogue->exec() == QDialog::Rejected){
                delete var;
                delete ds;
                delete matrix_dialogue;
                return;
            }
            delete matrix_dialogue;
            name = ds->name;
            type = "Matrix";
            constraints.prepend("Rows: " + ds->size_var->name + ", Columns: " + ds->size_var_2->name + ", ");
            constraints.append(QString::number(ds->L) + ", " + QString::number(ds->R) + " ]");
        }
        else if (type == "Graph"){
            graph_dialogue *graph_dial = new graph_dialogue(ds, this);
            if(graph_dial->exec() == QDialog::Rejected){
                delete var;
                delete ds;
                delete graph_dial;
                return;
            }
            delete graph_dial;
            name = ds->name;
            type = "Graph";
            if(ds->istree){
                type += "(Tree)";
            }
            constraints = ("Vertices: " + ds->size_var->name);
            if(!ds->istree)
                constraints.append(", Edges: " + ds->size_var_2->name);
            if(ds->weighted){
                constraints.append(", wt_range: [" + QString::number(ds->L) + ", " + QString::number(ds->R)+"]");
            }
            if(ds->zero_base){
                constraints.append(", 0 ind");
            }
            if(!ds->istree){
                if(ds->connected){
                    constraints.append(", connected");
                }
                if(ds->multi_edge){
                    constraints.append(", multiedge");
                }
                if(ds->self_loop){
                    constraints.append(", self loop");
                }
            }
        }
    }
    // Define fixed widths for each part
    int nameWidth = 50;
    int typeWidth = 50;
    int constraintsWidth = 50;

    // Construct the itemText string with fixed widths
    QString itemText = QString("%1  %2 %3")
                           .arg(name.leftJustified(nameWidth, ' '))
                           .arg(type.leftJustified(typeWidth, ' '))
                           .arg(constraints.leftJustified(constraintsWidth, ' '));
    QListWidgetItem *item = new QListWidgetItem(itemText);
    ui->listWidget->addItem(item);
    map_type[item] = type;
    if(type == "Integer" || type == "Charecter"){
        map_variable[item] = var;
        delete ds;
    }
    else{
        map_data_structure[item] = ds;
        delete var;
    }

}
void MainWindow::delete_data_structure(QListWidgetItem* ds_item){
    if(ds_item == nullptr)return;
    auto it = map_data_structure.find(ds_item);
    if (it == map_data_structure.end()) return;

    auto ds = it.value();
    if (ds == nullptr) return;

    // Remove associations with size variables
    if (ds->size_var != nullptr) {
        auto it = ds->size_var->used_by.find(ds->name);
        if(it!=ds->size_var->used_by.end()){
            ds->size_var->used_by.erase(it);
        }
        ds->size_var = nullptr;
    }
    if (ds->size_var_2 != nullptr) {
        auto it = ds->size_var_2->used_by.find(ds->name);
        if(it!=ds->size_var_2->used_by.end()){
            ds->size_var_2->used_by.erase(it);
        }
        ds->size_var_2 = nullptr;
    }

    // Erase from map and delete the data structure
    map_data_structure.erase(it);
    delete ds;
}
void MainWindow::delete_itemset(QList<QListWidgetItem*> delete_list){
    bool containsVariable = false;
    for (auto item : delete_list) {
        if (map_variable.contains(item) and map_variable[item]->int_type) {
            containsVariable = true;
            break;
        }
    }
    if (containsVariable) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::warning(this, "Delete Warning",
                                     "The selected items include variables. If these variables are deleted, "
                                     "all data structures using these variables will also be deleted. Do you want to continue?",
                                     QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::No) {
            return;
        }
    }

    QSet<QListWidgetItem*> delete_set;
    for (auto item : delete_list) {
        if (map_variable.contains(item)) {
            delete_set.insert(item);
            auto var = map_variable[item];
            for (auto it2 = var->used_by.begin(); it2!= var->used_by.end(); it2++) {
                auto ds_name = *it2;
                for (auto it = map_data_structure.begin(); it != map_data_structure.end(); ++it) {
                    if (it.value()->name == ds_name) {
                        delete_set.insert(it.key());
                    }
                }
            }
        }
        if (map_data_structure.contains(item)) {
            delete_set.insert(item);
        }
    }

    // Delete data structures
    for (auto item : delete_set) {
        delete_data_structure(item);
        if(map_type.contains(item)){
            map_type.remove(item);
        }
    }

    // Delete variables and clear the list widget
    for (auto item : delete_set) {
        if (map_variable.contains(item)) {
            auto var = map_variable[item];
            map_variable.remove(item);
            delete var;
        }
    }
    qDeleteAll(delete_set);
}
void MainWindow::on_pushButton_delete_clicked(){
    delete_itemset(ui->listWidget->selectedItems());
}
void MainWindow::on_pushButton_clear_clicked(){
    ui->listWidget->selectAll();
    delete_itemset(ui->listWidget->selectedItems());
}
QList<QListWidgetItem*> MainWindow::getListWidgetItems() const
{
    ui->listWidget->selectAll();
    auto lst = ui->listWidget->selectedItems();
    ui->listWidget->clearSelection();
    return lst;
}
void MainWindow::on_pushButton_clicked()
{

    QFileInfo fileInfofast(ui->line_fast_sol->text());
    QFileInfo fileInfoslow(ui->line_slow_sol->text());

    // Check if the file exists
    if (!fileInfofast.exists() || !fileInfofast.isFile() || !fileInfoslow.exists() || !fileInfoslow.isFile()) {
        QMessageBox::critical(this, "Invalid File Location", "The specified file location is invalid. Please check the path and try again.");
        return;
    }

    // Check if the file has a .cpp or .py extension
    QString extension1 = fileInfofast.suffix().toLower(), extension2 = fileInfoslow.suffix().toLower();
    if(extension1 == "cpp" || extension1 == "py" || extension2 == "cpp" || extension2 == "py"){
        runner_dialogue *runner = new runner_dialogue(ui->line_fast_sol->text(), ui->line_slow_sol->text(), ui->no_of_testcases->text().toInt(), this);
        runner->exec();
    }
    else{
        QMessageBox::warning(this, "File Type Warning", "The tester only accepts Python (.py) or C++ (.cpp) files.");
        return;
    }
}

