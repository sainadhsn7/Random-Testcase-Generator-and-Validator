#include "runner_dialogue.h"
#include "ui_runner_dialogue.h"
#include <QProcess>
#include <gen.h>
#include <mainwindow.h>
#include <variable.h>
#include <QMap>
#include <QListWidgetItem>
#include <QFile>
#include <QTextStream>
#include <QTimer>
#include <QDir>

runner_dialogue::runner_dialogue(QString fast_sol, QString slow_sol, int no_of_testcase, MainWindow *parent)
    : QDialog(parent)
    , ui(new Ui::runner_dialogue)
{
    ui->setupUi(this);
    test_cases = no_of_testcase;
    fastSolFileName = fast_sol;
    slowSolFileName = slow_sol;
    par = parent;
    QString folderPath = QDir::currentPath() + "/test_files";
    QDir dir(folderPath);

    // Ensure the directory exists
    if (!dir.exists()) {
        dir.mkpath(".");
    }

    // Define file paths within this directory
    inputFilePath = folderPath + "/rinputf.txt";
    fastOutputFilePath = folderPath + "/routputf1.txt";
    slowOutputFilePath = folderPath + "/routputf2.txt";
    // QTimer::singleShot(1000, this, &runner_dialogue::compileSlowSol);
    fastSolProcess = new QProcess(this);
    slowSolProcess = new QProcess(this);
    connect(fastSolProcess, &QProcess::finished, this, &runner_dialogue::handleFastSolCompilationFinished);
    connect(slowSolProcess, &QProcess::finished, this, &runner_dialogue::handleSlowSolCompilationFinished);
    compileFastSol();
}

runner_dialogue::~runner_dialogue()
{
    delete ui;
}
void runner_dialogue::compileFastSol(){
    ui->plainTextEdit->append("Compiling fast solution...\n");
    fastSolProcess->start("g++", QStringList() << fastSolFileName << "-o" << "fast_solution");
}
void runner_dialogue::compileSlowSol()
{
    ui->plainTextEdit->append("Compiling slow solution...\n");
    slowSolProcess->start("g++", QStringList() << slowSolFileName << "-o" << "slow_solution");
}
void runner_dialogue::handleFastSolCompilationFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    if (exitStatus == QProcess::CrashExit || exitCode != 0) {
        ui->plainTextEdit->append("Fast solution compilation failed:\n");
        ui->plainTextEdit->append(fastSolProcess->readAllStandardError());
    } else {
        ui->plainTextEdit->append("Fast solution compiled successfully.\n");
        compileSlowSol();
    }
}

void runner_dialogue::handleSlowSolCompilationFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    if (exitStatus == QProcess::CrashExit || exitCode != 0) {
        ui->plainTextEdit->append("Slow solution compilation failed:\n");
        ui->plainTextEdit->append(slowSolProcess->readAllStandardError());
    } else {
        ui->plainTextEdit->append("Slow solution compiled successfully.\n");
        runTests();
    }
}
void runner_dialogue::gentestcase(QString& testCase, Gen& gen){

    auto add = [&testCase](long long x){
        testCase.append(QString::number(x) + " ");
    };
    QHash<Variable*, long long> map_var_val;
    for(auto item: par->getListWidgetItems()){
        QString type = par->map_type[item];
        if(type == "Integer"){
            auto x = map_var_val[par->map_variable[item]] = gen.RandomNumber(par->map_variable[item]->L, par->map_variable[item]->R);
            add(x);
            testCase.append("\n");
        }
        else if(type == "Charecter"){
            auto &subset = par->map_variable[item]->char_subset;
            testCase.append(QString(subset[gen.RandomNumber(0, subset.size()-1)]) + " ");
        }
        else{
            auto ds = par->map_data_structure[item];
            if(type == "List"){
                if(ds->ispermutation){
                    for(auto x: gen.RandomPermutation(map_var_val[ds->size_var], ds->zero_base)){
                        add(x);
                    }
                    testCase.append("\n");
                }
                else{
                    for(auto x: gen.RandomList(map_var_val[ds->size_var], ds->L, ds->R)){
                        add(x);
                    }
                    testCase.append("\n");
                }
            }
            else if(type == "Matrix"){
                auto N = map_var_val[ds->size_var];
                auto M = map_var_val[ds->size_var_2];
                for(auto v: gen.RandomMatrix(N, M, ds->L, ds->R)){
                    for(auto x: v){
                        add(x);
                    }
                    testCase.append("\n");
                }
            }
            else if(type == "String"){
                auto N = map_var_val[ds->size_var];
                testCase.append(gen.RandomString(N, ds->char_set) + "\n");
            }
            else{
                auto N = map_var_val[ds->size_var];
                if(ds->istree){
                    for(auto p: gen.RandomTree(N, ds->weighted, ds->L, ds->R, ds->zero_base)){
                        for(auto x: p){
                            add(x);
                        }
                        testCase.append("\n");
                    }
                }
                else{
                    auto M = map_var_val[ds->size_var_2];
                    for(auto p: gen.RandomGraph(N, M, ds->weighted, ds->L, ds->R, ds->connected, ds->self_loop, ds->multi_edge, ds->zero_base)){
                        for(auto x: p){
                            add(x);
                        }
                        testCase.append("\n");
                    }
                }
            }
        }

    }
}

void runner_dialogue::runTests()
{
    ui->plainTextEdit->append("Input Format: \n");
    for(auto item: par->getListWidgetItems()){
        ui->plainTextEdit->append(item->text());
    }
    ui->plainTextEdit->append("\nRunning tests...\n");
    Gen gen;
    for (int test_num = 1; test_num <= test_cases; ++test_num) {
        // Generate a test case
        QString testCase;
        gentestcase(testCase, gen);
        // Clear the files before writing new data
        QFile::remove(inputFilePath);
        QFile::remove(fastOutputFilePath);
        QFile::remove(slowOutputFilePath);

        // Write the test case to the input file
        QFile inputFile(inputFilePath);
        if (inputFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&inputFile);
            out << testCase;
            inputFile.close();
            ui->plainTextEdit->append(QString(out.readAll()));
        }

        // Run fast solution
        QProcess fastSolRunner;
        fastSolRunner.setStandardInputFile(inputFilePath);
        fastSolRunner.setStandardOutputFile(fastOutputFilePath);
        fastSolRunner.start("./fast_solution");
        fastSolRunner.waitForFinished();

        // Run slow solution
        QProcess slowSolRunner;
        slowSolRunner.setStandardInputFile(inputFilePath);
        slowSolRunner.setStandardOutputFile(slowOutputFilePath);
        slowSolRunner.start("./slow_solution");
        slowSolRunner.waitForFinished();

        // Compare outputs line by line
        QFile fastOutputFile(fastOutputFilePath);
        QFile slowOutputFile(slowOutputFilePath);

        if (fastOutputFile.open(QIODevice::ReadOnly | QIODevice::Text) && slowOutputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream fastOutStream(&fastOutputFile);
            QTextStream slowOutStream(&slowOutputFile);
            QString fastLine;
            QString slowLine;
            bool mismatch = false;
            while (!fastOutStream.atEnd() && !slowOutStream.atEnd()) {
                fastLine = fastOutStream.readLine();
                slowLine = slowOutStream.readLine();
                if (fastLine != slowLine) {
                    mismatch = true;
                    break;
                }
            }
            fastOutputFile.close();
            slowOutputFile.close();
            if (mismatch || !fastOutStream.atEnd() || !slowOutStream.atEnd()) {
                ui->plainTextEdit->append(QString("Test %1 failed.\n").arg(test_num));
                ui->plainTextEdit->append("Mismatch in outputs:\n");
                ui->plainTextEdit->append("Test Case: \n" + testCase + "\n");
                ui->plainTextEdit->append("Fast solution output: " + fastLine);
                ui->plainTextEdit->append("Slow solution output: " + slowLine);
            } else {
                ui->plainTextEdit->append(QString("Test %1 passed.\n").arg(test_num));
            }
        } else {
            ui->plainTextEdit->append(QString("Failed to open output files for test %1.\n").arg(test_num));
        }
    }
}
