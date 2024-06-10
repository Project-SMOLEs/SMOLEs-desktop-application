#include "viusalization.h"
#include <QGraphicsRectItem>

viusalization::viusalization() : QGraphicsView()
{
    resize(400,400);
    setBackgroundBrush(QPixmap("../graphicsView04/01.jpg"));//其实就是设置场景的背景
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,200,200);
    QGraphicsRectItem *item = new QGraphicsRectItem(0,0,20,20);
    item->setBrush(Qt::red);
    scene->addItem(item);
    setScene(scene);
}
