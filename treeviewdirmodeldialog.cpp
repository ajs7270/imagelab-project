#include "treeviewdirmodeldialog.h"
#include "ui_treeviewdirmodeldialog.h"

TreeViewDirModelDialog::TreeViewDirModelDialog(QWidget *pQDialog(parent),
                                               ui(new Ui::TreeViewDirModelDialog)
{
ui->setupUi(this);
                                                  model =new QDirModel(this);

                                                   model->setReadOnly(false);

                                                   ui->treeView->setModel(model);

}
TreeViewDirModelDialog::~TreeViewDirModelDialog()
{
         delete ui;
}
