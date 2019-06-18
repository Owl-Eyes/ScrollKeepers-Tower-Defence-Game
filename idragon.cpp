#include "idragon.h"

extern scrollgame *game;

iDragon::iDragon(QGraphicsItem *parent)
{
    hatched = false;
    targeting = false;

    //init graphics
    QPixmap e(":/img/AllySet.png");
    QPixmap iegg = e.copy(350,420,22,31);
    setPixmap(QPixmap (iegg));

    QTimer::singleShot(8000, this, SLOT(babyDragon()));

    connect(game->animationtimer, SIGNAL(timeout()), this, SLOT(animate()));

}

void iDragon::shoot()
{
    //init graphics
    QPixmap b(":/img/AllySet.png");
    QPixmap ibullet = b.copy(280,420,30,24);

    //Bullets
    Bullet *bullet = new Bullet();
    bullet->setPos(x() + 15, y()+ 30); //where bullet shoots from
    bullet->damage = 5;
    bullet->setPixmap(QPixmap (ibullet));

    QLineF ln(QPointF(x(), y()), targetDest);
    int angle = -1 * ln.angle()*1;        //clockwise

    bullet->setRotation(angle);
    game->scene->addItem(bullet);
}

void iDragon::getTarget()
{
    Dragon::getTarget();
}

void iDragon::animate()
{
    QPixmap e(":/img/AllySet.png");
    QPixmap idragon1 = e.copy(0,420,70,70);
    QPixmap idragon2 = e.copy(70,420,70,70);
    QPixmap idragon3 = e.copy(0,490,70,70);
    QPixmap idragon4 = e.copy(70,490,70,70);

    switch (sprite)
    {
    case 1:
        setPixmap(QPixmap (idragon2));
        sprite = 2;
        break;
    case 2:
        setPixmap(QPixmap (idragon1));
        sprite = 1;
        break;
    case 3:
        setPixmap(QPixmap (idragon4));
        sprite = 4;
        break;
    case 4:
        setPixmap(QPixmap (idragon3));
        sprite = 3;
        break;
    }


}

void iDragon::babyDragon()
{
    hatched = true;
    setOffset(-22,-22);
    sprite = 3;
    animate();

    QTimer * targettimer = new QTimer();
    connect(targettimer, SIGNAL(timeout()), this, SLOT(getTarget()));
    targettimer->start(500);
}
