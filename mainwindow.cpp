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

    //conncet contour
    contour = &defaultImage->contour;

    //creates our new model and populate
    mPath = "C:/";
    dirModel = new QFileSystemModel(this);
    ui->treeView->setModel(dirModel);

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


/*
void MainWindow::on_label_clicked(QMouseEvent* event)
{
    std::cout << "label clicked!" << event->x() << ", " << event->y() << std::endl;
}
*/


void MainWindow::on_openButton_clicked()
{

    string filePath = mPath.toStdString();
    defaultImage->setCImg(mPath);

    QPixmap defaultPix = QPixmap(filePath.c_str());
    QPixmap contourPix = QPixmap(filePath.c_str());
    //iamge open on grapicView
    defaultImage->setPixmap(defaultPix);
    contourImage->setPixmap(contourPix);

    /*
    //image open on label
    ui->label->setPixmap(pix);
    */
}

void MainWindow::on_enlargementButton_clicked()
{
    for(int i = 0;i<contour->size();i++){
        std::cout << contour->at(i).x << "," << contour->at(i).y<<std::endl;
    }

}

void MainWindow::on_reductionButton_clicked()
{

}
