#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <string>
#include <QGridLayout>
#include <QGraphicsPixmapItem>

using std::string;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    string filePath = "";

    //ready to open image
    scene = new QGraphicsScene(this);
    scene2 = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView_2->setScene(scene2);
    defaultImage = new QGraphicsPixmapItem();
    contourImage = new QGraphicsPixmapItem();
    scene->addItem(defaultImage);
    scene2->addItem(contourImage);


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
    std::cout<< mPath.toStdString()<<std::endl;
    string filePath = mPath.toStdString();
    QPixmap pix = QPixmap(filePath.c_str());

    //iamge open on grapicView
    defaultImage->setPixmap(pix);
    contourImage->setPixmap(pix);

    /*
    //image open on label
    ui->label->setPixmap(pix);
    */
}



