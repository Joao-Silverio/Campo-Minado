#include "mainwindow.h"
#include "ui_mainwindow.h"

extern int gameoverFlag;
extern int flagNum;
int Click = 0; //Player need to click on the square to start timing

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scmain = new myscenemain;
    ui->graphicsView_main->setScene(scmain);
    ui->stackedWidget->setCurrentIndex(0);
    timeFailorWin = new QTimer;
    currentTime = new QTimer;
    connect(timeFailorWin, SIGNAL(timeout()), this, SLOT(Update()));
    connect(currentTime, SIGNAL(timeout()), this, SLOT(updateCount()));
    currentTime->start(1);//The current time, updateCount() is called every 1 second
    t.setHMS(0, 0, 0);//lcd display is initialized to 0
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Update()
{
    if(gameoverFlag == 1)
    {
        Click = 0;
        t.setHMS(0, 0, 0);
        ui->lcdNumber->display("00:00");
        QMessageBox::information(this, "info", "you failed!");//8*8 failed
        gameoverFlag--;
        timeFailorWin->stop();
        gameoverFlag--;

    }else if(flagNum == 8)//All the bombs are found to be successful
    {
        Click = 0;
        QMessageBox::information(this, "info", "you win!");//8*8 success
        flagNum = 0;
        timeFailorWin->stop();
        flagNum = 0;
    }
}
void MainWindow::on_pushButton_clicked()
{
   sc = new myscene;
   ui->graphicsView_8x8->setScene(sc);
   ui->stackedWidget->setCurrentIndex(1);
   timeFailorWin->start(500);//Check whether you have won or lost every half a second, and execute the Update function
}
void MainWindow::updateCount()
{
    if(Click > 0)//The timer will start counting when the player starts playing the game and will be displayed on the lcd
    {
        currentTime->start(1);
        t = t.addMSecs(1.5);
        QString stime = t.toString("mm:ss");
        ui->lcdNumber->display(stime);
    }
}
void MainWindow::on_pushButtonrestart_clicked()
{
    delete sc;
    sc = new myscene;
    ui->graphicsView_8x8->setScene(sc);
    flagNum = 0;
    timeFailorWin->start(500);
    Click = 0;
    t.setHMS(0, 0, 0);
    ui->lcdNumber->display("00:00");
}
void MainWindow::on_pushButtonexit_clicked()
{
    delete sc;
    ui->stackedWidget->setCurrentIndex(0);
    flagNum = 0;
    Click = 0;
    t.setHMS(0, 0, 0);
    ui->lcdNumber->display("00:00");
}
