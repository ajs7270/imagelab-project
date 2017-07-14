#include "pixmapitem.h"
#include "CImg.h"
#include <iostream>
#include "contour_cimg.cpp"
PixmapItem::PixmapItem(QGraphicsPixmapItem *parent)
    : QGraphicsPixmapItem(parent)
{ 
}


void PixmapItem::mousePressEvent(QGraphicsSceneMouseEvent *event){
    Q_UNUSED(event)
    qDebug("mouse Press");
    std::cout<<"x point : " << event->pos().x() << ",y point : " << event->pos().y() << std::endl;
}
\
void PixmapItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    Q_UNUSED(event)
    qDebug("mouse Move");
    std::cout<<"x point : " << event->pos().x() << ",y point : " << event->pos().y() << std::endl;
}

void PixmapItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    Q_UNUSED(event)
    qDebug("mouse Release");
    std::cout<<"x point : " << event->pos().x() << ",y point : " << event->pos().y() << std::endl;
}


PixmapItem::~PixmapItem(){

}
