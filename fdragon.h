#ifndef FDRAGON_H
#define FDRAGON_H

#include "dragon.h"
#include "bullet.h"
#include "scrollgame.h"

#include <QTimer>

class fDragon: public Dragon
{
    Q_OBJECT
public:
    fDragon(QGraphicsItem *parent = 0);

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


#endif // FDRAGON_H
