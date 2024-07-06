#ifndef RUNNER_DIALOGUE_H
#define RUNNER_DIALOGUE_H

#include <QDialog>
#include <QString>
#include <QProcess>
#include <mainwindow.h>
#include <gen.h>
namespace Ui {
class runner_dialogue;
}

class runner_dialogue : public QDialog
{
    Q_OBJECT

public:
    explicit runner_dialogue(QString fast_sol, QString slow_sol, int no_of_testcase, MainWindow *parent=nullptr);
    ~runner_dialogue();
    void compileFastSol();
    void compileSlowSol();
    void handleFastSolCompilationFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void handleSlowSolCompilationFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void runTests();

private:
    Ui::runner_dialogue *ui;
    QProcess *fastSolProcess;
    QProcess *slowSolProcess;
    QString fastSolFileName;
    QString slowSolFileName;
    QString fastSolOutput;
    QString slowSolOutput;
    MainWindow *par;
    int test_cases;
    void gentestcase(QString& testCase, Gen& gen);
    QString inputFilePath = "://files/rinputf.txt";
    QString fastOutputFilePath = ":/files/files/routputf1.txt";
    QString slowOutputFilePath = ":/files/files/routputf2.txt";
};

#endif // RUNNER_DIALOGUE_H
