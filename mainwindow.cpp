#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clickablelabel.h"
#include <iostream>
#include <string>
#include <QLabel>
#include <QGridLayout>
#include <QGraphicsPixmapItem>

using std::string;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    string filePath = "";


    ui->setupUi(this);






    scene = new QGraphicsScene(this);
    scene2 = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView_2->setScene(scene2);
    defaultImage = new QGraphicsPixmapItem();
    contourImage = new QGraphicsPixmapItem();
    scene->addItem(defaultImage);
    scene2->addItem(contourImage);

    //create graphic image procceing


 //   scene.addItem(&item);
  //      view.show();

    //creates our new model and populate
    mPath = "C:/";
    dirModel = new QFileSystemModel(this);

    //set filter


    dirModel->setFilter(QDir::NoDotAndDotDot|QDir::AllEntries);

    // QFIleSystemModel requires root path
    dirModel->setRootPath(mPath);

    //filter the directory to show image files
    QStringList filters;
    filters << "*.png","*.jpeg","*.jpg";

   // dirModel->setNameFilters(filters);
   // dirModel->setNameFilterDisables(false);

    ui->treeView->setModel(dirModel);






}

MainWindow::~MainWindow()
{
    delete ui;
}





void MainWindow::on_pushButton_4_clicked()
{   
    std::cout<< mPath.toStdString()<<std::endl;
    string filePath = mPath.toStdString();

    //image open on label
    QPixmap pix = QPixmap(filePath.c_str());
    ui->label->setPixmap(pix);

    //iamge open on grapicView
    defaultImage->setPixmap(pix);
    contourImage->setPixmap(pix);
   // contourImage->moveBy(pix.width(),0);

}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    mPath = dirModel->fileInfo(index).absoluteFilePath();
}

void MainWindow::on_label_clicked(QMouseEvent* event)
{
    std::cout << "label clicked!" << event->x() << ", " << event->y() << std::endl;
}
