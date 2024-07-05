#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QFileDialog>
#include <QJsonArray>
#include "Thread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    void toInstallEventFilter();
    bool eventFilter(QObject *target, QEvent *event);

    QGraphicsScene *scene_Visualization;
    QGraphicsScene *scene_Pressure_value;
    QGraphicsRectItem *RectItemR1;
    QGraphicsRectItem *RectItemR2;
    QGraphicsRectItem *RectItemR3;
    QGraphicsRectItem *RectItemR4;
    QGraphicsRectItem *RectItemR5;
    QGraphicsRectItem *RectItemR6;
    QGraphicsRectItem *RectItemR7;
    QGraphicsRectItem *RectItemR8;
    QGraphicsRectItem *RectItemR9;
    QGraphicsRectItem *RectItemR10;
    QGraphicsRectItem *RectItemR11;
    QGraphicsRectItem *RectItemR12;
    QGraphicsRectItem *RectItemR13;
    QGraphicsRectItem *RectItemR14;
    QGraphicsRectItem *RectItemR15;
    QGraphicsRectItem *RectItemR16;

    QGraphicsRectItem *RectItemL1;
    QGraphicsRectItem *RectItemL2;
    QGraphicsRectItem *RectItemL3;
    QGraphicsRectItem *RectItemL4;
    QGraphicsRectItem *RectItemL5;
    QGraphicsRectItem *RectItemL6;
    QGraphicsRectItem *RectItemL7;
    QGraphicsRectItem *RectItemL8;
    QGraphicsRectItem *RectItemL9;
    QGraphicsRectItem *RectItemL10;
    QGraphicsRectItem *RectItemL11;
    QGraphicsRectItem *RectItemL12;
    QGraphicsRectItem *RectItemL13;
    QGraphicsRectItem *RectItemL14;
    QGraphicsRectItem *RectItemL15;
    QGraphicsRectItem *RectItemL16;



    int FindFile2(const QString& _filePath);
    void Delay_MSec(unsigned int msec);
    void Visualization_one_sensor_group();
    void Visualization_after_Slider_dropped(int);
    void Check_states_of_allcheckbox();


    ~MainWindow();


private slots:
    void on_pushButton_VISUALIZATION_clicked();
    void on_pushButton_PAUSE_clicked();
    void on_pushButton_BLUETOOTH_clicked();
    void on_pushButton_RECORD_clicked();
    void on_pushButton_CONTINUE_clicked();
    void on_pushButton_FORWARD_clicked();
    void on_pushButton_REWIND_clicked();

    void Set_Jsonfile_name();
    void Visualization_Reset();
    void Reset_Confirmwindow();
    void on_pushButton_ANALYSIS_clicked();
    void SLOT_of_Sliderdropped();


private:
    Ui::MainWindow *ui;

    QString headfilepath = "D:\\GUI\\demo\\SMOLEs-desktop-application\\sensordata";
    QString Json_file_name;
    QString Json_file_folder_path = "D:\\GUI\\demo\\SMOLEs-desktop-application\\sensordata";
    QString Combobox_defaultValue = "Json file selection";
    QStringList infolist;
    QVector<QJsonObject> jsonObjects; // to store json data
    QJsonArray sensorDataArray;

    Thread *thread1;
    Thread *thread2;

    int timeStamp, label, minVal, maxVal;
    bool leftFoot, sign_of_checkbox;
    QJsonArray sensorData;
    bool pauseindex = false;
    int count_number_of_sensorData_Array;//this parameter for counting the number of sensor Data array, maximum is 58
    int Slider_value = 0;
    QPen pen_Pressure_value;
    QBrush brush_;

    QList<QPointF>LSensor1_;QList<QPointF>LSensor2_;QList<QPointF>LSensor3_;QList<QPointF>LSensor4_;QList<QPointF>LSensor5_;QList<QPointF>LSensor6_;
    QList<QPointF>LSensor7_;QList<QPointF>LSensor8_;QList<QPointF>LSensor9_;QList<QPointF>LSensor10_;QList<QPointF>LSensor11_;QList<QPointF>LSensor12_;
    QList<QPointF>LSensor13_;QList<QPointF>LSensor14_;QList<QPointF>LSensor15_;QList<QPointF>LSensor16_;
    QList<QPointF>RSensor1_;QList<QPointF>RSensor2_;QList<QPointF>RSensor3_;QList<QPointF>RSensor4_;QList<QPointF>RSensor5_;QList<QPointF>RSensor6_;
    QList<QPointF>RSensor7_;QList<QPointF>RSensor8_;QList<QPointF>RSensor9_;QList<QPointF>RSensor10_;QList<QPointF>RSensor11_;QList<QPointF>RSensor12_;
    QList<QPointF>RSensor13_;QList<QPointF>RSensor14_;QList<QPointF>RSensor15_;QList<QPointF>RSensor16_;

    QList<QList<QPointF>>Point_List_Left =
    {
        LSensor1_,LSensor2_,LSensor3_,LSensor4_,LSensor5_,LSensor6_,
        LSensor7_,LSensor8_,LSensor9_,LSensor10_,LSensor11_,LSensor12_,
        LSensor13_,LSensor14_,LSensor15_,LSensor16_
    };
    QList<QList<QPointF>>Point_List_Right =
    {
        RSensor1_,RSensor2_,RSensor3_,RSensor4_,RSensor5_,RSensor6_,
        RSensor7_,RSensor8_,RSensor9_,RSensor10_,RSensor11_,RSensor12_,
        RSensor13_,RSensor14_,RSensor15_,RSensor16_
    };
    QPointF previousPoint;
    QPointF previousPoint_;
};
#endif // MAINWINDOW_H
