#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QString>
#include <QListView>
#include <QStringListModel>
#include <QStringList>
#include <QFile>
#include <QTextBrowser>
#include <QTextStream>
#include <QMessageBox>
#include <string>
#include <typeinfo>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QFileDialog>
#include <QTimer>

using namespace std;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    toInstallEventFilter();
    FindFile2(headfilepath);

    scene = new QGraphicsScene();//设置画板
    scene->setSceneRect(-150,-150,300,300);
    ui->graphicsView->setScene(scene);//将画板加入到view中

    RectItemR1 = new QGraphicsRectItem(0, 0, 30, 30);
    RectItemR2 = new QGraphicsRectItem(0, 0, 30, 30);
    RectItemR3 = new QGraphicsRectItem(0, 0, 30, 30);
    RectItemR4 = new QGraphicsRectItem(0, 0, 30, 30);
    RectItemR5 = new QGraphicsRectItem(0, 0, 30, 30);
    RectItemR6 = new QGraphicsRectItem(0, 0, 30, 30);
    RectItemR7 = new QGraphicsRectItem(0, 0, 30, 30);
    RectItemR8 = new QGraphicsRectItem(0, 0, 30, 30);
    RectItemR9 = new QGraphicsRectItem(0, 0, 30, 30);
    RectItemR10 = new QGraphicsRectItem(0, 0, 30, 30);
    RectItemR11 = new QGraphicsRectItem(0, 0, 30, 30);
    RectItemR12 = new QGraphicsRectItem(0, 0, 30, 30);
    RectItemR13 = new QGraphicsRectItem(0, 0, 30, 30);
    RectItemR14 = new QGraphicsRectItem(0, 0, 30, 30);
    RectItemR15 = new QGraphicsRectItem(0, 0, 30, 30);
    RectItemR16 = new QGraphicsRectItem(0, 0, 30, 30);//设置传感器图形

    RectItemR1->setBrush(QColor(0,0,255));//设置颜色
    RectItemR2->setBrush(QColor(0,0,255));
    RectItemR3->setBrush(QColor(0,0,255));
    RectItemR4->setBrush(QColor(0,0,255));
    RectItemR5->setBrush(QColor(0,0,255));
    RectItemR6->setBrush(QColor(0,0,255));
    RectItemR7->setBrush(QColor(0,0,255));
    RectItemR8->setBrush(QColor(0,0,255));
    RectItemR9->setBrush(QColor(0,0,255));
    RectItemR10->setBrush(QColor(0,0,255));
    RectItemR11->setBrush(QColor(0,0,255));
    RectItemR12->setBrush(QColor(0,0,255));
    RectItemR13->setBrush(QColor(0,0,255));
    RectItemR14->setBrush(QColor(0,0,255));
    RectItemR15->setBrush(QColor(0,0,255));
    RectItemR16->setBrush(QColor(0,0,255));

    scene->addItem(RectItemR1);
    scene->addItem(RectItemR2);
    scene->addItem(RectItemR3);
    scene->addItem(RectItemR4);
    scene->addItem(RectItemR5);
    scene->addItem(RectItemR6);
    scene->addItem(RectItemR7);
    scene->addItem(RectItemR8);
    scene->addItem(RectItemR9);
    scene->addItem(RectItemR10);
    scene->addItem(RectItemR11);
    scene->addItem(RectItemR12);
    scene->addItem(RectItemR13);
    scene->addItem(RectItemR14);
    scene->addItem(RectItemR15);
    scene->addItem(RectItemR16);

    RectItemR1->setPos(10,10);
    RectItemR2->setPos(50,10);
    RectItemR3->setPos(90,10);
    RectItemR4->setPos(130,10);
    RectItemR5->setPos(170,10);
    RectItemR6->setPos(10,50);
    RectItemR7->setPos(50,50);
    RectItemR8->setPos(90,50);
    RectItemR9->setPos(130,50);
    RectItemR10->setPos(170,50);
    RectItemR11->setPos(10,90);
    RectItemR12->setPos(50,90);
    RectItemR13->setPos(90,90);
    RectItemR14->setPos(130,90);
    RectItemR15->setPos(170,90);
    RectItemR16->setPos(210,90);



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::toInstallEventFilter()
{
    ui->pushButton->installEventFilter(this);
    ui->pushButton_2->installEventFilter(this);
}



bool MainWindow::eventFilter(QObject *target, QEvent *event) //change the buttom form with mouse movemoents
{
    if(target == ui->pushButton)
    {
        if(event->type() == QEvent::HoverEnter)
        {
            ui->pushButton->setStyleSheet("QPushButton#pushButton{border-radius: 8px;color: white;padding: 16px 32px;text-align: center;text-decoration: none;font-size: 16px;margin: 4px 2px;background-color: #e7e7e7;color: black;border: 2px solid #e7e7e7;}");
        }

        if(event->type() == QEvent::HoverLeave)
        {
            ui->pushButton->setStyleSheet("QPushButton#pushButton{border-radius: 8px;color: white;padding: 16px 32px;text-align: center;text-decoration: none;font-size: 16px;margin: 4px 2px;background-color: white;color: black;border: 2px solid #e7e7e7;}");
        }

        if(event->type() == QEvent::MouseButtonPress)
        {
            ui->pushButton->setStyleSheet("QPushButton#pushButton{border-radius: 8px;color: white;padding: 16px 32px;text-align: center;text-decoration: none;font-size: 16px;margin: 4px 2px;background-color: #06AD56;color: black;border: 2px solid #e7e7e7;}");
        }
    }

    if(target == ui->pushButton_2)
    {
        if(event->type() == QEvent::HoverEnter)
        {
             ui->pushButton_2->setStyleSheet("QPushButton#pushButton_2{border-radius: 8px;color: white;padding: 16px 32px;text-align: center;text-decoration: none;font-size: 16px;margin: 4px 2px;background-color: #e7e7e7;color: black;border: 2px solid #e7e7e7;}");
        }

        if(event->type() == QEvent::HoverLeave)
        {
            ui->pushButton_2->setStyleSheet("QPushButton#pushButton_2{border-radius: 8px;color: white;padding: 16px 32px;text-align: center;text-decoration: none;font-size: 16px;margin: 4px 2px;background-color: white;color: black;border: 2px solid #e7e7e7;}");
        }

        if(event->type() == QEvent::MouseButtonPress)
        {
            ui->pushButton_2->setStyleSheet("QPushButton#pushButton_2{border-radius: 8px;color: white;padding: 16px 32px;text-align: center;text-decoration: none;font-size: 16px;margin: 4px 2px;background-color: #ff0000;color: black;border: 2px solid #e7e7e7;}");
        }
    }



    return false;
}

void MainWindow::on_pushButton_clicked()
{
    for (int i = 0;i < infolist.length() ; i++)
    {
        QString filepath = headfilepath;
        qDebug() << filepath;
        filepath += infolist.at(i);
        qDebug() << filepath;
        QFile file(filepath);

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) //judge whether the file is successfully readed
        {
    //        qDebug() << "Fail to open jsonfile: " << file.errorString();
            QMessageBox::information(0,"info","fail to open!!!");
        }
        QByteArray jsonData = file.readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);
        QJsonObject jsonObject = jsonDoc.object();

        qint64 timeStamp = jsonObject["timeStamp"].toInt();
        bool leftFoot =  jsonObject["leftFoot"].toBool();

        QJsonArray sensordata = jsonObject.value("sensorData").toArray();
        for (qint32 i = 0; i < sensordata.count() ; i++)
        {
            QJsonValue value = sensordata.at(i);
            double result = value.toDouble();
            QString str = QString::number(result,'f', 2);
            int colorvalue = (int)((result / 16.0) * 255);
            qDebug() << colorvalue;

            if(leftFoot)
            {
                switch (i)
                {
                    case 0: ui->textBrowser_2->setText(str);
                    case 1: ui->textBrowser_4->setText(str);
                    case 2: ui->textBrowser_6->setText(str);
                    case 3: ui->textBrowser_8->setText(str);
                    case 4: ui->textBrowser_10->setText(str);
                    case 5: ui->textBrowser_12->setText(str);
                    case 6: ui->textBrowser_14->setText(str);
                    case 7: ui->textBrowser_16->setText(str);
                    case 8: ui->textBrowser_18->setText(str);
                    case 9: ui->textBrowser_20->setText(str);
                    case 10: ui->textBrowser_22->setText(str);
                    case 11: ui->textBrowser_24->setText(str);
                    case 12: ui->textBrowser_26->setText(str);
                    case 13: ui->textBrowser_28->setText(str);
                    case 14: ui->textBrowser_30->setText(str);
                    case 15: ui->textBrowser_32->setText(str);
                }
            }
            else
            {
                switch (i)
                {
                    case 0: ui->textBrowser->setText(str);RectItemR1->setBrush(QColor(colorvalue,0,255 - colorvalue));scene->addItem(RectItemR1);
                    case 1: ui->textBrowser_3->setText(str);RectItemR2->setBrush(QColor(colorvalue,0,255 - colorvalue));scene->addItem(RectItemR2);
                    case 2: ui->textBrowser_5->setText(str);RectItemR3->setBrush(QColor(colorvalue,0,255 - colorvalue));scene->addItem(RectItemR3);
                    case 3: ui->textBrowser_7->setText(str);RectItemR4->setBrush(QColor(colorvalue,0,255 - colorvalue));scene->addItem(RectItemR4);
                    case 4: ui->textBrowser_9->setText(str);RectItemR5->setBrush(QColor(colorvalue,0,255 - colorvalue));scene->addItem(RectItemR5);
                    case 5: ui->textBrowser_11->setText(str);RectItemR6->setBrush(QColor(colorvalue,0,255 - colorvalue));scene->addItem(RectItemR6);
                    case 6: ui->textBrowser_13->setText(str);RectItemR7->setBrush(QColor(colorvalue,0,255 - colorvalue));scene->addItem(RectItemR7);
                    case 7: ui->textBrowser_15->setText(str);RectItemR8->setBrush(QColor(colorvalue,0,255 - colorvalue));scene->addItem(RectItemR8);
                    case 8: ui->textBrowser_17->setText(str);RectItemR9->setBrush(QColor(colorvalue,0,255 - colorvalue));scene->addItem(RectItemR9);
                    case 9: ui->textBrowser_19->setText(str);RectItemR10->setBrush(QColor(colorvalue,0,255 - colorvalue));scene->addItem(RectItemR10);
                    case 10: ui->textBrowser_21->setText(str);RectItemR11->setBrush(QColor(colorvalue,0,255 - colorvalue));scene->addItem(RectItemR11);
                    case 11: ui->textBrowser_23->setText(str);RectItemR12->setBrush(QColor(colorvalue,0,255 - colorvalue));scene->addItem(RectItemR12);
                    case 12: ui->textBrowser_25->setText(str);RectItemR13->setBrush(QColor(colorvalue,0,255 - colorvalue));scene->addItem(RectItemR13);
                    case 13: ui->textBrowser_27->setText(str);RectItemR14->setBrush(QColor(colorvalue,0,255 - colorvalue));scene->addItem(RectItemR14);
                    case 14: ui->textBrowser_29->setText(str);RectItemR15->setBrush(QColor(colorvalue,0,255 - colorvalue));scene->addItem(RectItemR15);
                    case 15: ui->textBrowser_31->setText(str);RectItemR16->setBrush(QColor(colorvalue,0,255 - colorvalue));scene->addItem(RectItemR16);
                }
            }
        }
        Delay_MSec(1000);
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    qDebug() << 111;
}

int MainWindow::FindFile2(const QString& _filePath)
{
    QDir dir(_filePath);

    if (!dir.exists()) {
        return -1;
    }

  //取到所有的文件和文件名，但是去掉.和..的文件夹（这是QT默认有的）
    dir.setFilter(QDir::Dirs|QDir::Files|QDir::NoDotAndDotDot);

    //文件夹优先
    dir.setSorting(QDir::DirsFirst);

    //转化成一个list
    QFileInfoList list = dir.entryInfoList();
    infolist = dir.entryList(QDir::Files | QDir::NoDotAndDotDot);
    if(list.size()< 1 ) {
        return -1;
    }
    int i=0;

    //递归算法的核心部分
    do{
        QFileInfo fileInfo = list.at(i);
        //如果是文件夹，递归
        bool bisDir = fileInfo.isDir();
        if(bisDir) {
            FindFile2(fileInfo.filePath());
        }
        else{
            for(int m = 0; m <infolist.size(); m++) {
                                //这里是获取当前要处理的文件名
                qDebug() << infolist.at(m);
            }
            break;
        }//end else
        i++;
    } while(i < list.size());

    return 0;
}

void MainWindow::Delay_MSec(unsigned int msec)
{
    QEventLoop loop;//定义一个新的事件循环
    QTimer::singleShot(msec, &loop, SLOT(quit()));//创建单次定时器，槽函数为事件循环的退出函数
    loop.exec();//事件循环开始执行，程序会卡在这里，直到定时时间到，本循环被退出
}
