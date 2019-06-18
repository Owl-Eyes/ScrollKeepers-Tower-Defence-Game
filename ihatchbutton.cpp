#include "ihatchbutton.h"
#include "scrollgame.h"
#include "idragon.h"

extern scrollgame *game;

iHatchButton::iHatchButton(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    QPixmap eggs(":/img/AllySet.png");
    QPixmap iegg = eggs.copy(350,420,22,31);

    setPixmap(iegg);
}

void iHatchButton::mousePressEvent(QGraphicsSceneMouseEvent *e)
{
    if ((!game->hatch) && (game->chrystals >= 400))
    {
        game->hatch = new iDragon();
        game->changeMouseIcon(4);
        game->chrystals -= 400;
        game->refreshResources();
    }
}
