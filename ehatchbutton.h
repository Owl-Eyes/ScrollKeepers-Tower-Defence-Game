#ifndef HATCHBUTTON_H
#define HATCHBUTTON_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QPixmap>

class eHatchButton: public QGraphicsPixmapItem
{
public:
    eHatchButton(QGraphicsItem *parent = 0);

    void mousePressEvent(QGraphicsSceneMouseEvent *e);
};

#endif // HATCHBUTTON_H
