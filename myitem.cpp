#include "myitem.h"
#include <unistd.h>

int gameoverFlag = 0;
int a[8][8];
int flagNum;//Find the number of bombs (plug in the flag)

extern int Click;
extern myitem *item[64];

myitem::myitem(QString path)
{
    this->setPixmap(QPixmap(path));
    IsflagOrwhiteblock = 0;//0 means the state has not been clicked
    spreadFlag = 0;
    flag = 0;
}

void myitem::setNum(int y, int x)
{
    boomNum = 0;
    if((y-1 >= 0) && (x-1 >= 0) && (a[y-1][x-1] == 1))//Eight squares around detect how many mines there are in total
        boomNum++;
    if((y-1 >= 0) && a[y-1][x] == 1)
        boomNum++;
    if((y-1 >= 0) && (x+1 <= 7) && (a[y-1][x+1] == 1))
        boomNum++;
    if((x-1 >= 0) && (a[y][x-1] == 1))
        boomNum++;
    if((x+1 <= 7) && (a[y][x+1] == 1))
        boomNum++;
    if((x-1 >= 0) && (y+1 <= 7) && (a[y+1][x-1] == 1))
        boomNum++;
    if((y+1 <= 7) && (a[y+1][x] == 1))
        boomNum++;
    if((y+1 <= 7) && (x+1 <= 7) && (a[y+1][x+1] == 1))
        boomNum++;
    switch(boomNum)//Display the number on the current block according to the number of mines around
    {
        case 1: item[8*y+x]->setPixmap(QPixmap(":/source_pic/11")); item[8*y+x]->IsflagOrwhiteblock += 2; break;
        case 2: item[8*y+x]->setPixmap(QPixmap(":/source_pic/22")); item[8*y+x]->IsflagOrwhiteblock += 2; break;
        case 3: item[8*y+x]->setPixmap(QPixmap(":/source_pic/33")); item[8*y+x]->IsflagOrwhiteblock += 2; break;
        case 4: item[8*y+x]->setPixmap(QPixmap(":/source_pic/44")); item[8*y+x]->IsflagOrwhiteblock += 2; break;
        case 5: item[8*y+x]->setPixmap(QPixmap(":/source_pic/55")); item[8*y+x]->IsflagOrwhiteblock += 2; break;
        case 6: item[8*y+x]->setPixmap(QPixmap(":/source_pic/66")); item[8*y+x]->IsflagOrwhiteblock += 2; break;
        case 7: item[8*y+x]->setPixmap(QPixmap(":/source_pic/77")); item[8*y+x]->IsflagOrwhiteblock += 2; break;
        case 8: item[8*y+x]->setPixmap(QPixmap(":/source_pic/88")); item[8*y+x]->IsflagOrwhiteblock += 2; break;
        case 0: item[8*y+x]->setPixmap(QPixmap(":/source_pic/f2"));//It means that there is no bomb around, and the blocks in different positions below spread to the surroundings in different ways
        if(y < 7 && y > 0 && x < 7 && x > 0 && item[8*y+x]->spreadFlag == 0)//Belongs to the middle square
        {
            item[8*y+x]->spreadFlag = 1;
            setNum(y-1, x);
            setNum(y, x-1);
            setNum(y+1, x);
            setNum(y, x+1);
        }
        if(y == 0 && (x != 0) && (x != 7) && item[8*y+x]->spreadFlag == 0)//The top box does not include two sides
        {
            item[8*y+x]->spreadFlag = 1;
            setNum(y, x-1);
            setNum(y+1, x);
            setNum(y, x+1);
        }
        if((x == 0) && (y != 0) && (y != 7) && item[8*y+x]->spreadFlag == 0)//The box on the left does not contain both sides
        {
            item[8*y+x]->spreadFlag = 1;
            setNum(y-1, x);
            setNum(y+1, x);
            setNum(y, x+1);
        }
        if((y == 7) && (x != 0) && (x != 7) && item[8*y+x]->spreadFlag == 0)//The box below does not contain both sides
        {
            item[8*y+x]->spreadFlag = 1;
            setNum(y-1, x);
            setNum(y, x-1);
            setNum(y, x+1);
        }
        if((x == 7) && (y != 0) && (y != 7) && item[8*y+x]->spreadFlag == 0)//The box on the right does not contain both sides
        {
            item[8*y+x]->spreadFlag = 1;
            setNum(y-1, x);
            setNum(y, x-1);
            setNum(y+1, x);
        }
        if((x == 0) && (y == 0) && item[8*y+x]->spreadFlag == 0)//Upper left corner
        {
            item[8*y+x]->spreadFlag = 1;
            setNum(y, x+1);
            setNum(y+1, x);
        }
        if((x == 7) && (y == 7) && item[8*y+x]->spreadFlag == 0)//Bottom right corner
        {
            item[8*y+x]->spreadFlag = 1;
            setNum(y-1, x);
            setNum(y, x-1);
         }
        if((y == 7) && (x == 0) && item[8*y+x]->spreadFlag == 0)//Bottom left

        {
            item[8*y+x]->spreadFlag = 1;
            setNum(y-1, x);
            setNum(y, x+1);
        }
        if((x == 7)&&(y == 0) && item[8*y+x]->spreadFlag == 0)//Upper right corner
        {
            item[8*y+x]->spreadFlag = 1;
            setNum(y+1, x);
            setNum(y, x-1);
        }
        item[8*y+x]->IsflagOrwhiteblock += 2;

       break;
   }
}
void myitem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && flag == 0 && IsflagOrwhiteblock == 0) //The box is not clicked, left click the mouse and it is not a bomb
    {
        m_x = this->pos().x();
        m_y = this->pos().y(); //Get the coordinates of this block
        setNum(m_y/48, m_x/48); //Take [0,0]->[7,7], judge the number of surrounding bombs and display them, or if there is no bomb spreading

    }else if(event->button() == Qt::LeftButton && flag == 1 && IsflagOrwhiteblock == 0) //The box is not clicked, the left click is bomb
    {
        this->setPixmap(QPixmap(":/source_pic/z1")); //Set bomb icon
        gameoverFlag = 1; //Game over

    }else if(event->button() == Qt::RightButton && flag == 1) //Right-click the square that is bomb
    {
        if(IsflagOrwhiteblock == 0) //The cube has not been clicked
        {
            this->setPixmap(QPixmap(":/source_pic/q1"));//Flag off
            IsflagOrwhiteblock++; //ndicates that this block has been flagged
            flagNum++; //Add one to the number of bomb found

        }else if(IsflagOrwhiteblock == 1)//If this piece has been flagged
        {
            this->setPixmap(QPixmap(":/source_pic/f3"));//Cancel the flag
            IsflagOrwhiteblock--; //Before the state returned to the point
            flagNum--; //The number of mines found minus one
        }

    }else if(event->button() == Qt::RightButton && flag == 0)//Right click on the square that is not bomb

    {
        if(IsflagOrwhiteblock == 0)//If the flag has not been clicked, it will show that the flag has been inserted
        {
            this->setPixmap(QPixmap(":/source_pic/q1"));
            IsflagOrwhiteblock++;
            flagNum--;//Wrong flag -1
        }else if(IsflagOrwhiteblock == 1)//If the flag has been planted, cancel the flag planting
        {
           this->setPixmap(QPixmap(":/source_pic/f3"));
           IsflagOrwhiteblock--;
           flagNum++;//Cancel the wrong flag +1
        }
    }

    Click++;//The number of clicks plus one
}
