#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <QGridLayout>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <iostream>


using std::string;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    string filePath = "";

    //ready to open image
    defaultScene = new QGraphicsScene(this);
    contourScene = new QGraphicsScene(this);
    ui->defaultGraphicsView->setScene(defaultScene);
    ui->contourGraphicsView->setScene(contourScene);
    defaultImage = new PixmapItem();
    contourImage = new  QGraphicsPixmapItem();
    defaultScene->addItem(defaultImage);
    contourScene->addItem(contourImage);
    contour = &defaultImage->contour;

    //share contourScence with defaultScene
    defaultImage->setContourScene(contourScene);

    //creates our new model and populate
    mPath = "C:/";
    dirModel = new QFileSystemModel(this);
    ui->treeView->setModel(dirModel);
    ui->treeView->setHeaderHidden(true);
    for(int i = 3;i>0;i--){
        ui->treeView->hideColumn(i);
    }

    // QFIleSystemModel requires root path
    dirModel->setRootPath(mPath);

    //set filter
    dirModel->setFilter(QDir::NoDotAndDotDot|QDir::AllEntries);


    /*
    //filter the directory to show image files
    QStringList filters;
    filters << "*.png","*.jpeg","*.jpg";
    dirModel->setNameFilters(filters);
    dirModel->setNameFilterDisables(false);
    */


}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    //renew filePath
    mPath = dirModel->fileInfo(index).absoluteFilePath();


}




void MainWindow::on_openButton_clicked()
{





    string filePath = mPath.toStdString();
    defaultImage->setCImg(mPath);

    defaultPix = new QPixmap(filePath.c_str());
    //image open on grapicView
    defaultImage->setPixmap(*defaultPix);
    contourScene->clear();
    contourScene->addPixmap(*defaultPix);
    defaultImage->setImage(defaultPix);




}

void MainWindow::on_enlargementButton_clicked()
{
   defaultImage->setScale(1.25 * defaultImage->scale());
   contourImage->setScale(defaultImage->scale());

}

void MainWindow::on_reductionButton_clicked()
{
defaultImage->setScale(0.8 * defaultImage->scale());
contourImage->setScale(defaultImage->scale());
}
