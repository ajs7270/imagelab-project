#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <QGridLayout>
#include <QGraphicsPixmapItem>
#include <QDebug>


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
    QPixmap *oriDefault = NULL;
    QPixmap *oriContour = NULL;

    if(defaultPix){
       oriDefault = defaultPix;
       oriContour = contourPix;
    }

    defaultPix = new QPixmap(filePath.c_str());
    contourPix = new QPixmap(filePath.c_str());
    //image open on grapicView
    defaultImage->setPixmap(*defaultPix);
    contourImage->setPixmap(*contourPix);
    defaultImage->setImage(defaultPix);

    if(oriDefault){
        delete(oriDefault);
        delete(oriContour);
    }

    /*
    //image open on label
    ui->label->setPixmap(pix);
    */
}

void MainWindow::on_enlargementButton_clicked()
{

}

void MainWindow::on_reductionButton_clicked()
{

}
