#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QDialog>
#include <Qtcore>
#include <QtGui>
#include <QFileSystemModel>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    Ui::Dialog *ui;
    QFileSystemModel *dirmodel;
    QFileSystemModel *filemodel;
};

#endif // TREEMODEL_H
