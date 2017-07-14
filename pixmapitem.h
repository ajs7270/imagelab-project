#ifndef PIXMAPITEM_H
#define PIXMAPITEM_H
#include<QGraphicsItem>
#include<QGraphicsSceneMouseEvent>
#include <QDebug>
#include "CImg.h"

class PixmapItem : public QGraphicsPixmapItem
{
public:
    PixmapItem(QGraphicsPixmapItem *parent = Q_NULLPTR);
    ~PixmapItem();

    void setCImg();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif // PIXMAPITEM_H
