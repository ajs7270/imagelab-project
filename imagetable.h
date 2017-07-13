#ifndef IMAGETABLE_H
#define IMAGETABLE_H

#include <QGraphicsView>

class imageTable : public QGraphicsView{


public:
    imageTable(QGraphicsScene *scene, QWidget *parent = Q_NULLPTR);
    ~imageTable();

signals:
    void clicked(QMouseEvent*);

protected:
    void mousePressEvent(QMouseEvent* event);
};

#endif // IMAGETABLE_H
