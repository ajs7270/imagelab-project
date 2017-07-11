#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //creates our new model and populate
    mPath = "C:/";
    dirModel = new QFileSystemModel(this);

    //set filter


    dirModel->setFilter(QDir::NoDotAndDotDot|QDir::AllEntries);

    // QFIleSystemModel requires root path
    dirModel->setRootPath(mPath);

    //filter the directory to show image files
    QStringList filters;
    filters << "*.png";

    dirModel->setNameFilters(filters);
    dirModel->setNameFilterDisables(false);

    ui->treeView->setModel(dirModel);






}

MainWindow::~MainWindow()
{
    delete ui;
}





void MainWindow::on_pushButton_4_clicked()
{
    std::cout<< mPath.toStdString()<<std::endl;
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    mPath = dirModel->fileInfo(index).absoluteFilePath();
}
