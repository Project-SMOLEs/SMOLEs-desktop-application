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


    ui->comboBox->addItem(Combobox_defaultValue);
    ui->comboBox->setCurrentText(Combobox_defaultValue);
    connect(ui->comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(Set_Jsonfile_name()));
    connect(ui->comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(Reset_Confirmwindow()));
//    connect(ui->comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(Visualization_Reset()));

    ui->pushButton_VISUALIZATION->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));//set icon of buttons
    ui->pushButton_PAUSE->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    ui->pushButton_CONTINUE->setIcon(style()->standardIcon(QStyle::SP_ArrowRight));
    ui->pushButton_FORWARD->setIcon(style()->standardIcon(QStyle::SP_MediaSeekForward));
    ui->pushButton_REWIND->setIcon(style()->standardIcon(QStyle::SP_MediaSeekBackward));

    scene_Visualization = new QGraphicsScene(this);//set the scene of visualization
    scene_Visualization->setSceneRect(0,0,600,600);
    ui->graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    ui->graphicsView->setScene(scene_Visualization);//add the scene into graphview
    QPixmap pixmap("D:\\GUI\\demo\\SMOLEs-desktop-application\\image\\image.png");
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pixmap);

    // set the picture position
    item->setPos(50, 50);
    QRectF sceneRect = scene_Visualization->sceneRect();
    QSizeF sceneSize = sceneRect.size();
    QSize imageSize = pixmap.size();

    qreal scaleX = sceneSize.width() / imageSize.width();
    qreal scaleY = sceneSize.height() / imageSize.height();
    qreal scale = qMin(scaleX, scaleY);
    item->setScale(scale);
    scene_Visualization->addItem(item);


    scene_Pressure_value = new QGraphicsScene(this);
    ui->graphicsView_2->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
    scene_Pressure_value->setSceneRect(0,0,600,600);
    ui->graphicsView_2->setScene(scene_Pressure_value);
    // set Pen of Pressure value graph
    pen_Pressure_value.setColor(Qt::white);
    pen_Pressure_value.setWidth(2);
    brush_.setColor(Qt::white);
    brush_.setStyle(Qt::SolidPattern);
    ui->graphicsView_2->setRenderHint(QPainter::Antialiasing);

    // draw X and Yaxis
    scene_Pressure_value->addLine(QLineF(0, 600, 600, 600), pen_Pressure_value); // X轴
    scene_Pressure_value->addLine(QLineF(0, 600, 0, 0), pen_Pressure_value); // Y轴
//    ui->graphicsView_2->fitInView(scene_Pressure_value->sceneRect(), Qt::KeepAspectRatio);

//    // 定义折线图的数据点
//    QVector<QPointF> points = {
//        QPointF(0, 0),
//        QPointF(50, 30),
//        QPointF(100, 20),
//        QPointF(150, 80),
//        QPointF(200, 50)
//    };

//    // 绘制X轴和Y轴上的标签
//    for (int i = 0; i <= 200; i += 50) {
//        QGraphicsTextItem *textItem = scene_Pressure_value->addText(QString::number(i));
//        textItem->setPos(i, 105); // X轴标签
//    }

//    for (int i = 0; i <= 100; i += 20) {
//        QGraphicsTextItem *textItem = scene_Pressure_value->addText(QString::number(i));
//        textItem->setPos(-20, 100 - i); // Y轴标签
//    }

//    // 将数据点连成折线并添加到场景中
//    for (int i = 0; i < points.size() - 1; ++i) {
//        scene_Pressure_value->addLine(QLineF(points[i].x(), 100 - points[i].y(), points[i + 1].x(), 100 - points[i + 1].y()), pen_Pressure_value);
//    }



    RectItemL1 = new QGraphicsRectItem(0, 0, 30, 30);RectItemL1->setBrush(QColor(0,0,255));
    RectItemL2 = new QGraphicsRectItem(0, 0, 30, 30);RectItemL2->setBrush(QColor(0,0,255));
    RectItemL3 = new QGraphicsRectItem(0, 0, 30, 30);RectItemL3->setBrush(QColor(0,0,255));
    RectItemL4 = new QGraphicsRectItem(0, 0, 30, 30);RectItemL4->setBrush(QColor(0,0,255));
    RectItemL5 = new QGraphicsRectItem(0, 0, 30, 30);RectItemL5->setBrush(QColor(0,0,255));
    RectItemL6 = new QGraphicsRectItem(0, 0, 30, 30);RectItemL6->setBrush(QColor(0,0,255));
    RectItemL7 = new QGraphicsRectItem(0, 0, 30, 30);RectItemL7->setBrush(QColor(0,0,255));
    RectItemL8 = new QGraphicsRectItem(0, 0, 30, 30);RectItemL8->setBrush(QColor(0,0,255));
    RectItemL9 = new QGraphicsRectItem(0, 0, 30, 30);RectItemL9->setBrush(QColor(0,0,255));
    RectItemL10 = new QGraphicsRectItem(0, 0, 30, 30);RectItemL10->setBrush(QColor(0,0,255));
    RectItemL11 = new QGraphicsRectItem(0, 0, 30, 30);RectItemL11->setBrush(QColor(0,0,255));
    RectItemL12 = new QGraphicsRectItem(0, 0, 30, 30);RectItemL12->setBrush(QColor(0,0,255));
    RectItemL13 = new QGraphicsRectItem(0, 0, 30, 30);RectItemL13->setBrush(QColor(0,0,255));
    RectItemL14 = new QGraphicsRectItem(0, 0, 30, 30);RectItemL14->setBrush(QColor(0,0,255));
    RectItemL15 = new QGraphicsRectItem(0, 0, 30, 30);RectItemL15->setBrush(QColor(0,0,255));
    RectItemL16 = new QGraphicsRectItem(0, 0, 30, 30);RectItemL16->setBrush(QColor(0,0,255));

    RectItemR1 = new QGraphicsRectItem(0, 0, 30, 30);RectItemR1->setBrush(QColor(0,0,255));
    RectItemR2 = new QGraphicsRectItem(0, 0, 30, 30);RectItemR2->setBrush(QColor(0,0,255));
    RectItemR3 = new QGraphicsRectItem(0, 0, 30, 30);RectItemR3->setBrush(QColor(0,0,255));
    RectItemR4 = new QGraphicsRectItem(0, 0, 30, 30);RectItemR4->setBrush(QColor(0,0,255));
    RectItemR5 = new QGraphicsRectItem(0, 0, 30, 30);RectItemR5->setBrush(QColor(0,0,255));
    RectItemR6 = new QGraphicsRectItem(0, 0, 30, 30);RectItemR6->setBrush(QColor(0,0,255));
    RectItemR7 = new QGraphicsRectItem(0, 0, 30, 30);RectItemR7->setBrush(QColor(0,0,255));
    RectItemR8 = new QGraphicsRectItem(0, 0, 30, 30);RectItemR8->setBrush(QColor(0,0,255));
    RectItemR9 = new QGraphicsRectItem(0, 0, 30, 30);RectItemR9->setBrush(QColor(0,0,255));
    RectItemR10 = new QGraphicsRectItem(0, 0, 30, 30);RectItemR10->setBrush(QColor(0,0,255));
    RectItemR11 = new QGraphicsRectItem(0, 0, 30, 30);RectItemR11->setBrush(QColor(0,0,255));
    RectItemR12 = new QGraphicsRectItem(0, 0, 30, 30);RectItemR12->setBrush(QColor(0,0,255));
    RectItemR13 = new QGraphicsRectItem(0, 0, 30, 30);RectItemR13->setBrush(QColor(0,0,255));
    RectItemR14 = new QGraphicsRectItem(0, 0, 30, 30);RectItemR14->setBrush(QColor(0,0,255));
    RectItemR15 = new QGraphicsRectItem(0, 0, 30, 30);RectItemR15->setBrush(QColor(0,0,255));
    RectItemR16 = new QGraphicsRectItem(0, 0, 30, 30);RectItemR16->setBrush(QColor(0,0,255));//set sensor Item color and size

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

    RectItemR1->setPos(275,105);RectItemL1->setPos(110,100);//set sensor Item position
    RectItemR2->setPos(335,105);RectItemL2->setPos(170,100);
    RectItemR3->setPos(270,180);RectItemL3->setPos(80,180);
    RectItemR4->setPos(315,180);RectItemL4->setPos(130,180);
    RectItemR5->setPos(370,180);RectItemL5->setPos(180,180);
    RectItemR6->setPos(270,260);RectItemL6->setPos(70,260);
    RectItemR7->setPos(320,260);RectItemL7->setPos(125,260);
    RectItemR8->setPos(380,260);RectItemL8->setPos(180,260);
    RectItemR9->setPos(275,350);RectItemL9->setPos(80,350);
    RectItemR10->setPos(320,350);RectItemL10->setPos(130,350);
    RectItemR11->setPos(370,350);RectItemL11->setPos(170,350);
    RectItemR12->setPos(290,430);RectItemL12->setPos(90,430);
    RectItemR13->setPos(325,430);RectItemL13->setPos(125,430);
    RectItemR14->setPos(360,430);RectItemL14->setPos(165,430);
    RectItemR15->setPos(300,540);RectItemL15->setPos(100,540);
    RectItemR16->setPos(345,540);RectItemL16->setPos(155,540);



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
    if(target == ui->pushButton_VISUALIZATION)
    {
        if(event->type() == QEvent::HoverEnter)
        {
//            ui->pushButton_VISUALIZATION->setStyleSheet("QPushButton#pushButton_VISUALIZATION{border-radius: 8px;color: white;padding: 16px 32px;text-align: center;text-decoration: none;font-size: 16px;margin: 4px 2px;background-color: #e7e7e7;color: black;border: 2px solid #e7e7e7;}");
           ui->pushButton_VISUALIZATION->setStyleSheet("QPushButton#pushButton_VISUALIZATION{    color: #b1b1b1;border-image: url('D:/GUI/demo/SMOLEs-desktop-application/image/button-background@2x.9.png') 0 0 0 0 stretch stretch;border-width: 1px;border-color: #1e1e1e;border-style: solid;border-radius: 6;padding: 3px;font-size: 12px;padding-left: 5px;padding-right: 5px;}");
        }

        if(event->type() == QEvent::HoverLeave)
        {
            ui->pushButton_VISUALIZATION->setStyleSheet("QPushButton#pushButton_VISUALIZATION{border-radius: 8px;color: white;padding: 16px 32px;text-align: center;text-decoration: none;font-size: 16px;margin: 4px 2px;background-color: white;color: black;border: 2px solid #e7e7e7;}");
        }

        if(event->type() == QEvent::MouseButtonPress)
        {
            ui->pushButton_VISUALIZATION->setStyleSheet("QPushButton#pushButton_VISUALIZATION{border-radius: 8px;color: white;padding: 16px 32px;text-align: center;text-decoration: none;font-size: 16px;margin: 4px 2px;background-color: #06AD56;color: black;border: 2px solid #e7e7e7;}");
        }
    }

    if(target == ui->pushButton_PAUSE)
    {
        if(event->type() == QEvent::HoverEnter)
        {
             ui->pushButton_PAUSE->setStyleSheet("QPushButton#pushButton_PAUSE{border-radius: 8px;color: white;padding: 16px 32px;text-align: center;text-decoration: none;font-size: 16px;margin: 4px 2px;background-color: #e7e7e7;color: black;border: 2px solid #e7e7e7;}");
        }

        if(event->type() == QEvent::HoverLeave)
        {
            ui->pushButton_PAUSE->setStyleSheet("QPushButton#pushButton_PAUSE{border-radius: 8px;color: white;padding: 16px 32px;text-align: center;text-decoration: none;font-size: 16px;margin: 4px 2px;background-color: white;color: black;border: 2px solid #e7e7e7;}");
        }

        if(event->type() == QEvent::MouseButtonPress)
        {
            ui->pushButton_PAUSE->setStyleSheet("QPushButton#pushButton_PAUSE{border-radius: 8px;color: white;padding: 16px 32px;text-align: center;text-decoration: none;font-size: 16px;margin: 4px 2px;background-color: #ff0000;color: black;border: 2px solid #e7e7e7;}");
        }
    }

    if(target == ui->pushButton_BLUETOOTH)
    {
        if(event->type() == QEvent::HoverEnter)
        {
             ui->pushButton_BLUETOOTH->setStyleSheet("QPushButton#pushButton_BLUETOOTH{border-radius: 8px;color: white;padding: 16px 32px;text-align: center;text-decoration: none;font-size: 16px;margin: 4px 2px;background-color: #e7e7e7;color: black;border: 2px solid #e7e7e7;}");
        }

        if(event->type() == QEvent::HoverLeave)
        {
            ui->pushButton_BLUETOOTH->setStyleSheet("QPushButton#pushButton_BLUETOOTH{border-radius: 8px;color: white;padding: 16px 32px;text-align: center;text-decoration: none;font-size: 16px;margin: 4px 2px;background-color: white;color: black;border: 2px solid #e7e7e7;}");
        }

        if(event->type() == QEvent::MouseButtonPress)
        {
            ui->pushButton_BLUETOOTH->setStyleSheet("QPushButton#pushButton_BLUETOOTH{border-radius: 8px;color: white;padding: 16px 32px;text-align: center;text-decoration: none;font-size: 16px;margin: 4px 2px;background-color: #00FFFF;color: black;border: 2px solid #e7e7e7;}");
        }
    }

    if(target == ui->pushButton_RECORD)
    {
        if(event->type() == QEvent::HoverEnter)
        {
             ui->pushButton_RECORD->setStyleSheet("QPushButton#pushButton_RECORD{border-radius: 8px;color: white;padding: 16px 32px;text-align: center;text-decoration: none;font-size: 16px;margin: 4px 2px;background-color: #e7e7e7;color: black;border: 2px solid #e7e7e7;}");
        }

        if(event->type() == QEvent::HoverLeave)
        {
            ui->pushButton_RECORD->setStyleSheet("QPushButton#pushButton_RECORD{border-radius: 8px;color: white;padding: 16px 32px;text-align: center;text-decoration: none;font-size: 16px;margin: 4px 2px;background-color: white;color: black;border: 2px solid #e7e7e7;}");
        }

        if(event->type() == QEvent::MouseButtonPress)
        {
            ui->pushButton_RECORD->setStyleSheet("QPushButton#pushButton_RECORD{border-radius: 8px;color: white;padding: 16px 32px;text-align: center;text-decoration: none;font-size: 16px;margin: 4px 2px;background-color: #5500ff;color: black;border: 2px solid #e7e7e7;}");
        }
    }

    if(target == ui->pushButton_CONTINUE)
    {
        if(event->type() == QEvent::HoverEnter)
        {
             ui->pushButton_CONTINUE->setStyleSheet("QPushButton#pushButton_CONTINUE{border-radius: 8px;color: white;padding: 16px 32px;text-align: center;text-decoration: none;font-size: 16px;margin: 4px 2px;background-color: #e7e7e7;color: black;border: 2px solid #e7e7e7;}");
        }

        if(event->type() == QEvent::HoverLeave)
        {
            ui->pushButton_CONTINUE->setStyleSheet("QPushButton#pushButton_CONTINUE{border-radius: 8px;color: white;padding: 16px 32px;text-align: center;text-decoration: none;font-size: 16px;margin: 4px 2px;background-color: white;color: black;border: 2px solid #e7e7e7;}");
        }

        if(event->type() == QEvent::MouseButtonPress)
        {
            ui->pushButton_CONTINUE->setStyleSheet("QPushButton#pushButton_CONTINUED{border-radius: 8px;color: white;padding: 16px 32px;text-align: center;text-decoration: none;font-size: 16px;margin: 4px 2px;background-color: #3300ff;color: black;border: 2px solid #e7e7e7;}");
        }
    }

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
        qDebug() << 1;
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

        for (count_number_of_sensorData_Array = 0; count_number_of_sensorData_Array < sensorDataArray.size(); count_number_of_sensorData_Array++)
        {
            do{
                Delay_MSec(100);
            }while(pauseindex);

            const QJsonValue &value = sensorDataArray[count_number_of_sensorData_Array];
            if (!value.isObject()) continue;
            QJsonObject sensorDataObject = value.toObject();

            timeStamp = sensorDataObject["timeStamp"].toInt();
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
            Slider_value++;
            ui->horizontalSlider->setValue(Slider_value);
            Delay_MSec(200);
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
    if((pauseindex == true) && (count_number_of_sensorData_Array < 59))
    {
        count_number_of_sensorData_Array++;
        qDebug() << "forward to sensor group:" << count_number_of_sensorData_Array;
    }
}


void MainWindow::on_pushButton_REWIND_clicked()
{
    if((pauseindex == true) && (count_number_of_sensorData_Array < 59))
    {
        count_number_of_sensorData_Array--;
        qDebug() << "rewind to sensor group:" << count_number_of_sensorData_Array;
    }
}

void MainWindow::on_pushButton_ANALYSIS_clicked()
{
    QString scriptPath = "D:\\GUI\\demo\\SMOLEs-desktop-application\\test.py";

    QString cmd_qt = QString("python %1").arg(scriptPath);

    const char* cmd = cmd_qt.toLocal8Bit().constData();// convert the string to cmd command

    system(cmd);
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
    QList<QGraphicsRectItem*> RectItems =
    {
        RectItemR1, RectItemR2, RectItemR3, RectItemR4, RectItemR5, RectItemR6,
        RectItemR7, RectItemR8, RectItemR9, RectItemR10, RectItemR11, RectItemR12,
        RectItemR13, RectItemR14, RectItemR15, RectItemR16,RectItemL1, RectItemL2, RectItemL3, RectItemL4, RectItemL5, RectItemL6,
        RectItemL7, RectItemL8, RectItemL9, RectItemL10, RectItemL11, RectItemL12,
        RectItemL13, RectItemL14, RectItemL15, RectItemL16
    };

    for (int i = 0; i < RectItems.size();i++)
    {
        RectItems[i]->setBrush(QColor(0,0,255));
    }

    for (int i = 0; i < 50; ++i) {
        qDebug() << endl;
    }

    Slider_value = 0;
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "select", "Do you want to automatically run visualization for new Json file?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes && pauseindex == true)
    {
        pauseindex = false;
        ui->pushButton_VISUALIZATION->click();
    }
    else if(reply == QMessageBox::Yes && (!pauseindex == true))
    {
        ui->pushButton_VISUALIZATION->click();
    }


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
        pauseindex = false;
    }
}

void MainWindow::Visualization_one_sensor_group()
{
    int count_single_sensorData_Array = 0;//this parameter for counting single sensor, maximum is 15
    for (const QJsonValue &sensorValue : sensorData)
    {
        int val = sensorValue.toInt();
        qDebug() << "In json file" << Json_file_name << ",val of sensor group" << count_number_of_sensorData_Array  << "'s sensor " << count_single_sensorData_Array + 1 << "："<< val;
        int colorvalue = (int)(((val - minVal) / (double)(maxVal - minVal)) * 255);
        qDebug() << "In json file" << Json_file_name << ",color of sensor group" << count_number_of_sensorData_Array << "'s sensor " << count_single_sensorData_Array + 1<< "：" << colorvalue;
      if(leftFoot)
        {

             QList<QGraphicsRectItem*> leftRectItems =
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
                    QPointF point_(count_number_of_sensorData_Array + 1, val);
                    switch (count_single_sensorData_Array)
                    {
                        case 0: {Point_List_Left[count_single_sensorData_Array].append(point_);break;}
                        case 1: {Point_List_Left[count_single_sensorData_Array].append(point_);break;}
                        case 2: {Point_List_Left[count_single_sensorData_Array].append(point_);break;}
                        case 3: {Point_List_Left[count_single_sensorData_Array].append(point_);break;}
                        case 4: {Point_List_Left[count_single_sensorData_Array].append(point_);break;}
                        case 5: {
                                    if(count_number_of_sensorData_Array != 0)
                                    {
                                        scene_Pressure_value->addLine(QLineF(previousPoint_.x(), previousPoint_.y(), point_.x()*10, 600 - point_.y() - 2), QPen(Qt::yellow));
                                    }
                                    previousPoint_ = QPointF(point_.x()*10, 600 - point_.y() - 2);
                                    break;
                                }
                        case 6:{
                                    if(count_number_of_sensorData_Array != 0)
                                    {
                                        scene_Pressure_value->addLine(QLineF(previousPoint.x(), previousPoint.y(), point_.x()*10, 600 - point_.y() - 2), pen_Pressure_value);
                                    }
                                    previousPoint = QPointF(point_.x()*10, 600 - point_.y() - 2);
                                    break;
                                }
                        case 7: Point_List_Left[count_single_sensorData_Array].append(point_);
                        case 8: Point_List_Left[count_single_sensorData_Array].append(point_);
                        case 9: Point_List_Left[count_single_sensorData_Array].append(point_);
                        case 10: Point_List_Left[count_single_sensorData_Array].append(point_);
                        case 11: Point_List_Left[count_single_sensorData_Array].append(point_);
                        case 12: Point_List_Left[count_single_sensorData_Array].append(point_);
                        case 13: Point_List_Left[count_single_sensorData_Array].append(point_);
                        case 14: Point_List_Left[count_single_sensorData_Array].append(point_);
                        case 15: Point_List_Left[count_single_sensorData_Array].append(point_);
                    }
//                    Point_List_Left[count_single_sensorData_Array].append(point_);
//                    scene_Pressure_value->addEllipse(point_.x()*10, 600 - (point_.y() + 10) - 2, 10, 10, pen_Pressure_value, brush_);
                 }

//                 leftTextBrowsers[count_single_sensorData_Array]->setText(str);
                 leftRectItems[count_single_sensorData_Array]->setBrush(QColor(0,0,255));
                 leftRectItems[count_single_sensorData_Array]->setBrush(QColor(colorvalue,0,255 - colorvalue));
             }
        }
        else
        {
              QList<QGraphicsRectItem*> rightRectItems =
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
                 QPointF point_(count_number_of_sensorData_Array + 1, val);
                 switch (count_single_sensorData_Array)
                 {
                     case 0: Point_List_Right[count_single_sensorData_Array].append(point_);
                     case 1: Point_List_Right[count_single_sensorData_Array].append(point_);
                     case 2: Point_List_Right[count_single_sensorData_Array].append(point_);
                     case 3: Point_List_Right[count_single_sensorData_Array].append(point_);
                     case 4: Point_List_Right[count_single_sensorData_Array].append(point_);
                     case 5: Point_List_Right[count_single_sensorData_Array].append(point_);
                     case 6: Point_List_Right[count_single_sensorData_Array].append(point_);scene_Pressure_value->addEllipse(point_.x() - 2, 100 - point_.y() - 2, 4, 4, pen_Pressure_value, brush_);
                     case 7: Point_List_Right[count_single_sensorData_Array].append(point_);
                     case 8: Point_List_Right[count_single_sensorData_Array].append(point_);
                     case 9: Point_List_Right[count_single_sensorData_Array].append(point_);
                     case 10: Point_List_Right[count_single_sensorData_Array].append(point_);
                     case 11: Point_List_Right[count_single_sensorData_Array].append(point_);
                     case 12: Point_List_Right[count_single_sensorData_Array].append(point_);
                     case 13: Point_List_Right[count_single_sensorData_Array].append(point_);
                     case 14: Point_List_Right[count_single_sensorData_Array].append(point_);
                     case 15: Point_List_Right[count_single_sensorData_Array].append(point_);
                 }
              }

              if (count_single_sensorData_Array < rightRectItems.size()) {
//                  rightTextBrowsers[count_single_sensorData_Array]->setText(str);
                  rightRectItems[count_single_sensorData_Array]->setBrush(QColor(0,0,255));
                  rightRectItems[count_single_sensorData_Array]->setBrush(QColor(colorvalue,0,255 - colorvalue));
              }
          }
         count_single_sensorData_Array++;
    }
}

void MainWindow::SLOT_of_Sliderdropped()
{
    QList<QGraphicsRectItem*> RectItems_ =
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
        RectItems_[i]->setBrush(QColor(0,0,255));
    }
    count_number_of_sensorData_Array = ui->horizontalSlider->value();
    Slider_value = count_number_of_sensorData_Array;
    Visualization_after_Slider_dropped(count_number_of_sensorData_Array);
    pauseindex = true;

}

void MainWindow::Visualization_after_Slider_dropped(int count_number)
{
    QList<QGraphicsRectItem*> leftRectItems_ =
    {
        RectItemL1, RectItemL2, RectItemL3, RectItemL4, RectItemL5, RectItemL6,
        RectItemL7, RectItemL8, RectItemL9, RectItemL10, RectItemL11, RectItemL12,
        RectItemL13, RectItemL14, RectItemL15, RectItemL16
    };
    QList<QGraphicsRectItem*> rightRectItems_ =
    {
        RectItemR1, RectItemR2, RectItemR3, RectItemR4, RectItemR5, RectItemR6,
        RectItemR7, RectItemR8, RectItemR9, RectItemR10, RectItemR11, RectItemR12,
        RectItemR13, RectItemR14, RectItemR15, RectItemR16
    };

    const QJsonValue &value_ = sensorDataArray[count_number];
    QJsonObject sensorDataObject_ = value_.toObject();
    bool leftfoot_ = sensorDataObject_["leftFoot"].toBool();
    QJsonArray sensorData_ = sensorDataObject_["sensorData"].toArray();

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
            leftRectItems_[i]->setBrush(QColor(colorvalue__,0,255 - colorvalue__));
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
            rightRectItems_[i]->setBrush(QColor(colorvalue__,0,255 - colorvalue__));
        }
    }
}




