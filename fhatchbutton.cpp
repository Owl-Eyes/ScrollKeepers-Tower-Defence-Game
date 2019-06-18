#include "fhatchbutton.h"

#include "scrollgame.h"
#include "fdragon.h"

extern scrollgame *game;

fHatchButton::fHatchButton(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    QPixmap eggs(":/img/AllySet.png");
    QPixmap fegg = eggs.copy(350,280,22,31);

    setPixmap(fegg);
}

void fHatchButton::mousePressEvent(QGraphicsSceneMouseEvent *e)
{
    if ((!game->hatch) && (game->chrystals >= 200))
    {
        game->hatch = new fDragon();
        game->changeMouseIcon(3);
        game->chrystals -= 200;
        game->refreshResources();
    }
}
