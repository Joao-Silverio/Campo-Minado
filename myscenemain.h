#ifndef MYSCENEMAIN_H
#define MYSCENEMAIN_H
#include "myitemmain.h"
#include <QObject>
#include<QGraphicsScene>

class myscenemain : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit myscenemain(QObject *parent = 0);

signals:

public slots:
private:
    myitemmain *itemmain;
};

#endif // MYSCENEMAIN_H
