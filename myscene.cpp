#include "myscene.h"

extern int a[8][8];
extern int gameoverFlag;
myitem *item[64];

int myscene::index = 0; //global

myscene::myscene(QObject *parent) :
    QGraphicsScene(parent)
{
    initImage(); //Initialize the game interface
    ptimer = new QTimer;
    connect(ptimer, SIGNAL(timeout()), this, SLOT(Update()));
    ptimer->start(1); //Refresh the interface every second
}

void myscene::initImage()
{
    for(int i=0; i<64; i++)
    {
        item[i] = new myitem(":/source_pic/f3"); //8x8 initialization image for each icon
        item[i]->setPos(item[i]->boundingRect().width()*(i%8), item[i]->boundingRect().height()*(i/8)); //8x8 arrangement
        this->addItem(item[i]); //Add each item to the scene
        a[i/8][i%8] = 0;//The value behind each item is assigned to 0

    }
    for(int j=0; j<8; j++)//Take eight mines at random and assign a value of 1
    {
        index = qrand()%64;//Take eight random numbers within 64
        if(item[index]->flag == 1)//Retake if repeated
            j--;
        item[index]->flag = 1; //The item member variable flag is set to 1
        a[index/8][index%8] = 1; //The value behind the 8x8 grid is assigned to 1
    }
}

void myscene::Update() //The value behind the 8x8 square is assigned to 1 when the game is over, it is called to display all the mines
{
    if(gameoverFlag == 1)
    {
        for(index=0; index<64; index++)
        {
            if(a[index/8][index%8] == 1)
            {
                item[index] = new myitem(":/source_pic/l2"); //Bomb
                item[index]->setPos(item[index]->boundingRect().width()*(index%8), item[index]->boundingRect().height()*(index/8));
                this->addItem(item[index]);
            }
        }
        ptimer->stop();
    }
}
