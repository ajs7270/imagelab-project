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
    cimg_library::CImg<double> *im = NULL;
    QGraphicsScene *contourScene;

    void setCImg(QString path);
    void setContourScene(QGraphicsScene *contourScene);
    void setImage(QPixmap *image);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
private:
    int contourIndex;
    QGraphicsLineItem *line;
    QPixmap *image;




};

#endif // PIXMAPITEM_H
