#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "CImg.h"
//#include "contour_cimg.cpp"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //creates our new model and populate
    mPath = "C:/";
    dirModel = new QFileSystemModel(this);

    //set filter
    //dirModel = new RootFileSysProxyModel(new QFileSystemModel, "/", this);

    dirModel->setFilter(QDir::NoDotAndDotDot|QDir::AllEntries);

    // QFIleSystemModel requires root path
    dirModel->setRootPath(mPath);

    //Attach the model to the view
    QStringList filters;
 //  filters << "*.jpg";
 //   dirModel->setNameFilters(filters);
 //   dirModel->setNameFilterDisables(false);

    ui->treeView->setModel(dirModel);




    //FILES

    //fileModel = new QFileSystemModel(this);


    //set filter
   // fileModel->setFilter(QDir::NoDotAndDotDot|QDir::Files);


    //QFileSystemModel requires root path
    //fileModel->setRootPath(mPath);


    //Attach the model to the view


   // ui->listView->setModel(fileModel);

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
