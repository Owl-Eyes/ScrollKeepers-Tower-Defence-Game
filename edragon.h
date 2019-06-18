#ifndef EDRAGON_H
#define EDRAGON_H

#include "dragon.h"
#include "bullet.h"
#include "scrollgame.h"

#include <QTimer>

class eDragon: public Dragon
{
    Q_OBJECT
public:
    eDragon(QGraphicsItem *parent = 0);

    void shoot();
    int sprite;
    bool targeting;
    bool hatched;

private:
    QTimer *targettimer;

public slots:
    void getTarget();
    void animate();
    void babyDragon();

};

#endif // EDRAGON_H
