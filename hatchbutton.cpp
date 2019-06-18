#include "hatchbutton.h"
#include "scrollgame.h"

extern scrollgame *game;

HatchButton::HatchButton(QGraphicsItem *parent): QGraphicsPixmapItem(parent)
{
    QPixmap eggs(":/img/AllySet.png");
    QPixmap eegg = eggs.copy(350,0,22,31);

    setPixmap(eegg);
}

void HatchButton::mousePressEvent(QGraphicsSceneMouseEvent *e)
{
    if (!game->hatch)
    {
        game->hatch = new Dragon();
        game->changeMouseIcon(1);
    }
}
