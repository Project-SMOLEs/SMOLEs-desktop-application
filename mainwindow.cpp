#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "SmolesManager.h"
#include <QComboBox>
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
#include <QGraphicsPixmapItem>
#include <QStyle>
#include <QWidget>
#include <QVBoxLayout>
#include <QSlider>
#include <QGraphicsLineItem>
#include <QBrush>
#include <QGraphicsEllipseItem>
#include <QPainter>

using namespace std;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    toInstallEventFilter();
    FindFile2(Json_file_folder_path);

    ui->horizontalSlider->setMinimum(0);//set the maximum and minimum of the slider
    ui->horizontalSlider->setMaximum(59);
    ui->horizontalSlider->setValue(Slider_value);
    connect(ui->horizontalSlider,SIGNAL(sliderMoved(int)),this,SLOT(on_pushButton_PAUSE_clicked()));
    connect(ui->horizontalSlider,SIGNAL(sliderReleased()),this, SLOT(SLOT_of_Sliderdropped()));
//    connect(ui->textBrowser_TIMESTAMP->document(), SIGNAL(contentsChanged()),this,SLOT(Slider_slide()));


    ui->comboBox->addItem(Combobox_defaultValue);
    ui->comboBox->setCurrentText(Combobox_defaultValue);
//    connect(ui->comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(Set_Jsonfile_name()));
    connect(ui->comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(Run_visualization_automaticaly_window()));

    ui->pushButton_VISUALIZATION->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));//set icon of buttons
    ui->pushButton_PAUSE->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    ui->pushButton_CONTINUE->setIcon(style()->standardIcon(QStyle::SP_ArrowRight));
    ui->pushButton_FORWARD->setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward));
    ui->pushButton_REWIND->setIcon(style()->standardIcon(QStyle::SP_MediaSeekBackward));

    scene_Visualization = new QGraphicsScene(this);//set the scene of visualization
    scene_Visualization->setSceneRect(0,0,600,600);
    ui->graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    ui->graphicsView->setScene(scene_Visualization);//add the scene into graphview
    QPixmap pixmap_Insole("D:\\GUI\\demo\\SMOLEs-desktop-application\\image\\image.png");
    QGraphicsPixmapItem *item_Insole = new QGraphicsPixmapItem(pixmap_Insole);

    // set the picture position
    item_Insole->setPos(50, 50);
    QRectF sceneRect = scene_Visualization->sceneRect();
    QSizeF sceneSize = sceneRect.size();
    QSize imageSize = pixmap_Insole.size();

    qreal scaleX = sceneSize.width() / imageSize.width();
    qreal scaleY = sceneSize.height() / imageSize.height();
    qreal scale = qMin(scaleX, scaleY);
    item_Insole->setScale(scale);
    scene_Visualization->addItem(item_Insole);


    scene_Pressure_value = new QGraphicsScene(this);//set QGraphicsScene of Pressure value
    ui->graphicsView_2->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
    scene_Pressure_value->setSceneRect(0,0,790,710);
    ui->graphicsView_2->setScene(scene_Pressure_value);

    lineGroup = new QGraphicsItemGroup();
    scene_Pressure_value->addItem(lineGroup);

    // set Pen of Pressure value graph
    pen_Pressure_value.setColor(Qt::white);
    pen_Pressure_value.setWidth(2);
    brush_.setColor(Qt::white);
    brush_.setStyle(Qt::SolidPattern);
    ui->graphicsView_2->setRenderHint(QPainter::Antialiasing);

    // draw X and Yaxis
    scene_Pressure_value->addLine(QLineF(50, 680, 800, 680), pen_Pressure_value); // X axis
    scene_Pressure_value->addLine(QLineF(50, 680, 50, 30), pen_Pressure_value); // Y axis

    // Define the Y axis scale factor
    const qreal scaleFactorY = 5000.0 / 650.0;

    // Define the scale factor for X axis (0-800 range)
    const qreal scaleFactorX = 60 / 750.0; // 700 is the length of X axis in pixels (750 - 50)


    // Add tick marks to the Y axes
    for(int i = 0; i <= 650; i += 50)
    {
        scene_Pressure_value->addLine(QLineF(45, 680 - i, 55, 680 - i), pen_Pressure_value); // Y axis ticks

        // Y axis labels
        QGraphicsTextItem *textY = scene_Pressure_value->addText(QString::number(static_cast<int>(i * scaleFactorY)));
        textY->setDefaultTextColor(Qt::white);
        textY->setPos(5, 680 - i - 10); // Adjust position to center the text
    }

    // Add tick marks to the X axes
    for(int i = 0; i <= 750; i += 50)
    {
        scene_Pressure_value->addLine(QLineF(50 + i, 675, 50 + i, 685), pen_Pressure_value); // X axis ticks

        // X axis labels
        QGraphicsTextItem *textX = scene_Pressure_value->addText(QString::number(static_cast<int>(i * scaleFactorX)));
        textX->setDefaultTextColor(Qt::white);
        textX->setPos(50 + i -10, 690); // Adjust position to center the text
    }

    scene_Logo = new QGraphicsScene(this);//set QGraphicsScene of Logo
    scene_Logo->setSceneRect(0,0,881,161);
    QPixmap pixmap_Logo("D:\\GUI\\demo\\SMOLEs-desktop-application\\image\\cover.png");
    QGraphicsPixmapItem *item_Logo = new QGraphicsPixmapItem(pixmap_Logo);
    scene_Logo->addItem(item_Logo);

    ui->graphicsView_logo->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    ui->graphicsView_logo->setScene(scene_Logo);
    ui->graphicsView_logo->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView_logo->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QSize viewSize = ui->graphicsView_logo->size();
    QPixmap scaledPixmap = pixmap_Logo.scaled(viewSize);
    item_Logo->setPixmap(scaledPixmap);

    QRectF rect(0, 0, 65, 26);
    qreal xRadius = 15;
    qreal yRadius = 50;
    RectItemL1 = new RoundedRectItem(rect, xRadius, yRadius);RectItemL1->setRotation(118);
    RectItemL2 = new RoundedRectItem(rect, xRadius, yRadius);RectItemL2->setRotation(75);
    RectItemL3 = new RoundedRectItem(rect, xRadius, yRadius);RectItemL3->setRotation(105);
    RectItemL4 = new RoundedRectItem(rect, xRadius, yRadius);RectItemL4->setRotation(100);
    RectItemL5 = new RoundedRectItem(rect, xRadius, yRadius);RectItemL5->setRotation(85);
    RectItemL6 = new RoundedRectItem(rect, xRadius, yRadius);RectItemL6->setRotation(89);
    RectItemL7 = new RoundedRectItem(rect, xRadius, yRadius);RectItemL7->setRotation(93);
    RectItemL8 = new RoundedRectItem(rect, xRadius, yRadius);RectItemL8->setRotation(95);
    RectItemL9 = new RoundedRectItem(rect, xRadius, yRadius);RectItemL9->setRotation(77);
    RectItemL10 = new RoundedRectItem(rect, xRadius, yRadius);RectItemL10->setRotation(88);
    RectItemL11 = new RoundedRectItem(rect, xRadius, yRadius);RectItemL11->setRotation(97);
    RectItemL12 = new RoundedRectItem(rect, xRadius, yRadius);RectItemL12->setRotation(88);
    RectItemL13 = new RoundedRectItem(rect, xRadius, yRadius);RectItemL13->setRotation(88);
    RectItemL14 = new RoundedRectItem(rect, xRadius, yRadius);RectItemL14->setRotation(88);
    RectItemL15 = new RoundedRectItem(rect, xRadius, yRadius);RectItemL15->setRotation(88);
    RectItemL16 = new RoundedRectItem(rect, xRadius, yRadius);RectItemL16->setRotation(88);

    RectItemR1 = new RoundedRectItem(rect, xRadius, yRadius);RectItemR1->setRotation(113);
    RectItemR2 = new RoundedRectItem(rect, xRadius, yRadius);RectItemR2->setRotation(63);
    RectItemR3 = new RoundedRectItem(rect, xRadius, yRadius);RectItemR3->setRotation(95);
    RectItemR4 = new RoundedRectItem(rect, xRadius, yRadius);RectItemR4->setRotation(85);
    RectItemR5 = new RoundedRectItem(rect, xRadius, yRadius);RectItemR5->setRotation(80);
    RectItemR6 = new RoundedRectItem(rect, xRadius, yRadius);RectItemR6->setRotation(82);
    RectItemR7 = new RoundedRectItem(rect, xRadius, yRadius);RectItemR7->setRotation(85);
    RectItemR8 = new RoundedRectItem(rect, xRadius, yRadius);RectItemR8->setRotation(89);
    RectItemR9 = new RoundedRectItem(rect, xRadius, yRadius);RectItemR9->setRotation(86);
    RectItemR10 = new RoundedRectItem(rect, xRadius, yRadius);RectItemR10->setRotation(90);
    RectItemR11 = new RoundedRectItem(rect, xRadius, yRadius);RectItemR11->setRotation(103);
    RectItemR12 = new RoundedRectItem(rect, xRadius, yRadius);RectItemR12->setRotation(92);
    RectItemR13 = new RoundedRectItem(rect, xRadius, yRadius);RectItemR13->setRotation(92);
    RectItemR14 = new RoundedRectItem(rect, xRadius, yRadius);RectItemR14->setRotation(90);
    RectItemR15 = new RoundedRectItem(rect, xRadius, yRadius);RectItemR15->setRotation(92);
    RectItemR16 = new RoundedRectItem(rect, xRadius, yRadius);RectItemR16->setRotation(92);//set sensor Item color and size

    scene_Visualization->addItem(RectItemR1);scene_Visualization->addItem(RectItemL1);
    scene_Visualization->addItem(RectItemR2);scene_Visualization->addItem(RectItemL2);
    scene_Visualization->addItem(RectItemR3);scene_Visualization->addItem(RectItemL3);
    scene_Visualization->addItem(RectItemR4);scene_Visualization->addItem(RectItemL4);
    scene_Visualization->addItem(RectItemR5);scene_Visualization->addItem(RectItemL5);
    scene_Visualization->addItem(RectItemR6);scene_Visualization->addItem(RectItemL6);
    scene_Visualization->addItem(RectItemR7);scene_Visualization->addItem(RectItemL7);
    scene_Visualization->addItem(RectItemR8);scene_Visualization->addItem(RectItemL8);
    scene_Visualization->addItem(RectItemR9);scene_Visualization->addItem(RectItemL9);
    scene_Visualization->addItem(RectItemR10);scene_Visualization->addItem(RectItemL10);
    scene_Visualization->addItem(RectItemR11);scene_Visualization->addItem(RectItemL11);
    scene_Visualization->addItem(RectItemR12);scene_Visualization->addItem(RectItemL12);
    scene_Visualization->addItem(RectItemR13);scene_Visualization->addItem(RectItemL13);
    scene_Visualization->addItem(RectItemR14);scene_Visualization->addItem(RectItemL14);
    scene_Visualization->addItem(RectItemR15);scene_Visualization->addItem(RectItemL15);
    scene_Visualization->addItem(RectItemR16);scene_Visualization->addItem(RectItemL16);

    RectItemR1->setPos(315,100);RectItemL1->setPos(155,95);//set sensor Item position
    RectItemR2->setPos(348,87);RectItemL2->setPos(192,88);
    RectItemR3->setPos(295,165);RectItemL3->setPos(115,165);
    RectItemR4->setPos(340,160);RectItemL4->setPos(165,160);
    RectItemR5->setPos(390,160);RectItemL5->setPos(205,160);
    RectItemR6->setPos(290,240);RectItemL6->setPos(99,245);
    RectItemR7->setPos(347,240);RectItemL7->setPos(155,240);
    RectItemR8->setPos(405,245);RectItemL8->setPos(210,240);
    RectItemR9->setPos(300,330);RectItemL9->setPos(100,325);
    RectItemR10->setPos(350,330);RectItemL10->setPos(155,325);
    RectItemR11->setPos(405,335);RectItemL11->setPos(205,325);
    RectItemR12->setPos(313,420);RectItemL12->setPos(118,417);
    RectItemR13->setPos(352,420);RectItemL13->setPos(152,416);
    RectItemR14->setPos(385,420);RectItemL14->setPos(192,414);
    RectItemR15->setPos(327,525);RectItemL15->setPos(125,525);
    RectItemR16->setPos(380,530);RectItemL16->setPos(180,520);



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::toInstallEventFilter()
{
    ui->pushButton_VISUALIZATION->installEventFilter(this);
    ui->pushButton_PAUSE->installEventFilter(this);
    ui->pushButton_BLUETOOTH->installEventFilter(this);
    ui->pushButton_RECORD->installEventFilter(this);
    ui->pushButton_CONTINUE->installEventFilter(this);
}


bool MainWindow::eventFilter(QObject *target, QEvent *event) //change the buttom form with mouse movemoents
{
//    if(target == ui->pushButton_VISUALIZATION)
//    {
//        if(event->type() == QEvent::HoverEnter)
//        {
//            ui->pushButton_VISUALIZATION->setStyleSheet("QPushButton#pushButton_VISUALIZATION{border-radius: 8px;color: white;padding: 16px 32px;text-align: center;text-decoration: none;font-size: 16px;margin: 4px 2px;background-color: #e7e7e7;color: black;border: 2px solid #e7e7e7;}");
//           ui->pushButton_VISUALIZATION->setStyleSheet("QPushButton#pushButton_VISUALIZATION{    color: #b1b1b1;border-image: url('D:/GUI/demo/SMOLEs-desktop-application/image/button-background@2x.9.png') 0 0 0 0 stretch stretch;border-width: 1px;border-color: #1e1e1e;border-style: solid;border-radius: 6;padding: 3px;font-size: 12px;padding-left: 5px;padding-right: 5px;}");
//        }

//        if(event->type() == QEvent::HoverLeave)
//        {
//            ui->pushButton_VISUALIZATION->setStyleSheet("QPushButton#pushButton_VISUALIZATION{border-radius: 8px;color: white;padding: 16px 32px;text-align: center;text-decoration: none;font-size: 16px;margin: 4px 2px;background-color: white;color: black;border: 2px solid #e7e7e7;}");
//        }

//        if(event->type() == QEvent::MouseButtonPress)
//        {
//            ui->pushButton_VISUALIZATION->setStyleSheet("QPushButton#pushButton_VISUALIZATION{border-radius: 8px;color: white;padding: 16px 32px;text-align: center;text-decoration: none;font-size: 16px;margin: 4px 2px;background-color: #06AD56;color: black;border: 2px solid #e7e7e7;}");
//        }
//    }

//    if(target == ui->pushButton_PAUSE)
//    {
//        if(event->type() == QEvent::HoverEnter)
//        {
//             ui->pushButton_PAUSE->setStyleSheet("QPushButton#pushButton_PAUSE{border-radius: 8px;color: white;padding: 16px 32px;text-align: center;text-decoration: none;font-size: 16px;margin: 4px 2px;background-color: #e7e7e7;color: black;border: 2px solid #e7e7e7;}");
//        }

//        if(event->type() == QEvent::HoverLeave)
//        {
//            ui->pushButton_PAUSE->setStyleSheet("QPushButton#pushButton_PAUSE{border-radius: 8px;color: white;padding: 16px 32px;text-align: center;text-decoration: none;font-size: 16px;margin: 4px 2px;background-color: white;color: black;border: 2px solid #e7e7e7;}");
//        }

//        if(event->type() == QEvent::MouseButtonPress)
//        {
//            ui->pushButton_PAUSE->setStyleSheet("QPushButton#pushButton_PAUSE{border-radius: 8px;color: white;padding: 16px 32px;text-align: center;text-decoration: none;font-size: 16px;margin: 4px 2px;background-color: #ff0000;color: black;border: 2px solid #e7e7e7;}");
//        }
//    }

//    if(target == ui->pushButton_BLUETOOTH)
//    {
//        if(event->type() == QEvent::HoverEnter)
//        {
//             ui->pushButton_BLUETOOTH->setStyleSheet("QPushButton#pushButton_BLUETOOTH{border-radius: 8px;color: white;padding: 16px 32px;text-align: center;text-decoration: none;font-size: 16px;margin: 4px 2px;background-color: #e7e7e7;color: black;border: 2px solid #e7e7e7;}");
//        }

//        if(event->type() == QEvent::HoverLeave)
//        {
//            ui->pushButton_BLUETOOTH->setStyleSheet("QPushButton#pushButton_BLUETOOTH{border-radius: 8px;color: white;padding: 16px 32px;text-align: center;text-decoration: none;font-size: 16px;margin: 4px 2px;background-color: white;color: black;border: 2px solid #e7e7e7;}");
//        }

//        if(event->type() == QEvent::MouseButtonPress)
//        {
//            ui->pushButton_BLUETOOTH->setStyleSheet("QPushButton#pushButton_BLUETOOTH{border-radius: 8px;color: white;padding: 16px 32px;text-align: center;text-decoration: none;font-size: 16px;margin: 4px 2px;background-color: #00FFFF;color: black;border: 2px solid #e7e7e7;}");
//        }
//    }

//    if(target == ui->pushButton_RECORD)
//    {
//        if(event->type() == QEvent::HoverEnter)
//        {
//             ui->pushButton_RECORD->setStyleSheet("QPushButton#pushButton_RECORD{border-radius: 8px;color: white;padding: 16px 32px;text-align: center;text-decoration: none;font-size: 16px;margin: 4px 2px;background-color: #e7e7e7;color: black;border: 2px solid #e7e7e7;}");
//        }

//        if(event->type() == QEvent::HoverLeave)
//        {
//            ui->pushButton_RECORD->setStyleSheet("QPushButton#pushButton_RECORD{border-radius: 8px;color: white;padding: 16px 32px;text-align: center;text-decoration: none;font-size: 16px;margin: 4px 2px;background-color: white;color: black;border: 2px solid #e7e7e7;}");
//        }

//        if(event->type() == QEvent::MouseButtonPress)
//        {
//            ui->pushButton_RECORD->setStyleSheet("QPushButton#pushButton_RECORD{border-radius: 8px;color: white;padding: 16px 32px;text-align: center;text-decoration: none;font-size: 16px;margin: 4px 2px;background-color: #5500ff;color: black;border: 2px solid #e7e7e7;}");
//        }
//    }

//    if(target == ui->pushButton_CONTINUE)
//    {
//        if(event->type() == QEvent::HoverEnter)
//        {
//             ui->pushButton_CONTINUE->setStyleSheet("QPushButton#pushButton_CONTINUE{border-radius: 8px;color: white;padding: 16px 32px;text-align: center;text-decoration: none;font-size: 16px;margin: 4px 2px;background-color: #e7e7e7;color: black;border: 2px solid #e7e7e7;}");
//        }

//        if(event->type() == QEvent::HoverLeave)
//        {
//            ui->pushButton_CONTINUE->setStyleSheet("QPushButton#pushButton_CONTINUE{border-radius: 8px;color: white;padding: 16px 32px;text-align: center;text-decoration: none;font-size: 16px;margin: 4px 2px;background-color: white;color: black;border: 2px solid #e7e7e7;}");
//        }

//        if(event->type() == QEvent::MouseButtonPress)
//        {
//            ui->pushButton_CONTINUE->setStyleSheet("QPushButton#pushButton_CONTINUED{border-radius: 8px;color: white;padding: 16px 32px;text-align: center;text-decoration: none;font-size: 16px;margin: 4px 2px;background-color: #3300ff;color: black;border: 2px solid #e7e7e7;}");
//        }
//    }

    return false;
}

void MainWindow::on_pushButton_VISUALIZATION_clicked()
{
    sign_of_checkbox = false;
    QList<QCheckBox*> List_of_Checkbox =
    {
        ui->checkBox_LSensor1,ui->checkBox_LSensor2,ui->checkBox_LSensor3,ui->checkBox_LSensor4,ui->checkBox_LSensor5,ui->checkBox_LSensor6,ui->checkBox_LSensor7,ui->checkBox_LSensor8,ui->checkBox_LSensor9,
        ui->checkBox_LSensor10,ui->checkBox_LSensor11,ui->checkBox_LSensor12,ui->checkBox_LSensor13,ui->checkBox_LSensor14,ui->checkBox_LSensor15,ui->checkBox_LSensor16,ui->checkBox_RSensor1,ui->checkBox_RSensor2,ui->checkBox_RSensor3,
        ui->checkBox_RSensor4,ui->checkBox_RSensor5,ui->checkBox_RSensor6,ui->checkBox_RSensor7,ui->checkBox_RSensor8,ui->checkBox_RSensor9,ui->checkBox_RSensor10,ui->checkBox_RSensor11,ui->checkBox_RSensor12,
        ui->checkBox_RSensor13,ui->checkBox_RSensor14,ui->checkBox_RSensor15,ui->checkBox_RSensor16
    };

    for (int i = 0;i < List_of_Checkbox.size() ;i++ ) {
        if(List_of_Checkbox[i]->isChecked() == true)
        {
            sign_of_checkbox = true;
        }
    }  

    if(sign_of_checkbox == true)
    {
        jsonObjects.clear();
        QString filepath = headfilepath;
        qDebug() << filepath;
        QString current_filepath = filepath + "\\" + Json_file_name;
        qDebug() << current_filepath;
        QFile file(current_filepath);

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) //judge whether the file is successfully readed
        {
    //        qDebug() << "Fail to open jsonfile: " << file.errorString();
            QMessageBox::information(0,"info","fail to open!!!Please select one json file!!");
        }

        QByteArray jsonData = file.readAll();
        QJsonDocument document = QJsonDocument::fromJson(jsonData);
        QJsonObject rootObject = document.object();
        sensorDataArray = rootObject["SensorDataPackage"].toArray();

        for (const QJsonValue &value : sensorDataArray) {
                QJsonObject sensorDataObject = value.toObject();
                QString timeStamp__ = sensorDataObject["timeStamp"].toString();

                // 提取最后一位秒数
                QStringList timeParts = timeStamp__.split(":");
                if (timeParts.size() == 6) {
                    int seconds = timeParts.last().toInt();
                    // 检查是否加入QList
                    if (uniqueSeconds.isEmpty()) {
                        uniqueSeconds.append(seconds);
                        lastAddedSecond = seconds;
                    } else if (!uniqueSeconds.contains(seconds)) {
                        uniqueSeconds.append(seconds);
                        lastAddedSecond = seconds;
                    } else if (seconds == uniqueSeconds.first() && !firstSecondAddedAgain && lastAddedSecond != seconds) {
                        uniqueSeconds.append(seconds);
                        firstSecondAddedAgain = true;
                    }
                }
            }

//        for (int second : uniqueSeconds) {
//            qDebug() << second;
//        }

        for (count_number_of_sensorData_Array = 0; count_number_of_sensorData_Array < sensorDataArray.size(); count_number_of_sensorData_Array++)
        {
            do{
                Delay_MSec(10);
            }while(pauseindex);

            const QJsonValue &value = sensorDataArray[count_number_of_sensorData_Array];
            if (!value.isObject()) continue;
            QJsonObject sensorDataObject = value.toObject();

            timeStamp = sensorDataObject["timeStamp"].toString();
            QString new_lastPart = timeStamp.section(':', -1);  // get last part of timeStamp

            if (!previous_last_bit_TimeStamp.isEmpty() && previous_last_bit_TimeStamp != new_lastPart) {
                Pre_Slider_value = ui->horizontalSlider->value();
                Slider_value++;
                ui->horizontalSlider->setValue(Slider_value);
            }

            ui->textBrowser_TIMESTAMP->setText(timeStamp);
            leftFoot = sensorDataObject["leftFoot"].toBool();
            label = sensorDataObject["label"].toInt();
            sensorData = sensorDataObject["sensorData"].toArray();

            QList<int> sensorDataList;
            minVal = std::numeric_limits<int>::max();
            maxVal = std::numeric_limits<int>::min();
            for (const QJsonValue &sensorValue : sensorData)
            {
                sensorDataList.append(sensorValue.toInt());
                int val = sensorValue.toInt();
                if (val < minVal) minVal = val;
                if (val > maxVal) maxVal = val;
            }

            MainWindow::Visualization_one_sensor_group();
            previous_last_bit_TimeStamp = new_lastPart;
            Delay_MSec(10);
         }
    }
    else
    {
        QMessageBox::information(0,"info","Please check the sensors in the right side!!!");
    }
}


void MainWindow::on_pushButton_PAUSE_clicked()
{
     pauseindex = true;
}


void MainWindow::on_pushButton_BLUETOOTH_clicked()
{
//    MessageBox::information(this, "message", "start scan bluetooth...");//scan bluetooth after click button
//    SmolesManager* smo1 = new SmolesManager;
//    smo1->connect();
//    smo1->disconnect();
//    smo1->set_bluetooth_address("08:23:23:12");
//    smo1->start_measuring();
//    smo1->stop_measuring();

}

void MainWindow::on_pushButton_RECORD_clicked()
{
    if (jsonObjects.isEmpty()) {
        QMessageBox::information(this, "message", "no json file can be saved");
        return;
    }

    QJsonArray jsonArray;
    for (const QJsonObject &obj : jsonObjects) {
        jsonArray.append(obj);
    }

    QJsonDocument jsonDoc(jsonArray);
    QString filePath = QFileDialog::getSaveFileName(this, "保存 JSON 文件", "", "JSON 文件 (*.json);;所有文件 (*)");

    if (filePath.isEmpty()) {
        return;
    }

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "false", "can not save file");
        return;
    }

    file.write(jsonDoc.toJson());
    file.close();
    QMessageBox::information(this, "success", "JSON file saved successful");
}

void MainWindow::on_pushButton_CONTINUE_clicked()
{
     pauseindex = false;
}


void MainWindow::on_pushButton_FORWARD_clicked()
{
    if (count_number_of_sensorData_Array < sensorDataArray.size() - 1)
    {
        Slider_value = ui->horizontalSlider->value();
        Pre_Slider_value = ui->horizontalSlider->value();
        if (Slider_value < ui->horizontalSlider->maximum())
        {
            Slider_value++;
            ui->horizontalSlider->setValue(Slider_value);

            // 手动调用滑块释放的槽函数
            SLOT_of_Sliderdropped();
        }

        qDebug() << "forward to sensor group:" << count_number_of_sensorData_Array;
    }
}


void MainWindow::on_pushButton_REWIND_clicked()
{
    if (count_number_of_sensorData_Array > 0)
        {
            Slider_value = ui->horizontalSlider->value();
            Pre_Slider_value = ui->horizontalSlider->value();
            if (Slider_value > ui->horizontalSlider->minimum())
            {
                Slider_value--;
                ui->horizontalSlider->setValue(Slider_value);

                // 手动调用滑块释放的槽函数
                SLOT_of_Sliderdropped();
            }

            qDebug() << "rewind to sensor group:" << count_number_of_sensorData_Array;
        }
}

void MainWindow::on_pushButton_ANALYSIS_clicked()
{
    QString scriptPath = "D:\\GUI\\demo\\SMOLEs-desktop-application\\test1.py";

    QString cmd_qt = QString("conda activate smoles && python %1").arg(scriptPath);

    const char* cmd = cmd_qt.toLocal8Bit().constData();// convert the string to cmd command

    system(cmd);
}

void MainWindow::on_pushButton_RESET_clicked()
{
    Reset();
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
            for(int m = 0; m <infolist.size(); m++) { //这里是获取当前要处理的文件名
                qDebug() << infolist.at(m);
                ui->comboBox->addItem(infolist.at(m));
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

void MainWindow::Set_Jsonfile_name()
{
    Json_file_name = ui->comboBox->currentText();
    qDebug() << Json_file_name;
}

void MainWindow::Visualization_Reset()
{
    QList<RoundedRectItem*> RectItems =
    {
        RectItemR1, RectItemR2, RectItemR3, RectItemR4, RectItemR5, RectItemR6,
        RectItemR7, RectItemR8, RectItemR9, RectItemR10, RectItemR11, RectItemR12,
        RectItemR13, RectItemR14, RectItemR15, RectItemR16,RectItemL1, RectItemL2, RectItemL3, RectItemL4, RectItemL5, RectItemL6,
        RectItemL7, RectItemL8, RectItemL9, RectItemL10, RectItemL11, RectItemL12,
        RectItemL13, RectItemL14, RectItemL15, RectItemL16
    };

    for (int i = 0; i < RectItems.size();i++)
    {
        RectItems[i]->setColor(QColor(0,0,255));
    }

    Slider_value = 0;
    ui->horizontalSlider->setValue(Slider_value);

    ui->textBrowser_TIMESTAMP->clear();
    count_number_of_sensorData_Array = 0;
    pauseindex = true;

    uniqueSeconds.clear();
    firstSecondAddedAgain = false;
    lastAddedSecond = -1;
}

void MainWindow::Pressure_value_Reset()
{
    clearLines();
}

void MainWindow::Reset()
{
    Visualization_Reset();
    Pressure_value_Reset();
}

void MainWindow::Reset_Confirmwindow()//jump out a window let the user confirm whether they want to reset the visualization
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "select", "confirm or cancel?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes && pauseindex == false)
    {
        Visualization_Reset();
    }
    else if(reply == QMessageBox::Yes && pauseindex == true)
    {
        Visualization_Reset();
    }
}

void MainWindow::Run_visualization_automaticaly_window()
{
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "select", "Do you want to automatically run visualization for new Json file?",
                                      QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes && pauseindex == true)
        {
            ui->pushButton_RESET->click();
            pauseindex = false;
            Set_Jsonfile_name();
            ui->pushButton_VISUALIZATION->click();
        }
        else if(reply == QMessageBox::Yes && (!pauseindex == true))
        {
            ui->pushButton_RESET->click();
            pauseindex = false;
            Set_Jsonfile_name();
            ui->pushButton_VISUALIZATION->click();
        }
        else if (reply == QMessageBox::No && pauseindex == true)
        {
            ui->pushButton_RESET->click();
            Set_Jsonfile_name();
            QMessageBox::information(0,"Info","When you want, you need to click the PLAY button or continue button to start the viusalisation of new File");
        }
        else if(reply == QMessageBox::No && (!pauseindex == true))
        {
            ui->pushButton_RESET->click();
            Set_Jsonfile_name();
            QMessageBox::information(0,"Info","When you want, you need to click the PLAY button or continue button to start the viusalisation of new File");
        }
}

void MainWindow::Visualization_one_sensor_group()
{
    int count_single_sensorData_Array = 0;//this parameter for counting single sensor, maximum is 15
    for (const QJsonValue &sensorValue : sensorData)
    {
        int val = sensorValue.toInt();
//        qDebug() << "In json file" << Json_file_name << ",val of sensor group" << count_number_of_sensorData_Array  << "'s sensor " << count_single_sensorData_Array + 1 << "："<< val;
        int colorvalue = (int)(((val - minVal) / (double)(maxVal - minVal)) * 255);
//        qDebug() << "In json file" << Json_file_name << ",color of sensor group" << count_number_of_sensorData_Array << "'s sensor " << count_single_sensorData_Array + 1<< "：" << colorvalue;
      if(leftFoot)
        {

             QList<RoundedRectItem*> leftRectItems =
             {
                 RectItemL1, RectItemL2, RectItemL3, RectItemL4, RectItemL5, RectItemL6,
                 RectItemL7, RectItemL8, RectItemL9, RectItemL10, RectItemL11, RectItemL12,
                 RectItemL13, RectItemL14, RectItemL15, RectItemL16
             };

             QList<QCheckBox*> List_of_Checkbox_Left =
             {
                 ui->checkBox_LSensor1,ui->checkBox_LSensor2,ui->checkBox_LSensor3,ui->checkBox_LSensor4,ui->checkBox_LSensor5,ui->checkBox_LSensor6,ui->checkBox_LSensor7,ui->checkBox_LSensor8,ui->checkBox_LSensor9,
                 ui->checkBox_LSensor10,ui->checkBox_LSensor11,ui->checkBox_LSensor12,ui->checkBox_LSensor13,ui->checkBox_LSensor14,ui->checkBox_LSensor15,ui->checkBox_LSensor16
             };

             if (count_single_sensorData_Array < leftRectItems.size())
             {
                 if(List_of_Checkbox_Left[count_single_sensorData_Array]->isChecked())
                 {
                    QPointF point_(count_number_of_sensorData_Array,  val);
//                    680 - (val / 5000 * 650) - 30
                    switch (count_single_sensorData_Array)
                    {
                        case 0: {
                                    Draw_line_on_right_coordinate(Pre_Point_List_Left,count_single_sensorData_Array,point_,QPen(QColor(255, 0, 0)));
                                    break;
                                }
                        case 1: {
                                    Draw_line_on_right_coordinate(Pre_Point_List_Left,count_single_sensorData_Array,point_,QPen(QColor(0, 0, 255)));
                                    break;
                                }
                        case 2: {
                                    Draw_line_on_right_coordinate(Pre_Point_List_Left,count_single_sensorData_Array,point_,QPen(QColor(0, 255, 0)));
                                    break;
                                }
                        case 3: {
                                    Draw_line_on_right_coordinate(Pre_Point_List_Left,count_single_sensorData_Array,point_,QPen(QColor(0, 255, 255)));
                                    break;
                                }
                        case 4: {
                                    Draw_line_on_right_coordinate(Pre_Point_List_Left,count_single_sensorData_Array,point_,QPen(Qt::magenta));
                                    break;
                                }
                        case 5: {
                                    Draw_line_on_right_coordinate(Pre_Point_List_Left,count_single_sensorData_Array,point_,QPen(QColor(255, 165, 0)));
                                    break;
                                }
                        case 6:{
                                    Draw_line_on_right_coordinate(Pre_Point_List_Left,count_single_sensorData_Array,point_,QPen(Qt::white));
                                    break;
                                }
                        case 7:{
                                Draw_line_on_right_coordinate(Pre_Point_List_Left,count_single_sensorData_Array,point_,QPen(QColor(255, 192, 203)));
                                break;
                            }
                        case 8:{
                                Draw_line_on_right_coordinate(Pre_Point_List_Left,count_single_sensorData_Array,point_,QPen(QColor(0, 255, 0)));
                                break;
                            }
                        case 9: {
                                Draw_line_on_right_coordinate(Pre_Point_List_Left,count_single_sensorData_Array,point_,QPen(QColor(255, 215, 0)));
                                break;
                            }
                        case 10:{
                                Draw_line_on_right_coordinate(Pre_Point_List_Left,count_single_sensorData_Array,point_,QPen(QColor(238, 130, 238)));
                                break;
                            }
                        case 11:{
                                Draw_line_on_right_coordinate(Pre_Point_List_Left,count_single_sensorData_Array,point_,QPen(QColor(144, 238, 144)));
                                break;
                            }
                        case 12:{
                                Draw_line_on_right_coordinate(Pre_Point_List_Left,count_single_sensorData_Array,point_,QPen(QColor(240, 128, 128)));
                                break;
                            }
                        case 13:{
                                Draw_line_on_right_coordinate(Pre_Point_List_Left,count_single_sensorData_Array,point_,QPen(QColor(240, 230, 140)));
                                break;
                            }
                        case 14:{
                                Draw_line_on_right_coordinate(Pre_Point_List_Left,count_single_sensorData_Array,point_,QPen(QColor(64, 224, 208)));
                                break;
                            }
                        case 15:{
                                Draw_line_on_right_coordinate(Pre_Point_List_Left,count_single_sensorData_Array,point_,QPen(QColor(255, 160, 122)));
                                break;
                            }
                    }
                 }
                 leftRectItems[count_single_sensorData_Array]->setColor(QColor(colorvalue,0,255 - colorvalue));
             }
        }
        else
        {
              QList<RoundedRectItem*> rightRectItems =
              {
                  RectItemR1, RectItemR2, RectItemR3, RectItemR4, RectItemR5, RectItemR6,
                  RectItemR7, RectItemR8, RectItemR9, RectItemR10, RectItemR11, RectItemR12,
                  RectItemR13, RectItemR14, RectItemR15, RectItemR16
              };

              QList<QCheckBox*> List_of_Checkbox_Right =
              {
                  ui->checkBox_RSensor1,ui->checkBox_RSensor2,ui->checkBox_RSensor3,ui->checkBox_RSensor4,ui->checkBox_RSensor5,ui->checkBox_RSensor6,
                  ui->checkBox_RSensor7,ui->checkBox_RSensor8,ui->checkBox_RSensor9,ui->checkBox_RSensor10,ui->checkBox_RSensor11,ui->checkBox_RSensor12,
                  ui->checkBox_RSensor13,ui->checkBox_RSensor14,ui->checkBox_RSensor15,ui->checkBox_RSensor16
              };

              if(List_of_Checkbox_Right[count_single_sensorData_Array]->isChecked())
              {
                 QPointF point_(count_number_of_sensorData_Array, val);
                 switch (count_single_sensorData_Array)
                 {
                     case 0:{
                                 Draw_line_on_right_coordinate(Pre_Point_List_Right,count_single_sensorData_Array,point_,QPen(QColor(255, 0, 0)));
                                 break;
                             }
                     case 1:{
                     Draw_line_on_right_coordinate(Pre_Point_List_Right,count_single_sensorData_Array,point_,QPen(QColor(0, 0, 255)));
                     break;
                 }
                     case 2:{
                     Draw_line_on_right_coordinate(Pre_Point_List_Right,count_single_sensorData_Array,point_,QPen(QColor(0, 255, 0)));
                     break;
                 }
                     case 3:{
                     Draw_line_on_right_coordinate(Pre_Point_List_Right,count_single_sensorData_Array,point_,QPen(QColor(0, 255, 255)));
                     break;
                 }
                     case 4:{
                     Draw_line_on_right_coordinate(Pre_Point_List_Right,count_single_sensorData_Array,point_,QPen(Qt::magenta));
                     break;
                 }
                     case 5:{
                     Draw_line_on_right_coordinate(Pre_Point_List_Right,count_single_sensorData_Array,point_,QPen(QColor(255, 165, 0)));
                     break;
                 }
                     case 6:{
                     Draw_line_on_right_coordinate(Pre_Point_List_Right,count_single_sensorData_Array,point_,QPen(Qt::white));
                     break;
                 }
                     case 7:{
                     Draw_line_on_right_coordinate(Pre_Point_List_Right,count_single_sensorData_Array,point_,QPen(QColor(255, 192, 203)));
                     break;
                 }
                     case 8:{
                     Draw_line_on_right_coordinate(Pre_Point_List_Right,count_single_sensorData_Array,point_,QPen(QColor(0, 255, 0)));
                     break;
                 }
                     case 9:{
                     Draw_line_on_right_coordinate(Pre_Point_List_Right,count_single_sensorData_Array,point_,QPen(QColor(255, 215, 0)));
                     break;
                 }
                     case 10:{
                     Draw_line_on_right_coordinate(Pre_Point_List_Right,count_single_sensorData_Array,point_,QPen(QColor(238, 130, 238)));
                     break;
                 }
                     case 11:{
                     Draw_line_on_right_coordinate(Pre_Point_List_Right,count_single_sensorData_Array,point_,QPen(QColor(144, 238, 144)));
                     break;
                 }
                     case 12:{
                     Draw_line_on_right_coordinate(Pre_Point_List_Right,count_single_sensorData_Array,point_,QPen(QColor(240, 128, 128)));
                     break;
                 }
                     case 13:{
                     Draw_line_on_right_coordinate(Pre_Point_List_Right,count_single_sensorData_Array,point_,QPen(QColor(240, 230, 140)));
                     break;
                 }
                     case 14:{
                     Draw_line_on_right_coordinate(Pre_Point_List_Right,count_single_sensorData_Array,point_,QPen(QColor(64, 224, 208)));
                     break;
                 }
                     case 15:{
                     Draw_line_on_right_coordinate(Pre_Point_List_Right,count_single_sensorData_Array,point_,QPen(QColor(255, 160, 122)));
                     break;
                 }
                 }
              }

              if (count_single_sensorData_Array < rightRectItems.size()) {
                  rightRectItems[count_single_sensorData_Array]->setColor(QColor(colorvalue,0,255 - colorvalue));
              }
          }
         count_single_sensorData_Array++;
    }
}

void MainWindow::SLOT_of_Sliderdropped()
{
    pauseindex = true;
    QList<RoundedRectItem*> RectItems_ =
    {
        RectItemR1, RectItemR2, RectItemR3, RectItemR4, RectItemR5, RectItemR6,
        RectItemR7, RectItemR8, RectItemR9, RectItemR10, RectItemR11, RectItemR12,
        RectItemR13, RectItemR14, RectItemR15, RectItemR16,RectItemL1, RectItemL2, RectItemL3, RectItemL4, RectItemL5, RectItemL6,
        RectItemL7, RectItemL8, RectItemL9, RectItemL10, RectItemL11, RectItemL12,
        RectItemL13, RectItemL14, RectItemL15, RectItemL16
    };

    qDebug() << "SLOT_of_Sliderdropped()";
    for (int i = 0; i < RectItems_.size();i++)
    {
        RectItems_[i]->setColor(QColor(0,0,255));
    }

    ui->textBrowser_TIMESTAMP->clear();
    Pressure_value_Reset();

    Slider_value = ui->horizontalSlider->value();//滑块滑动之后的滑块值
    Different_between_pre_and_current_Slidervalue = Slider_value - Pre_Slider_value;//和滑动之前的滑块值之间的差值,也就相当于滑动了几个单位，因为可以往左右两个方向滑动，所以这个值可正可负
    Pre_Slider_value = Slider_value;//把当前的、滑块滑动之后的滑块值传给Pre_Slider_value

    int correspondingSecond = uniqueSeconds[Slider_value];
    qDebug() << "Corresponding second in uniqueSeconds:" << correspondingSecond;
    count_number_of_sensorData_Array = findFirstTimestampEndingWithnumberX(sensorDataArray,correspondingSecond);//当前的sensorDataArray中，第一个、timeStamp最后一位是 new_lastPart_slider的数据组的索引下标

    Visualization_after_Slider_dropped(count_number_of_sensorData_Array);

    //对Pressure value可视化的设置
    if (count_number_of_sensorData_Array > 0)
       {
           if(leftFoot)
           {
               for (int i = 0; i < Pre_Point_List_Left.size(); ++i)
               {
                   const QJsonValue &value_ = sensorDataArray[count_number_of_sensorData_Array - 1];
                   QJsonObject sensorDataObject_ = value_.toObject();
                   QJsonArray sensorData_ = sensorDataObject_["sensorData"].toArray();
                   int val_ = sensorData_[i].toInt();
                   Pre_Point_List_Left[i] = QPointF(50 + (count_number_of_sensorData_Array - 1) + (60.0 / 750.0), 680 - (val_ / 5000.0 * 650));
               }
           }
           else if(!leftFoot)
           {
               for (int i = 0; i < Pre_Point_List_Right.size(); ++i)
               {
                   const QJsonValue &value_ = sensorDataArray[count_number_of_sensorData_Array - 1];
                   QJsonObject sensorDataObject_ = value_.toObject();
                   QJsonArray sensorData_ = sensorDataObject_["sensorData"].toArray();
                   int val_ = sensorData_[i].toInt();
                   Pre_Point_List_Right[i] = QPointF(50 + (count_number_of_sensorData_Array - 1) + (60.0 / 750.0), 680 - (val_ / 5000.0 * 650));
               }
           }
       }


}

void MainWindow::Visualization_after_Slider_dropped(int count_number)
{
    QList<RoundedRectItem*> leftRectItems_ =
    {
        RectItemL1, RectItemL2, RectItemL3, RectItemL4, RectItemL5, RectItemL6,
        RectItemL7, RectItemL8, RectItemL9, RectItemL10, RectItemL11, RectItemL12,
        RectItemL13, RectItemL14, RectItemL15, RectItemL16
    };
    QList<RoundedRectItem*> rightRectItems_ =
    {
        RectItemR1, RectItemR2, RectItemR3, RectItemR4, RectItemR5, RectItemR6,
        RectItemR7, RectItemR8, RectItemR9, RectItemR10, RectItemR11, RectItemR12,
        RectItemR13, RectItemR14, RectItemR15, RectItemR16
    };

    const QJsonValue &value_ = sensorDataArray[count_number];
    QJsonObject sensorDataObject_ = value_.toObject();
    bool leftfoot_ = sensorDataObject_["leftFoot"].toBool();
    QJsonArray sensorData_ = sensorDataObject_["sensorData"].toArray();
//    timeStamp = sensorDataObject_["timeStamp"].toString();
//    ui->textBrowser_TIMESTAMP->setText(timeStamp);

    QList<int> sensorDataList;
    int minVal_ = std::numeric_limits<int>::max();
    int maxVal_ = std::numeric_limits<int>::min();
    for (const QJsonValue &sensorValue__ : sensorData_)
    {
        sensorDataList.append(sensorValue__.toInt());
        int val_ = sensorValue__.toInt();
        if (val_ < minVal_) minVal_ = val_;
        if (val_ > maxVal_) maxVal_ = val_;
    }


    if(leftfoot_)
    {
        for (int i = 0;i < sensorData_.size();i++ ) {
            const QJsonValue &sensorValue__ = sensorData_[i];
            int val__ = sensorValue__.toInt();
            QString str__ = QString::number(val__,'f', 2);
            int colorvalue__ = (int)(((val__ - minVal_) / (double)(maxVal_ - minVal_)) * 255);
            qDebug() << "Now is the visualization after slider dragged for jsonfile" << Json_file_name << ", leftfoot, sensor group number:" << count_number << ", sensor number:" << i << "value: " << val__;
            leftRectItems_[i]->setColor(QColor(colorvalue__,0,255 - colorvalue__));
        }
    }
    else
    {
        for (int i = 0;i < sensorData_.size();i++ ) {
            const QJsonValue &sensorValue__ = sensorData_[i];
            int val__ = sensorValue__.toInt();
            QString str__ = QString::number(val__,'f', 2);
            int colorvalue__ = (int)(((val__ - minVal_) / (double)(maxVal_ - minVal_)) * 255);
            qDebug() << "Now is the visualization after slider dragged for jsonfile" << Json_file_name << ", rightfoot, sensor group number:" << count_number << ", value of sensor " << i << "value: " << val__;
            rightRectItems_[i]->setColor(QColor(colorvalue__,0,255 - colorvalue__));
        }
    }    
}

void MainWindow::Draw_line_on_right_coordinate(QList<QPointF>& Pre_point_list, int count_single_sensorData_Array_, QPointF point__,QPen pen)
{

    if(count_number_of_sensorData_Array != 0)
    {
//        qDebug() << "X坐标：" << Pre_point_list[count_single_sensorData_Array_].x() << "Y坐标: " << Pre_point_list[count_single_sensorData_Array_].y();
        QGraphicsLineItem* line =  scene_Pressure_value->addLine(QLineF(Pre_point_list[count_single_sensorData_Array_].x(), Pre_point_list[count_single_sensorData_Array_].y(), 50 + point__.x() + (60.0 / 750.0), 680 - (point__.y() / 5000 * 650)), pen);
        lineGroup->addToGroup(line);
        Pre_point_list[count_single_sensorData_Array_] = QPointF(50 + point__.x() + (60.0 / 750.0), 680 - (point__.y() / 5000 * 650));
    }
    else if(count_number_of_sensorData_Array == 0)
    {
        Pre_point_list[count_single_sensorData_Array_] = QPoint(50 + point__.x() + (60.0 / 750.0), 680 - (point__.y() / 5000 * 650));
//        qDebug() << "X坐标：" << Pre_point_list[count_single_sensorData_Array_].x() << "Y坐标: " << Pre_point_list[count_single_sensorData_Array_].y();
    };
}

// 添加一个函数用于清除绘制的折线
void MainWindow::clearLines()
{
    scene_Pressure_value->removeItem(lineGroup);
    delete lineGroup;

    lineGroup = new QGraphicsItemGroup();
    scene_Pressure_value->addItem(lineGroup);
}

int MainWindow::findFirstTimestampEndingWithnumberX(const QJsonArray &sensorDataArray_,const int numberX) {

    for(int i = 0;i < sensorDataArray_.size();++i)
    {
        QJsonObject obj = sensorDataArray_[i].toObject();
        QString timeStamp_ = obj["timeStamp"].toString();
        int timeStamp_lastbit = timeStamp_.section(':', -1).toInt();
        if(!timeStamp_.isEmpty() && (timeStamp_lastbit == numberX))
        {
            qDebug() << obj;
            return i;
            break;
        }
    }
}



