#ifndef DRAGON_H
#define DRAGON_H

#include "scrollgame.h"

#include <QGraphicsPolygonItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QPointF>
#include <QTimer>
#include <QObject>



class Dragon : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Dragon(QGraphicsItem * parent = 0);
    double howFar(QGraphicsItem *item);
    int sprite;
    bool hatched;
    bool targeting;

    virtual void shoot();
    QPointF targetDest;

public slots:
    void animate();
    void getTarget();
    //void faceDirection(QPointF p);

private:

    QTimer *targettimer;
    QTimer *eggttimer;

    QGraphicsPolygonItem * targetrange;

private slots:
    void babyDragon();


protected:

};

#endif // DRAGON_H
