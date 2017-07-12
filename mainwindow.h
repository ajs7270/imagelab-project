#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QSortFilterProxyModel>
#include <QtOpenGL/QtOpenGL>

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



    void on_pushButton_4_clicked();

    void on_treeView_clicked(const QModelIndex &index);

    void on_label_clicked(QMouseEvent*);

private:
    Ui::MainWindow *ui;
    QFileSystemModel *dirModel;
    QFileSystemModel *fileModel;
    QSortFilterProxyModel *proxy_model;
};

#endif // MAINWINDOW_H
