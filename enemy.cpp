#include "enemy.h"
#include "scrollgame.h"
#include "bullet.h"

#include <QTimer>
#include <QGraphicsRectItem>
#include <QPixmap>

extern scrollgame *game;

Enemy::Enemy(QGraphicsItem* parent): QObject(),  QGraphicsPixmapItem(parent)
{
    //init graphics
    sprite = 1;

    //connect(game->eanimationtimer, &QTimer::timeout, this, &Enemy::animate);

    connect(game->eanimationtimer, &QTimer::timeout, this, &Enemy::move);

    hit = false;
    health = 4;
    damage = 1;

}

void Enemy::assignPath(QVector<QPointF> v)
{
    path = v;
    pathindex = path.size() -1;
    nextdest = path[pathindex];
}

void Enemy::animate()
{
    if (game->changed == 0)               //bird
    {
        QPixmap b(":/img/EnemySet.png");
        QPixmap bshadow1 = b.copy(0,0,64,64);
        QPixmap bshadow2 = b.copy(64,0,64,64);
        QPixmap bshadow3 = b.copy(0,64,64,64);
        QPixmap bshadow4 = b.copy(64,64,64,64);

        switch (sprite)
        {
        case 1:
            setPixmap(QPixmap (bshadow2));
            sprite = 2;
            break;
        case 2:
            setPixmap(QPixmap (bshadow1));
            sprite = 1;
            break;
        case 3:
            setPixmap(QPixmap (bshadow4));
            sprite = 4;
            break;
        case 4:
            setPixmap(QPixmap (bshadow3));
            sprite = 3;
            break;
        }
    }

    if (game->changed == 1)   //dog
    {
        QPixmap b(":/img/EnemySet.png");
        QPixmap dshadow1 = b.copy(0,128,64,64);
        QPixmap dshadow2 = b.copy(64,128,64,64);
        QPixmap dshadow3 = b.copy(0,192,64,64);
        QPixmap dshadow4 = b.copy(64,192,64,64);

        switch (sprite)
        {
        case 1:
            setPixmap(QPixmap (dshadow2));
            sprite = 2;
            break;
        case 2:
            setPixmap(QPixmap (dshadow1));
            sprite = 1;
            break;
        case 3:
            setPixmap(QPixmap (dshadow4));
            sprite = 4;
            break;
        case 4:
            setPixmap(QPixmap (dshadow3));
            sprite = 3;
            break;
        }
    }

    if (game->changed == 2)              //deer
    {
        QPixmap b(":/img/EnemySet.png");
        QPixmap lshadow1 = b.copy(0,256,70,94);
        QPixmap lshadow2 = b.copy(70,256,70,94);
        QPixmap lshadow3 = b.copy(0,350,70,94);
        QPixmap lshadow4 = b.copy(70,350,70,94);

        switch (sprite)
        {
        case 1:
            setPixmap(QPixmap (lshadow2));
            sprite = 2;
            break;
        case 2:
            setPixmap(QPixmap (lshadow1));
            sprite = 1;
            break;
        case 3:
            setPixmap(QPixmap (lshadow4));
            sprite = 4;
            break;
        case 4:
            setPixmap(QPixmap (lshadow3));
            sprite = 3;
            break;
        }
    }


}

void Enemy::move()
{
    //setPos(x() + 10, y() + 5);

//    if (pathindex >= 0)
//    {
//        int nextx = nextdest.x();
//        int nexty = nextdest.y();

//        QPointF nextxy = xypoint(nextx, nexty);

////        while (seminextpoint.x() < nextxy.x())
////        {
////            QPointF seminextpoint = (nextxy.x()+nextxy.x()*.01, nextxy.y()+nextxy.y()*.01);
////            setPos(seminextpoint);
////        }
//        setPos(nextxy);

//        nextdest = path[--pathindex];
//    }
//    else
//    {
//        deleteLater();
//    }


    if(pathindex != 0)
        {

          //int changedir = 0;
          int nextx = nextdest.x();
          int nexty = nextdest.y();

          QPointF nextxy = xypoint(nextx, nexty);

          int dx = (nextxy.x() - x())*12; //*16?
          int dy = (nextxy.y() - y())*12;

          if (dx == 0)
          {
              movex = 0;
          }
          else
          {
              movex = 10*dx/abs(dx);
          }

          if (dy == 0)
          {
              movey = 0;
          }
          else
          {
              movey = 5*dy/abs(dy);
          }

          //animate sprite
//          if (movex > 0)
//          {
//              changedir = 0;
//              if (sprite = 3)
//                  sprite = 4;
//              else
//                  sprite = 3;
//          }
//          else changedir = 1;

//          if (changedir == 1)
//          {

//              sprite = 3;
//              changedir = 0;
//          }


          //animate();

          setPos(x() + movex,y() + movey);

          if (sqrt(pow(dx,2) + pow(dy, 2)) <= 150) //c^2 = a^2 + b^2 72?
          {
              nextdest = path[--pathindex];
          }

          animate();

        }
        else
        {
          deleteLater();
          game->scrollsleft -= damage;
          game->refreshResources();
        }

}

QPointF Enemy::xypoint(int i, int j)
{
    tempnextx = i;
    tempnexty = j;
    int x = (j * game->tileX / 2 + i * game->tileX / 2) - 100;
    int y = (j * 32 / 2 - i * 32 / 2 + (game->mapY-15) * 32) - 20;
    return QPointF(x,y);
}

//void Enemy::faceDirection(QPointF p)
//{
    //if (nextdirection->x() < currentdirection)
    //sprite = 3;
    //if (nextdirection->x() > currentdirection)
    //sprite = 1;
//}

