#ifndef PIXMAPITEM_H
#define PIXMAPITEM_H
#include<QGraphicsItem>
#include<QGraphicsSceneMouseEvent>
#include <string>
#include <QDebug>
#include <vector>
#include "CImg.h"

struct point {

    double  x;
    double  y;
};


class PixmapItem : public QGraphicsPixmapItem
{
public:
    PixmapItem(QGraphicsPixmapItem *parent = Q_NULLPTR);
    ~PixmapItem();
     std::vector< point > contour;
     cimg_library::CImg<double> *im;
    void setCImg(QString path);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
private:
    int contourIndex;


};

#endif // PIXMAPITEM_H
