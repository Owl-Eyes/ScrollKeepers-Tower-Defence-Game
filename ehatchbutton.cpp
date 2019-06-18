#include "ehatchbutton.h"
#include "scrollgame.h"
#include "edragon.h"

extern scrollgame *game;

eHatchButton::eHatchButton(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    QPixmap eggs(":/img/AllySet.png");
    QPixmap eegg = eggs.copy(350,0,22,31);

    setPixmap(eegg);
}

void eHatchButton::mousePressEvent(QGraphicsSceneMouseEvent *e)
{
    if ((!game->hatch) && (game->chrystals >= 50))
    {
        game->hatch = new eDragon();
        game->changeMouseIcon(1);
        game->chrystals -= 50;
        game->refreshResources();
    }
}
