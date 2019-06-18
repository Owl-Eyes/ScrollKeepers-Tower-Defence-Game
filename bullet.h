#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>

class Bullet: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Bullet(QGraphicsItem *parent = 0);
    int damage;

public slots:

    void move();

private:
    bool hit;
    double range;
    double disttravelled;

private slots:
    void checkIfHit();

};

#endif // BULLET_H
