#ifndef IDRAGON_H
#define IDRAGON_H

#include "dragon.h"
#include "bullet.h"
#include "scrollgame.h"

#include <QTimer>

class iDragon: public Dragon
{
    Q_OBJECT
public:
    iDragon(QGraphicsItem *parent = 0);

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

#endif // IDRAGON_H
