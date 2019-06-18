#include "mainwindow.h"
#include "scrollgame.h"
#include "dragon.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QMessageBox>

scrollgame *game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QMessageBox box;
    QString message = QStringLiteral("***************************************************************** \n"
                                     "*          Welcome to the realm of the Scroll Keepers!            * \n"
                                     "***************************************************************** \n"
                                     "*                                                                                               * \n"
                                     "*  Protect the ancient scrolls from the Mad King's minions. * \n"
                                     "*                                                                                               * \n"
                                     "*****************************************************************");
    box.setInformativeText(message);
    box.setStandardButtons(QMessageBox::Ok);
    box.exec();


    if (QMessageBox::Ok)
    {
        game = new scrollgame;
        game->setMinimumSize(1922,1060);
        game->show();
    }

    return a.exec();
}
