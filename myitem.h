#ifndef MYITEM_H
#define MYITEM_H
#include<QString>
#include<QGraphicsPixmapItem>
#include<QGraphicsSceneMouseEvent>
#include<QMessageBox>
#include<QDebug>

class myitem : public QGraphicsPixmapItem
{
public:
    myitem(QString path);
    int flag;//0 means no bomb, 1 means bomb
    void setNum(int y, int x);
private:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    int boomNum;//The number of mines around
    int IsflagOrwhiteblock;//The 0 around the thunder means the state has not been clicked, 1 means the flag is inserted, and 2 means the number of mines turned white when they are clicked.
    int spreadFlag;//if the current block been spread
    int m_x;
    int m_y;
};

#endif // MYITEM_H
