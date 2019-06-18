#include "dragon.h"

#include "scrollgame.h"
#include "enemy.h"
#include "bullet.h"

#include <QVector>
#include <QPointF>
#include <QTimer>
#include <QPolygonF>
#include <QLineF>
#include <QGraphicsPolygonItem>
#include <QPixmap>

extern scrollgame *game;


Dragon::Dragon(QGraphicsItem* parent): QObject(),  QGraphicsPixmapItem(parent)
{
    targeting = false;
    hatched = false;

    //init graphics


    //targeting range
    QVector<QPointF> points;
    points << QPointF(1,0) << QPointF(2,0) << QPointF(3,.5) << QPointF(3,1) << QPointF(2,1.5)
           << QPointF(1,1.5) << QPointF(0,1) << QPointF(0,.5);

    int scalepoints = 80;
    for (int i = 0, n = points.size(); i < n; ++i)
    {
        points[i] *= scalepoints;
    }

    targetrange = new QGraphicsPolygonItem(QPolygonF(points), this);
    targetrange->setPen(QPen(Qt::DashDotDotLine));

    QPointF rangemid(1.5,.5);
    rangemid *= scalepoints;
    rangemid = mapToScene(rangemid);
    QPointF dragmid(x()+35-22, y()+35-22);
    QLineF ln(rangemid, dragmid);
    targetrange->setPos(x()+ln.dx(), y()+ln.dy());



    //timers

    //QTimer::singleShot(5000, this, SLOT(babyDragon()));

    /*if (hatched == true)
    {
        QTimer * targettimer = new QTimer();
        connect(targettimer, SIGNAL(timeout()), this, SLOT(getTarget()));
        targettimer->start(500);
    }*/

    //connect(game->animationtimer, SIGNAL(timeout()), this, SLOT(animate()));
    //connect(elec, &Dragon::shootbullet, this, &scrollgame::sendBullets);
    //connect(game, SIGNAL(game->animatedragon), this, animate());

}

double Dragon::howFar(QGraphicsItem *item)
{
    QLineF ln(pos(), item->pos());
    return ln.length();
}

void Dragon::animate()
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

void Dragon::shoot()
{
    //Bullets
    Bullet *bullet = new Bullet();
    bullet->setPos(x() + 15, y()+ 30); //where bullet shoots from

    QLineF ln(QPointF(x(), y()), targetDest);
    int angle = -1 * ln.angle()*1.15;        //clockwise

    bullet->setRotation(angle);
    game->scene->addItem(bullet);
}

void Dragon::getTarget()
{
    QList<QGraphicsItem *> itemsinrange = targetrange->collidingItems();

    targeting = false;

    double nearestdist = 300;
    QPointF nearestpoint = QPointF(0,0);
    for (size_t i = 0, n = itemsinrange.size(); i < n ; i++)
    {
        Enemy * enemy = dynamic_cast<Enemy *>(itemsinrange[i]);

        if (enemy)
        {
            double tempdist = howFar(enemy);
            if (tempdist < nearestdist)
            {
                nearestdist = tempdist;
                nearestpoint = itemsinrange[i]->pos();
                targeting = true;
            }

        }

    }

    if (targeting)
    {
        targetDest = nearestpoint;
        shoot();
    }

}

void Dragon::babyDragon()
{
    hatched = true;
    setOffset(-22,-22);
    sprite = 3;
    animate();

    //QTimer * targettimer = new QTimer();
    //connect(targettimer, SIGNAL(timeout()), this, SLOT(getTarget()));
    //targettimer->start(500);
}

/*void Dragon::faceDirection(QPointF p)
{
    //if (nextdirection->x() < currentdirection)
    //sprite = 3;
    //if (nextdirection->x() > currentdirection)
    //sprite = 1;
}*/


