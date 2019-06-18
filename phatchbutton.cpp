#include "phatchbutton.h"
#include "scrollgame.h"
#include "pdragon.h"

extern scrollgame *game;

pHatchButton::pHatchButton(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    QPixmap eggs(":/img/AllySet.png");
    QPixmap pegg = eggs.copy(350,140,22,31);

    setPixmap(pegg);
}

void pHatchButton::mousePressEvent(QGraphicsSceneMouseEvent *e)
{
    if ((!game->hatch) && (game->chrystals >= 100))
    {
        game->hatch = new pDragon();
        game->changeMouseIcon(2);
        game->chrystals -= 100;
        game->refreshResources();
    }
}
