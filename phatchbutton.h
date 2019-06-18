#ifndef PHATCHBUTTON_H
#define PHATCHBUTTON_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QPixmap>

class pHatchButton: public QGraphicsPixmapItem
{
public:
    pHatchButton(QGraphicsItem *parent = 0);

    void mousePressEvent(QGraphicsSceneMouseEvent *e);
};
#endif // PHATCHBUTTON_H
