#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "CImg/CImg.h"
//#include "contour_cimg.cpp"

using namespace cimg_library;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    CImg<unsigned char> image("lena.jpg"), visu(500,400,1,3,0);
      const unsigned char red[] = { 255,0,0 }, green[] = { 0,255,0 }, blue[] = { 0,0,255 };
      image.blur(2.5);
      CImgDisplay main_disp(image,"Click a point"), draw_disp(visu,"Intensity profile");
      while (!main_disp.is_closed() && !draw_disp.is_closed()) {
        main_disp.wait();
        if (main_disp.button() && main_disp.mouse_y()>=0) {
          const int y = main_disp.mouse_y();
          visu.fill(0).draw_graph(image.get_crop(0,y,0,0,image.width()-1,y,0,0),red,1,1,0,255,0);
          visu.draw_graph(image.get_crop(0,y,0,1,image.width()-1,y,0,1),green,1,1,0,255,0);
          visu.draw_graph(image.get_crop(0,y,0,2,image.width()-1,y,0,2),blue,1,1,0,255,0).display(draw_disp);
          }
        }

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
