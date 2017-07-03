#include "treemodel.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    QString sPath = "C:/";
    dirmodel =new QFileSystemModel(this);
    dirmodel->setRootPath(sPath);
    ui->treeView->setModel(dirmodel);

    ui->treeView->setModel(dirmodel);
}

Dialog::~Dialog()
{
    delete ui;
}
