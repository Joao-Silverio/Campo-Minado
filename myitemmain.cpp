#include "myitemmain.h"

myitemmain::myitemmain(QString path)
{
    this->setPixmap(QPixmap(path));
}
