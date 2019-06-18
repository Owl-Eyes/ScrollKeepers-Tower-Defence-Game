#include "scrollgame.h"

#include "dragon.h"
#include "enemy.h"
#include "bullet.h"

#include "ehatchbutton.h"
#include "phatchbutton.h"
#include "fhatchbutton.h"
#include "ihatchbutton.h"

#include "edragon.h"
#include "pdragon.h"
#include "fdragon.h"
#include "idragon.h"

#include <QDebug>
#include <QFont>
#include <QFontDatabase>
#include <QLabel>
#include <QGraphicsScene>

//extern scrollgame *game;

//class Enemy;

scrollgame::scrollgame()
{
    //new scene
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,1990,1090);
    setScene(scene);

    //cursor
    mouseicon = nullptr;
    setMouseTracking(true);
    hatch = nullptr;

    //The game background/map/HUD
    background();

    //Buttons!!
    eHatchButton *ebutton = new eHatchButton();
    ebutton->setScale(3);
    ebutton->setPos(1120,920);
    scene->addItem(ebutton);

    pHatchButton *pbutton = new pHatchButton();
    pbutton->setScale(3);
    pbutton->setPos(1245,920);
    scene->addItem(pbutton);

    fHatchButton *fbutton = new fHatchButton();
    fbutton->setScale(3);
    fbutton->setPos(1359,920);
    scene->addItem(fbutton);

    iHatchButton *ibutton = new iHatchButton();
    ibutton->setScale(3);
    ibutton->setPos(1475,920);
    scene->addItem(ibutton);

    //Set Resources
    chrystals = 150;
    scrollsleft = 50;
    refreshResources();

    //timers

    roundcount = 0;
    maxrounds = 15;
    maxspawns = 10;
    changed = 0;

    roundtimer = new QTimer;
    roundtimer->setInterval(15000);
    roundtimer->start();
    connect(roundtimer, &QTimer::timeout, this, &scrollgame::spawnShadows);


    animationtimer = new QTimer;
    animationtimer->setInterval(350);
    animationtimer->start();

    //connect(animationtimer, SIGNAL(timeout()), this, SLOT(incChrystals()));
    connect(animationtimer, &QTimer::timeout, this, &scrollgame::incChrystals);

    //connect(elec, &Dragon::shootbullet, this, &scrollgame::sendBullets);

    eanimationtimer = new QTimer;
    eanimationtimer->setInterval(100);
    eanimationtimer->start();

    //no scrollbars
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //Music
    music = new QMediaPlayer;
    music->setMedia(QUrl("qrc:/mp3/Avenged Sevenfold - Fiction(instrumental) [pleer.net].mp3"));
    music->play();

}

void scrollgame::background()
{

    initPath();
    spawnpoint = search[26][0];
    search[26][0]->cost = 1;
    destpoint = search[26][23];
    search[26][24]->cost = 1;

    QPixmap p(":/img/TileSetR.png");
    //grass = p.copy(1,0,64,64);
    libtile = p.copy(66,0,63,64);
    stone = p.copy(130,0,63,64);
    carpet = p.copy(196,0,63,64);
    none = p.copy(260,0,63,64);
    bshelfs = p.copy(1,66,63,64);
    bshelfe = p.copy(1,130,63,64);
    bshelfbs = p.copy(66,66,63,64);
    bshelfbe = p.copy(66,130,63,64);
    scrolls1 = p.copy(1,196,63,64);

    // ************************** BACKDROP ******************************


    QPixmap w(":/img/Windows.png");
    windows = w.copy(0,0,w.width(),w.height());
    QGraphicsPixmapItem *n = new QGraphicsPixmapItem();
    n->setPixmap(windows);

    int x = 0;
    int y = -100;
    n->setPos(x, y);
    scene->addItem(n);
    for (int i = 0; i < mapX; ++i) {
        for (int j = 0; j < mapY; ++j) {
            QGraphicsPixmapItem *l = new QGraphicsPixmapItem();
            Node *z = new Node;
            z->label = l;
            z->tile = Stone;
        }
    }

    // ************************ 1ST LAYER ********************************


    for (int i = 0; i < mapX; ++i)
    {
        for (int j = 5; j < 22; ++j)
        {
            map[i][j].tile = Libtile;
            search[i][j]->cost = 10;
        }
    }

    for (int i = 15; i < 35; ++i)
    {
        for (int j = 22; j < mapY; ++j)
        {
            map[i][j].tile = Carpet;
            search[i][j]->cost = 10;
        }
    }


    for (int i = mapX; i >= 0; --i)
    {
        for (int j = 0; j < mapY; ++j)
        {
            QGraphicsPixmapItem *l = new QGraphicsPixmapItem();

            switch(map[i][j].tile)
            {
            case Grass:
                l->setPixmap(grass);
                break;
            case Libtile:
                l->setPixmap(libtile);
                break;
            case Stone:
                l->setPixmap(stone);
                break;
            case Carpet:
                l->setPixmap(carpet);
                break;
            case None:
                l->setPixmap(none);
                break;
            case BShelfS:
                l->setPixmap(bshelfs);
                break;
            case BShelfE:
                l->setPixmap(bshelfe);
                break;
            case BShelfBS:
                l->setPixmap(bshelfbs);
                break;
            case BShelfBE:
                l->setPixmap(bshelfbe);
                break;
            case Scrolls1:
                l->setPixmap(scrolls1);
                break;

            }

            //l->setMinimumHeight(tileY);

            int x = (j * tileX / 2 + i * tileX / 2) - 100;
            int y = (j * 32 / 2 - i * 32 / 2 + (mapY-13) * 32) - 70;

            l->setPos(x, y);  //adjusts map start
            scene->addItem(l);
        }

    }

    // ************************ 2ND LAYER ********************************

    for (int i = 15; i < 35; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            map[i][j].tile = Carpet;    // CARPET
            search[i][j]->cost = 10;

        }

    }

    for (int i = 37; i < 40; ++i)
    {
        for (int j = 7; j < 12; ++j)
        {
            map[i][j].tile = Stone;    //STONE
            search[i][j]->cost = 1000;
        }

    }

    for (int i = 0; i < mapX; ++i)     //Remove ghost carpet
    {
        for (int j = 22; j < mapY; ++j)
        {

            map[i][j].tile = None;
        }
    }

    for (int i = 0; i < 15; ++i)   //Out Of Bounds
    {
        for (int j = 0; j < 5; ++j)
        {

            map[i][j].tile = None;
            search[i][j]->cost = 1000;
        }
    }

    for (int i = 0; i < 15; ++i)
    {
        for (int j = 22; j < mapY; ++j)
        {

            map[i][j].tile = None;
            search[i][j]->cost = 1000;
        }
    }

    for (int i = 35; i < mapX; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {

            map[i][j].tile = None;
            search[i][j]->cost = 1000;
        }
    }

    for (int i = 35; i < mapX; ++i)
    {
        for (int j = 22; j < mapY; ++j)
        {

            map[i][j].tile = None;
            search[i][j]->cost = 1000;
        }
    }

    //****************** MAZE ******************

    //    for (int j = 5; j < 22; ++j)          //original maze for testing
    //    {
    //        map[23][j].tile = BShelfS;
    //        map[28][j].tile = BShelfS;
    //        search[23][j]->cost = 1000;
    //        search[28][j]->cost = 1000;
    //    }

    //    for (int i = 15; i < 24; ++i)
    //    {
    //        map[i][5].tile = BShelfE;
    //        map[i][22].tile = BShelfE;
    //        search[i][5]->cost = 1000;
    //        search[i][22]->cost = 1000;
    //    }
    //    for (int i = 29; i < 35; ++i)
    //    {
    //        map[i][5].tile = BShelfE;
    //        map[i][22].tile = BShelfE;
    //        search[i][5]->cost = 1000;
    //        search[i][22]->cost = 1000;
    //    }

    for (int i = 15; i < 35; ++i)
    {
        map[i][8].tile = BShelfE;       //set shelf obstacle
        search[i][6]->cost = 1000;
        search[i][8]->cost = 1000;
        search[i+1][6]->cost = 1000;   //inc cost of surrounding blocks due to iso view
        search[i+1][7]->cost = 1000;
        search[i+1][8]->cost = 1000;
    }

    for (int i = 15; i < 35; ++i)
    {
        map[i][13].tile = BShelfE;      //set shelf obstacle
        search[i][12]->cost = 1000;
        search[i][14]->cost = 1000;
        search[i+1][13]->cost = 1000;   //inc cost of surrounding blocks due to iso view
        search[i+1][12]->cost = 1000;
        search[i+1][14]->cost = 1000;
    }

    for (int j = 5; j < 8; ++j)         //vert. shelf
    {
        map[35][j].tile = BShelfBS ;    //set shelf obstacle
        search[35][j]->cost = 1000;
        search[36][j]->cost = 1000;
    }

    for (int i = 15; i < 24; ++i)
    {
        map[i][18].tile = BShelfE;      //set shelf obstacle
        search[i][17]->cost = 1000;
        search[i][19]->cost = 1000;
        search[i+1][18]->cost = 1000;   //inc cost of surrounding blocks due to iso view
        search[i+1][17]->cost = 1000;
        //search[i+1][19]->cost = 1000;
    }

    for (int j = 7; j < 20; ++j)       //vert. shelf
    {
        map[10][j].tile = BShelfS ;    //set shelf obstacle
        search[10][j]->cost = 1000;
    }

    for (int j = 17; j < 20; ++j)       //vert. shelf
    {
        map[28][j].tile = BShelfS ;    //set shelf obstacle
        search[28][j]->cost = 1000;
    }


    //**************** SCROLLS **************

    map[24][24].tile = Scrolls1;
    map[25][24].tile = Scrolls1;
    map[26][24].tile = Scrolls1;
    map[27][24].tile = Scrolls1;



    for (int i = mapX; i >= 0; --i)
    {
        for (int j = 0; j < mapY; ++j)
        {
            QGraphicsPixmapItem *c = new QGraphicsPixmapItem();

            switch(map[i][j].tile)
            {
            case Grass:
                c->setPixmap(grass);
                break;
            case Libtile:
                //c->setPixmap(libtile);
                break;
            case Stone:
                c->setPixmap(stone);
                break;
            case Carpet:
                c->setPixmap(carpet);
                break;
            case None:
                c->setPixmap(none);
                break;
            case BShelfS:
                c->setPixmap(bshelfs);
                break;
            case BShelfE:
                c->setPixmap(bshelfe);
                break;
            case BShelfBS:
                c->setPixmap(bshelfbs);
                break;
            case BShelfBE:
                c->setPixmap(bshelfbe);
                break;
            case Scrolls1:
                c->setPixmap(scrolls1);
                break;

            }

            int x = (j * tileX / 2 + i * tileX / 2) - 100;
            int y = (j * 32 / 2 - i * 32 / 2 + (mapY-15) * 32) - 20;

            c->setPos(x, y);  //adjusts map start
            scene->addItem(c);
        }

    }


    //************************* MIDDROP **************************

    QPixmap s(":/img/ShelfWall.png");
    shelfWall = s.copy(0,0,s.width(),s.height());
    QGraphicsPixmapItem *o = new QGraphicsPixmapItem();
    o->setPixmap(shelfWall);

    int h = 0;
    int i = -100;

    o->setPos(h, i);
    scene->addItem(o);


    //*********************** FRONTDROP ***************************



    QPixmap b(":/img/Balcony2.png");
    balcony = b.copy(0,0,b.width(),b.height());
    QGraphicsPixmapItem *m = new QGraphicsPixmapItem();
    m->setPixmap(balcony);

    int f = 0;
    int g = -100;

    m->setPos(f, g);

    scene->addItem(m);

    //Display Egg Costs
    QGraphicsTextItem *echrystal = new QGraphicsTextItem;   //electric
    echrystal->setScale(2.5);
    echrystal->setPos(1135,1010);
    echrystal->setPlainText("50");
    echrystal->setDefaultTextColor(QColor("light blue"));
    scene->addItem(echrystal);

    QGraphicsTextItem *pchrystal = new QGraphicsTextItem;   //plant
    pchrystal->setScale(2.5);
    pchrystal->setPos(1250,1010);
    pchrystal->setPlainText("100");
    pchrystal->setDefaultTextColor(QColor("light blue"));
    scene->addItem(pchrystal);

    QGraphicsTextItem *fchrystal = new QGraphicsTextItem;   //fire
    fchrystal->setScale(2.5);
    fchrystal->setPos(1372,1010);
    fchrystal->setPlainText("200");
    fchrystal->setDefaultTextColor(QColor("light blue"));
    scene->addItem(fchrystal);


    QGraphicsTextItem *ichrystal = new QGraphicsTextItem;   //ice
    ichrystal->setScale(2.5);
    ichrystal->setPos(1490,1010);
    ichrystal->setPlainText("400");
    ichrystal->setDefaultTextColor(QColor("light blue"));
    scene->addItem(ichrystal);

    //Round
    QGraphicsTextItem *round = new QGraphicsTextItem;   //rounds
    round->setScale(2);
    round->setPos(1588,890);
    round->setPlainText("Round:");
    round->setDefaultTextColor(QColor("ivory"));
    scene->addItem(round);

    //*********************** PATHFINDING ****************************

    path.clear();
    openList.append(spawnpoint);
    calcNeighbours(spawnpoint);

    while(openList.length() > 0)
    {
        PathPoint *t = smallestF();
        closedList.append(t);
        if(t == destpoint)
        {
            while(t->parent)
            {
                //points.prepend(QPoint(t->x,t->y));
                t->pathFound = true;
                t = t->parent;
                path.append(QPointF(t->x,t->y));


            }
            //points.prepend(QPoint(t->x,t->y));
        }
        calcNeighbours(t);
    }
    qDebug() << "hi";
}

void scrollgame::changeMouseIcon(int dragonelement)
{
    QPixmap eggs(":/img/AllySet.png");
    QPixmap eegg = eggs.copy(350,0,22,31);
    QPixmap pegg = eggs.copy(350,140,22,31);
    QPixmap fegg = eggs.copy(350,280,22,31);
    QPixmap iegg = eggs.copy(350,420,22,31);

    if (!mouseicon)
    {
        //scene->removeItem(mouseicon);
        delete mouseicon;
    }

    mouseicon = new QGraphicsPixmapItem();

    switch(dragonelement)
    {
    case 1:
        mouseicon->setPixmap(QPixmap(eegg));
        break;
    case 2:
        mouseicon->setPixmap(QPixmap(pegg));
        break;
    case 3:
        mouseicon->setPixmap(QPixmap(fegg));
        break;
    case 4:
        mouseicon->setPixmap(QPixmap(iegg));
        break;
    }

    mouseicon->setScale(1);
    scene->addItem(mouseicon);
}

void scrollgame::mouseMoveEvent(QMouseEvent *e)
{
    if (mouseicon)
    {
        mouseicon->setPos(e->pos());
    }
}

void scrollgame::mousePressEvent(QMouseEvent *e)
{
    if (hatch)
    {
        //check for tower collision
        QList<QGraphicsItem *> items = mouseicon->collidingItems();
        for (size_t i = 0, n= items.size(); i < n; ++i)
        {
            if (dynamic_cast<Dragon*>(items[i]))
            {
                return;
            }
        }

        hatch->setPos(e->pos());
        scene->removeItem(mouseicon);
        scene->addItem(hatch);
        hatch = nullptr;
    }
    else
    {
        QGraphicsView::mousePressEvent(e);
    }
}

void scrollgame::refreshResources()
{
    scrolls->deleteLater();
    chrystal->deleteLater();
    roundnum->deleteLater();

    //Chrystals
    chrystal = new QGraphicsTextItem();
    chrystal->setPos(1800,845);
    chrystal->setScale(5);
    chrystal->setDefaultTextColor(QColor("light blue"));
    chrystal->setPlainText(QString::number(chrystals));
    scene->addItem(chrystal);

    //Lives
    scrolls = new QGraphicsTextItem();
    scrolls->setPos(1800,935);
    scrolls->setScale(5);
    scrolls->setDefaultTextColor(QColor("ivory"));
    scrolls->setPlainText(QString::number(scrollsleft));
    scene->addItem(scrolls);

    //Rounds
    roundnum = new QGraphicsTextItem;
    roundnum->setScale(5);
    roundnum->setPos(1600,910);
    roundnum->setPlainText(QString::number(roundcount));
    roundnum->setDefaultTextColor(QColor("ivory"));
    scene->addItem(roundnum);

    if (scrollsleft <= 0)
    {
        exit(0);
    }


}

void scrollgame::spawnShadows()
{
    //qDebug("hey");
    spawncount = 0;
    roundcount += 1;

    enemygaptimer = new QTimer;
    enemygaptimer->setInterval(400);
    enemygaptimer->start();

    connect(enemygaptimer, &QTimer::timeout, this, &scrollgame::spawn);

    if (roundcount == maxrounds)
    {
        roundtimer->stop();
    }


}

void scrollgame::spawn()
{
    if (roundcount < 5)               //bird
    {
        enemygaptimer->setInterval(700);
        roundtimer->setInterval(1400);

        Enemy *bird = new Enemy();
        bird->setScale(1);
        bird->setPos(725,200);
        bird->assignPath(path);
        bird->health = 5;
        bird->damage = 1;
        spawncount += 1;

        if (spawncount == maxspawns)
        {
            enemygaptimer->stop();
            maxspawns += 4;
            bird->health += 3;
        }

        scene->addItem(bird);
    }

    if ((roundcount >= 5) && (roundcount < 10))   //dog
    {
        changed = 1;
        enemygaptimer->setInterval(1800);
        roundtimer->setInterval(3600);

        Enemy *dog = new Enemy();
        dog->setScale(1);
        dog->setPos(725,200);
        dog->assignPath(path);
        dog->health = 30;
        dog->damage = 2;
        spawncount += 1;

        if (spawncount == maxspawns)
        {
            enemygaptimer->stop();
            maxspawns += 1;
            dog->health += 14;
        }

        scene->addItem(dog);
    }

    if ((roundcount >= 10) && (roundcount < 15))              //deer
    {
        changed = 2;
        enemygaptimer->setInterval(4000);
        roundtimer->setInterval(8000);

        Enemy *deer = new Enemy();
        deer->setScale(1);
        deer->setPos(725,200);
        deer->assignPath(path);
        deer->health = 150;
        deer->damage = 10;
        spawncount += 1;

        if (spawncount == maxspawns)
        {
            enemygaptimer->stop();
            maxspawns += 2;
            deer->health += 50;
        }

        scene->addItem(deer);
    }




}

void scrollgame::incChrystals()
{
    chrystals = chrystals + 1;
    refreshResources();
}

void scrollgame::initPath()
{
    for (int x = 0; x < mapX; ++x)
    {
        for (int y = 0; y < mapY; ++y)
        {
            PathPoint *t = new PathPoint;
            t->cost = 1;
            t->x = x;
            t->y = y;
            t->f = 0;
            t->g = 0;
            t->h = 0;
            t->pathFound = false;
            t->parent = 0;
            search[x][y] = t;

        }
    }

}

PathPoint* scrollgame::smallestF()
{
    PathPoint *r = openList.first();
    QVectorIterator<PathPoint*> i(openList);
    while(i.hasNext())
    {
        PathPoint *t = i.next();
        if(t->f < r->f)
            r = t;
    }
    //openList.resetPosOne(r);
    openList.removeOne(r);
    return r;
}

int scrollgame::calcH(PathPoint *a, PathPoint *b)
{
    int dx = abs(b->x - a->x);
    int dy = abs(b->y - a->y);
    return 1 * (dx + dy);
}

void scrollgame::calcNeighbours(PathPoint *n)
{
    for(int dy = -1; dy <= 1; ++dy)
    {
        for(int dx = -1; dx <= 1; ++dx)
        {
            int x = dx + n->x;
            int y = dy + n->y;
            if((x >= 0) && (x < mapX) &&
                    (y >= 0) && (y < mapY) &&
                    (!openList.contains(search[x][y])) &&
                    (!closedList.contains(search[x][y])) &&
                    (search[x][y]->cost < 100) &&
                    ((dx*dx) || (dy*dy)) &&
                    !(dx*dx == dy*dy))
            {
                search[x][y]->parent = n;
                search[x][y]->g = n->g + search[x][y]->cost;
                search[x][y]->h = calcH(search[x][y], destpoint);
                search[x][y]->f = search[x][y]->g + search[x][y]->h;
                openList.append(search[x][y]);
            }
        }
    }
}

/*void scrollgame::sendBullets(QPointF targetDest)
{
    //Bullets
    Bullet *bullet = new Bullet();
    bullet->setPos(dragonX + 15, dragonY + 30); //where bullet shoots from

    QLineF ln(QPointF(dragonX, dragonY), targetDest);
    int angle = -1 * ln.angle()*1.1;        //clockwise


    bullet->setRotation(angle);
    scene->addItem(bullet);
}*/
