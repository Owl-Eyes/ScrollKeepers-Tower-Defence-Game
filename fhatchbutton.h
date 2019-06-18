#ifndef FHATCHBUTTON_H
#define FHATCHBUTTON_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QPixmap>

class fHatchButton: public QGraphicsPixmapItem
{
public:
    fHatchButton(QGraphicsItem *parent = 0);

    void mousePressEvent(QGraphicsSceneMouseEvent *e);
};

#endif // FHATCHBUTTON_H
