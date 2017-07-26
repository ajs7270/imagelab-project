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

void PixmapItem::setContourScene(QGraphicsScene *contourScene){
    this->contourScene=contourScene;
}

void PixmapItem::setImage(QPixmap *image){
    this->image = image;
}


void PixmapItem::mousePressEvent(QGraphicsSceneMouseEvent *event){
    Q_UNUSED(event)
    qDebug("mouse Press");
    contourScene->clear();
    contourScene->addPixmap(*image);
    cout<<"x point : " << event->pos().toPoint().x() << ",y point : " << event->pos().y() << endl;
    contourIndex = cal_isocontour(*im,(double)event->pos().toPoint().x(), (double)event->pos().toPoint().y(), contour);

    qreal X1,X2,Y1,Y2;
    QPen pen(Qt::green, 3, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);

    if(contour.size()>1){
         for(int i=0;i<contour.size()-1;i++){
             X1=contour.at(i).x;
             X2=contour.at(i+1).x;
             Y1=contour.at(i).y;
             Y2=contour.at(i+1).y;

             contourScene->addLine(X1,Y1,X2,Y2,pen);
          }
     }

    //
}
\
void PixmapItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    Q_UNUSED(event)
    qDebug("mouse Move");
    contourScene->clear();
    contourScene->addPixmap(*image);
    std::cout<<"x point : " << event->pos().x() << ",y point : " << event->pos().y() << std::endl;
    contourIndex = cal_isocontour(*im,(double)event->pos().toPoint().x(), (double)event->pos().toPoint().y(), contour);

    qreal X1,X2,Y1,Y2;
    QPen pen(Qt::green, 3, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);

    if(contour.size()>1){
         for(int i=0;i<contour.size()-1;i++){
             X1=contour.at(i).x;
             X2=contour.at(i+1).x;
             Y1=contour.at(i).y;
             Y2=contour.at(i+1).y;

             contourScene->addLine(X1,Y1,X2,Y2,pen);
          }
     }
    //
}

void PixmapItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    Q_UNUSED(event)
    qDebug("mouse Release");
    contourScene->addPixmap(*image);
    std::cout<<"x point : " << event->pos().x() << ",y point : " << event->pos().y() << std::endl;
    contourIndex = cal_isocontour(*im,(double)event->pos().toPoint().x(), (double)event->pos().toPoint().y(), contour);
    //
    qreal X1,X2,Y1,Y2;
    QPen pen(Qt::green, 3, Qt::DashDotLine, Qt::RoundCap, Qt::RoundJoin);

    if(contour.size()>1){
         for(int i=0;i<contour.size()-1;i++){
             X1=contour.at(i).x;
             X2=contour.at(i+1).x;
             Y1=contour.at(i).y;
             Y2=contour.at(i+1).y;

             contourScene->addLine(X1,Y1,X2,Y2,pen);
          }
     }
}


PixmapItem::~PixmapItem(){

}
