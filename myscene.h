#ifndef MYSCENE_H
#define MYSCENE_H
#include "myitem.h"
#include <QObject>
#include <QGraphicsScene>
#include <QTime>
#include <QTimer>
#include <QtGlobal>
class myscene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit myscene(QObject *parent = 0);
    void initImage();

    static int index;
signals:

public slots:
    void Update();
private:
    QTime t;
    QTimer *ptimer;
};

#endif // MYSCENE_H
