#include "bullet.h"
#include "scrollgame.h"
#include "dragon.h"
#include "enemy.h"

#include <QPixmap>
#include <QTimer>
#include <qmath.h>

//class Enemy;

extern scrollgame *game;

Bullet::Bullet(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent)
{
    // Initialise
    setOffset(22,22);
    damage = 0;
    disttravelled = 0;
    range = 120;

    QTimer *bulletmovetimer = new QTimer(this);
    connect(bulletmovetimer, SIGNAL(timeout()), this, SLOT(move()));
    connect(bulletmovetimer, SIGNAL(timeout()), this, SLOT(checkIfHit()));
    bulletmovetimer->start(100);

}

void Bullet::move()
{
    int movesize = 30;
    double theta = rotation();

    double dx = movesize * qCos(qDegreesToRadians(theta));
    double dy = movesize * qSin(qDegreesToRadians(theta));

    setPos(x() + dx, y() + dy);
    disttravelled += movesize;

    if (disttravelled >= range)
    {
        deleteLater();
    }

}

void Bullet::checkIfHit()
{
    QList<QGraphicsItem *> itemsinrange = collidingItems();

    hit = false;

    for (size_t i = 0, n = itemsinrange.size(); i < n ; i++)
    {
        Enemy * enemy = dynamic_cast<Enemy *>(itemsinrange[i]);

        if (enemy)
        {
            hit = true;
            enemy->health = enemy->health-damage;

            if (enemy->health <= 0)
            {
                game->chrystals += 1;
                if (enemy->scene() != NULL)
                {
                    game->scene->removeItem(enemy);
                }
                enemy->deleteLater();
            }
            if (scene() != NULL)
            {
                game->scene->removeItem(this);
            }
            deleteLater();

        }
    }

    //    QList<QGraphicsPixmapItem *> edgesinrange = collidingItems();

    //    for (size_t i = 0, n = itemsinrange.size(); i < n ; i++)
    //    {
    //        if (edgesinrange[i] == game->m)
    //        {
    //            deleteLater();
    //        }
    //    }

}

