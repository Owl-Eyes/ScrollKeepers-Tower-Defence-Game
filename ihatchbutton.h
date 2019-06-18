#ifndef IHATCHBUTTON_H
#define IHATCHBUTTON_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QPixmap>

class iHatchButton: public QGraphicsPixmapItem
{
public:
    iHatchButton(QGraphicsItem *parent = 0);

    void mousePressEvent(QGraphicsSceneMouseEvent *e);
};

#endif // IHATCHBUTTON_H
