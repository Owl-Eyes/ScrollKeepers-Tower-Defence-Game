#ifndef PDRAGON_H
#define PDRAGON_H

#include "dragon.h"
#include "bullet.h"
#include "scrollgame.h"

#include <QTimer>

class pDragon: public Dragon
{
    Q_OBJECT
public:
    pDragon(QGraphicsItem *parent = 0);

    void shoot();
    int sprite;
    bool targeting;
    bool hatched;

public slots:
    void getTarget();
    void animate();
    void babyDragon();
};

#endif // PDRAGON_H
