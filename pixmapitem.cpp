#include "pixmapitem.h"
#include <iostream>
#include "contour_cimg.cpp"

using namespace cimg_library;
using namespace std;

PixmapItem::PixmapItem(QGraphicsPixmapItem *parent)
    : QGraphicsPixmapItem(parent)
{ 
}
void PixmapItem::setCImg(QString path){

    QByteArray filepath = path.toLocal8Bit();
    im = new CImg<double>(filepath.data());
}


void PixmapItem::mousePressEvent(QGraphicsSceneMouseEvent *event){
    Q_UNUSED(event)
    qDebug("mouse Press");
    cout<<"x point : " << event->pos().toPoint().x() << ",y point : " << event->pos().y() << endl;
    contourIndex = cal_isocontour(*im,(double)event->pos().toPoint().x(), (double)event->pos().toPoint().y(), contour);
    for(int i =0;i<contour.size();i++){
        cout << "x point : " << contour.at(i).x <<",y point : "<< contour.at(i).y<<endl;
    }

    //
}
\
void PixmapItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    Q_UNUSED(event)
    qDebug("mouse Move");
    std::cout<<"x point : " << event->pos().x() << ",y point : " << event->pos().y() << std::endl;
    contourIndex = cal_isocontour(*im,(double)event->pos().toPoint().x(), (double)event->pos().toPoint().y(), contour);
    //
}

void PixmapItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    Q_UNUSED(event)
    qDebug("mouse Release");
    std::cout<<"x point : " << event->pos().x() << ",y point : " << event->pos().y() << std::endl;
    contourIndex = cal_isocontour(*im,(double)event->pos().toPoint().x(), (double)event->pos().toPoint().y(), contour);
    //
}


PixmapItem::~PixmapItem(){

}
