#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "variable.h"
#include <QMap>
#include <QListWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QMap<QListWidgetItem*, Variable*> map_variable;
    QMap<QListWidgetItem*, Data_Structure*> map_data_structure;
    QMap<QListWidgetItem*, QString> map_type;
    QList<QListWidgetItem*> getListWidgetItems() const;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_action_Fast_solution_triggered();

    void on_action_Slow_soluion_triggered();

    void on_pushButton_fast_sol_clicked();

    void on_pushButton_slow_sol_clicked();

    void on_pushButton_fast_sol_edit_clicked();

    void on_pushButton_slow_sol_edit_clicked();

    void on_pushButton_add_clicked();
    void on_pushButton_delete_clicked();
    void on_pushButton_clear_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QString fast_sol_file, slow_sol_file, file_filter;
    void trigger_file_edit_dialogue(QString filename);
    void delete_data_structure(QListWidgetItem* ds_item);
    void delete_itemset(QList<QListWidgetItem*> delete_list);
};
#endif // MAINWINDOW_H
