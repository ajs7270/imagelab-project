#ifndef PIXMAPITEM_H
#define PIXMAPITEM_H
#include<QGraphicsItem>
#include<QGraphicsScene>
#include<QGraphicsSceneMouseEvent>
#include<QGraphicsLineItem>
#include <string>
#include <QDebug>
#include <vector>
#include "CImg.h"
#include <QPen>

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
    QGraphicsScene *contourScene;

    void setCImg(QString path);
    void setContourScene(QGraphicsScene *contourScene);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
private:
    int contourIndex;
    QGraphicsLineItem *line;




};

#endif // PIXMAPITEM_H
