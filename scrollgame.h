#ifndef SCROLLGAME_H
#define SCROLLGAME_H

#include "dragon.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QTimer>
#include <QVector>
#include <QMouseEvent>
#include <QtMultimedia/QMediaPlayer>

//#include <QMouseEvent>

class Dragon;

enum TileType
{
    Grass = 1,  //can leave out = 1 etc.
    Libtile = 2,
    Stone = 3,
    Carpet = 4,
    None = 5,
    BShelfS = 6,
    BShelfE = 7,
    BShelfBS = 8,
    BShelfBE = 9,
    Scrolls1 = 10,
};

struct Node
{
    QGraphicsPixmapItem *label;
    TileType tile;
};

struct PathPoint
{
    int cost;
    int x;
    int y;
    int f;
    int g;
    int h;
    PathPoint *parent;
    bool pathFound;
};


class scrollgame: public QGraphicsView
{
public:
    scrollgame();

    QGraphicsScene * scene;
    QGraphicsPixmapItem * mouseicon;

    void background();
    void changeMouseIcon(int dragonelement);
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void refreshResources();

    //void animate();

    Dragon *hatch;

    int chrystals = 100;
    int scrollsleft = 50;
    QGraphicsTextItem *chrystal;
    QGraphicsTextItem *scrolls;
    QGraphicsTextItem *roundnum;


    //Timers
    QTimer *animationtimer;
    QTimer *eanimationtimer;

    QTimer *roundtimer;
    QTimer *enemygaptimer;

    int roundcount;
    int maxrounds;

    int changed;

    QVector<QPointF> path;

    //Map Stuffs
    static const int mapX = 40;
    static const int mapY = 35;
    static const int tileX = 64;
    static const int tileY = 64;

    Node map[mapX][mapY];
    QPixmap grass, libtile, stone, carpet, none, bshelfs, bshelfe, bshelfbs, bshelfbe, scrolls1,
            balcony, windows, shelfWall;

    //Music
    QMediaPlayer *music;


private:

    //int dragonX, dragonY;

    int spawncount;
    int maxspawns;

    //Pathfinding
    PathPoint *spawnpoint;
    PathPoint *destpoint;
    PathPoint *search[mapX][mapY];
    QVector<PathPoint*> openList;
    QVector<PathPoint*> closedList;

    //QTimer *movementtimer;

private slots:
   // void playBGDMusic();

    int calcH(PathPoint *a, PathPoint *b);
    void calcNeighbours(PathPoint *n);
    void initPath();
    //void getPath();
    PathPoint* smallestF();

    int sprite;

    //Timerslots
    void moveEnemy();    

    //void mousePressEvent(QMouseEvent *e);

public slots:
    void incChrystals();
    void spawnShadows();
    void spawn();

signals:
    void animatedragon();
};

#endif // SCROLLGAME_H
