#include "pdragon.h"

extern scrollgame *game;

pDragon::pDragon(QGraphicsItem *parent)
{
    hatched = false;
    targeting = false;

    //init graphics
    QPixmap e(":/img/AllySet.png");
    QPixmap pegg = e.copy(350,140,22,31);
    setPixmap(QPixmap (pegg));

    QTimer::singleShot(5000, this, SLOT(babyDragon()));

    connect(game->animationtimer, SIGNAL(timeout()), this, SLOT(animate()));

}

void pDragon::shoot()
{
    //init graphics
    QPixmap b(":/img/AllySet.png");
    QPixmap pbullet = b.copy(280,140,22,24);

    //Bullets
    Bullet *bullet = new Bullet();
    bullet->setPos(x() + 15, y()+ 30); //where bullet shoots from
    bullet->setPixmap(QPixmap (pbullet));
    bullet->damage = 2;

    QLineF ln(QPointF(x(), y()), targetDest);
    int angle = -1 * ln.angle()*1.15;        //clockwise

    bullet->setRotation(angle);
    game->scene->addItem(bullet);
}

void pDragon::getTarget()
{
    Dragon::getTarget();
}

void pDragon::animate()
{
    QPixmap e(":/img/AllySet.png");
    QPixmap pdragon1 = e.copy(0,140,70,70);
    QPixmap pdragon2 = e.copy(70,140,70,70);
    QPixmap pdragon3 = e.copy(0,210,70,70);
    QPixmap pdragon4 = e.copy(70,210,70,70);

    switch (sprite)
    {
    case 1:
        setPixmap(QPixmap (pdragon2));
        sprite = 2;
        break;
    case 2:
        setPixmap(QPixmap (pdragon1));
        sprite = 1;
        break;
    case 3:
        setPixmap(QPixmap (pdragon4));
        sprite = 4;
        break;
    case 4:
        setPixmap(QPixmap (pdragon3));
        sprite = 3;
        break;
    }


}

void pDragon::babyDragon()
{
    hatched = true;
    setOffset(-22,-22);
    sprite = 3;
    animate();

    QTimer * targettimer = new QTimer();
    connect(targettimer, SIGNAL(timeout()), this, SLOT(getTarget()));
    targettimer->start(500);
}

