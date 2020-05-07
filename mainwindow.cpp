#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <vector>
#include <omp.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->button1,SIGNAL(released()),this,SLOT(prefixSoucet()));
    connect(ui->button2,SIGNAL(released()),this,SLOT(prefixSoucetViceVlaken()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

std::vector<int> MainWindow::generateInputVector(int max, bool omezeni) {
    if(max > 32 && omezeni) {
     std::vector<int> vector = {};
     return vector;
    } else {
        std::vector<int> vysokozdvizny_vozik;
        for(int i = 1; i <= max; i++) {
            vysokozdvizny_vozik.push_back(i);
        }
        return vysokozdvizny_vozik;
    }
}

void MainWindow::prefixSoucet()
{
    int size = ui->lineEdit1->text().toInt();
    std::vector<int> numbers = generateInputVector(size, true);
    if(numbers.size() == 0) {
        ui->label1->setText("Tak takhle teda ne.");
        return;
    }
    int result = 0;
#pragma omp parallel for shared(result) num_threads(numbers.size())
    for(uint i = 0; i < numbers.size(); i++) {
        result += numbers.at(i);
    }
    ui->label1->setText(QString::number(result));
}

void MainWindow::prefixSoucetViceVlaken()
{
    int size = ui->lineEdit_2->text().toInt();
    int threads = ui->lineEdit_3->text().toInt();
    std::vector<int> numbers = generateInputVector(size, false);
    if(numbers.size() == 0) {
        ui->label2->setText("Tak takhle teda ne.");
        return;
    }
    int result = 0;
//#pragma omp parallel for ordered schedule(dynamic) shared(result) num_threads(threads)
#pragma omp parallel for reduction(+:result) num_threads(threads)
    for(uint i = 0; i < numbers.size(); i++) {
        result += numbers.at(i);
    }
    ui->label2->setText(QString::number(result));
}

