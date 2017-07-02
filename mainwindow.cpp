#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //creates our new model and populate
    QString mPath = "C:/";
    dirModel = new QFileSystemModel(this);

    //set filter
    dirModel->setFilter(QDir::NoDotAndDotDot|QDir::AllDirs);

    // QFIleSystemModel requires root path
    dirModel->setRootPath(mPath);

    //Attach the model to the view
    ui->treeView->setModel(dirModel);

    //FILES

    fileModel = new QFileSystemModel(this);

    //set filter
    fileModel->setFilter(QDir::NoDotAndDotDot|QDir::AllDirs);

    //QFileSystemModel requires root path
    fileModel->setRootPath(mPath);

    //Attach the model to the view
    ui->listView->setModel(fileModel);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    // TreeView clicked
    // 1. We need to extract path
    // 2. Set that path into our ListView

    // Get the full path of the item that's user clicked
    QString mPath = dirModel->fileInfo(index).absoluteFilePath();
    ui->listView->setRootIndex(fileModel->setRootPath(mPath));
}
