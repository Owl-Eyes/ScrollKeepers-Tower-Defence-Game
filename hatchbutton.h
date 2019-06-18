#ifndef HATCHBUTTON_H
#define HATCHBUTTON_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QPixmap>

class HatchButton: public QGraphicsPixmapItem
{
public:
    HatchButton(QGraphicsItem *parent = 0);

    void mousePressEvent(QGraphicsSceneMouseEvent *e);
};

#endif // HATCHBUTTON_H
