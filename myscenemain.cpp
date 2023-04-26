#include "myscenemain.h"

myscenemain::myscenemain(QObject *parent) : QGraphicsScene(parent)
{
    QString path=":/source_pic/zhujiemian";
    itemmain = new myitemmain(path);
    this->addItem(itemmain);
}
