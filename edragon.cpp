#include "edragon.h"


extern scrollgame *game;

eDragon::eDragon(QGraphicsItem *parent)
{
    hatched = false;
    targeting = false;

    //init graphics
    QPixmap e(":/img/AllySet.png");
    QPixmap eegg = e.copy(350,0,22,31);
    setPixmap(QPixmap (eegg));

    QTimer::singleShot(3000, this, SLOT(babyDragon()));

    connect(game->animationtimer, SIGNAL(timeout()), this, SLOT(animate()));

}

void eDragon::shoot()
{
    //init graphics
    QPixmap b(":/img/AllySet.png");
    QPixmap ebullet = b.copy(280,0,22,24);

    //Bullets
    Bullet *bullet = new Bullet();
    bullet->setPos(x() + 15, y()+ 30); //where bullet shoots from
    bullet->damage = 1;
    bullet->setPixmap(QPixmap (ebullet));

    QLineF ln(QPointF(x(), y()), targetDest);
    int angle = -1 * ln.angle()*1.15;        //clockwise

    bullet->setRotation(angle);
    game->scene->addItem(bullet);
}

void eDragon::getTarget()
{
    Dragon::getTarget();
}

void eDragon::animate()
{
    QPixmap e(":/img/AllySet.png");
    QPixmap edragon1 = e.copy(0,0,70,70);
    QPixmap edragon2 = e.copy(70,0,70,70);
    QPixmap edragon3 = e.copy(0,70,70,70);
    QPixmap edragon4 = e.copy(70,70,70,70);

    switch (sprite)
    {
    case 1:
        setPixmap(QPixmap (edragon2));
        sprite = 2;
        break;
    case 2:
        setPixmap(QPixmap (edragon1));
        sprite = 1;
        break;
    case 3:
        setPixmap(QPixmap (edragon4));
        sprite = 4;
        break;
    case 4:
        setPixmap(QPixmap (edragon3));
        sprite = 3;
        break;
    }


}

void eDragon::babyDragon()
{
    hatched = true;
    setOffset(-22,-22);
    sprite = 3;
    animate();

    QTimer * targettimer = new QTimer();
    connect(targettimer, SIGNAL(timeout()), this, SLOT(getTarget()));
    targettimer->start(500);
}
