#include "fdragon.h"



extern scrollgame *game;

fDragon::fDragon(QGraphicsItem *parent)
{
    hatched = false;
    targeting = false;

    //init graphics
    QPixmap e(":/img/AllySet.png");
    QPixmap fegg = e.copy(350,280,22,31);
    setPixmap(QPixmap (fegg));

    QTimer::singleShot(6000, this, SLOT(babyDragon()));

    connect(game->animationtimer, SIGNAL(timeout()), this, SLOT(animate()));

}

void fDragon::shoot()
{
    //init graphics
    QPixmap b(":/img/AllySet.png");
    QPixmap fbullet = b.copy(280,280,30,24);

    //Bullets
    Bullet *bullet = new Bullet();
    bullet->setPos(x() + 15, y()-5); //where bullet shoots from
    bullet->damage = 1;
    bullet->setPixmap(QPixmap (fbullet));

    QLineF ln(QPointF(x(), y()), targetDest);
    int angle = -1 * ln.angle()*1.1;        //clockwise

    bullet->setRotation(angle);
    game->scene->addItem(bullet);
}

void fDragon::getTarget()
{
    Dragon::getTarget();
}

void fDragon::animate()
{
    QPixmap e(":/img/AllySet.png");
    QPixmap fdragon1 = e.copy(0,210,70,70);
    QPixmap fdragon2 = e.copy(70,210,70,70);
    QPixmap fdragon3 = e.copy(0,350,70,70);
    QPixmap fdragon4 = e.copy(70,350,70,70);

    switch (sprite)
    {
    case 1:
        setPixmap(QPixmap (fdragon2));
        sprite = 2;
        break;
    case 2:
        setPixmap(QPixmap (fdragon1));
        sprite = 1;
        break;
    case 3:
        setPixmap(QPixmap (fdragon4));
        sprite = 4;
        break;
    case 4:
        setPixmap(QPixmap (fdragon3));
        sprite = 3;
        break;
    }


}

void fDragon::babyDragon()
{
    hatched = true;
    setOffset(-22,-22);
    sprite = 3;
    animate();

    QTimer * targettimer = new QTimer();
    connect(targettimer, SIGNAL(timeout()), this, SLOT(getTarget()));
    targettimer->start(300);
}
