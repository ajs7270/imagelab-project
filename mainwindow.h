#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QSortFilterProxyModel>
#include <QtOpenGL/QtOpenGL>
#include <QGraphicsScene>
#include "pixmapitem.h"
#include <QGraphicsPixmapItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);\
    QString mPath;
    ~MainWindow();

private slots:

    void on_treeView_clicked(const QModelIndex &index); 
    void on_openButton_clicked();
    void on_enlargementButton_clicked();
    void on_reductionButton_clicked();

private:
    Ui::MainWindow *ui;
    QFileSystemModel *dirModel;
    QSortFilterProxyModel *proxy_model;
    QGraphicsScene *defaultScene;
    QGraphicsScene *contourScene;
    PixmapItem *defaultImage;
    QGraphicsPixmapItem *contourImage;
};

#endif // MAINWINDOW_H
