#ifndef ENEMY_H
#define ENEMY_H

#include "scrollgame.h"

#include <QGraphicsPolygonItem>
#include <QVector>
#include <QPoint>
#include <QGraphicsItem>
#include <QTimer>
#include <QObject>

extern scrollgame *game;

class Enemy : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Enemy(QGraphicsItem* parent = 0);

    int health;
    int damage;

    double movex;
    double movey;
    double tempnextx;
    double tempnexty;

    void assignPath(QVector<QPointF> v);
    QVector<QPointF> path;
    int pathindex;
    QPointF nextdest;

    //QTimer *eanimationtimer;

public slots:
    void animate();
    void move();
 // void faceDirection(QPointF p);

private:
    int sprite;
    bool hit;
    //QTimer *checkalivetimer;

    QPointF xypoint(int i, int j);

signals:
    void loss();

};

#endif // ENEMY_H
