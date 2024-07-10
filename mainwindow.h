#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QFileDialog>
#include <QJsonArray>
#include "RoundedRectItem.h"
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
    QGraphicsScene *scene_Logo;
    RoundedRectItem *RectItemR1;
    RoundedRectItem *RectItemR2;
    RoundedRectItem *RectItemR3;
    RoundedRectItem *RectItemR4;
    RoundedRectItem *RectItemR5;
    RoundedRectItem *RectItemR6;
    RoundedRectItem *RectItemR7;
    RoundedRectItem *RectItemR8;
    RoundedRectItem *RectItemR9;
    RoundedRectItem *RectItemR10;
    RoundedRectItem *RectItemR11;
    RoundedRectItem *RectItemR12;
    RoundedRectItem *RectItemR13;
    RoundedRectItem *RectItemR14;
    RoundedRectItem *RectItemR15;
    RoundedRectItem *RectItemR16;

    RoundedRectItem *RectItemL1;
    RoundedRectItem *RectItemL2;
    RoundedRectItem *RectItemL3;
    RoundedRectItem *RectItemL4;
    RoundedRectItem *RectItemL5;
    RoundedRectItem *RectItemL6;
    RoundedRectItem *RectItemL7;
    RoundedRectItem *RectItemL8;
    RoundedRectItem *RectItemL9;
    RoundedRectItem *RectItemL10;
    RoundedRectItem *RectItemL11;
    RoundedRectItem *RectItemL12;
    RoundedRectItem *RectItemL13;
    RoundedRectItem *RectItemL14;
    RoundedRectItem *RectItemL15;
    RoundedRectItem *RectItemL16;



    int FindFile2(const QString& _filePath);
    void Delay_MSec(unsigned int msec);
    void Visualization_one_sensor_group();
    void Visualization_after_Slider_dropped(int);
    void Check_states_of_allcheckbox();
    void Draw_line_on_right_coordinate(QList<QPointF>&,int,QPointF, QPen);


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

    int label, minVal, maxVal;
    bool leftFoot, sign_of_checkbox;
    QString timeStamp;
    QJsonArray sensorData;
    bool pauseindex = false;
    int count_number_of_sensorData_Array;//this parameter for counting the number of sensor Data array, maximum is 58
    int Slider_value = 0;
    QPen pen_Pressure_value;
    QBrush brush_;

    QPoint Pre_LSensor1,Pre_LSensor2,Pre_LSensor3,Pre_LSensor4,Pre_LSensor5,Pre_LSensor6,Pre_LSensor7,Pre_LSensor8,Pre_LSensor9,Pre_LSensor10,
           Pre_LSensor11,Pre_LSensor12,Pre_LSensor13,Pre_LSensor14,Pre_LSensor15,Pre_LSensor16,Pre_RSensor1,Pre_RSensor2,Pre_RSensor3,
           Pre_RSensor4,Pre_RSensor5,Pre_RSensor6,Pre_RSensor7,Pre_RSensor8,Pre_RSensor9,Pre_RSensor10,Pre_RSensor11,Pre_RSensor12,Pre_RSensor13,Pre_RSensor14,
           Pre_RSensor15,Pre_RSensor16;

    QList<QPointF>Pre_Point_List_Left =
    {
        Pre_LSensor1,Pre_LSensor2,Pre_LSensor3,Pre_LSensor4,
        Pre_LSensor5,Pre_LSensor6,Pre_LSensor7,Pre_LSensor8,
        Pre_LSensor9,Pre_LSensor10,Pre_LSensor11,Pre_LSensor12,
        Pre_LSensor13,Pre_LSensor14,Pre_LSensor15,Pre_LSensor16
    };
    QList<QPointF>Pre_Point_List_Right =
    {
        Pre_RSensor1,Pre_RSensor2,Pre_RSensor3,Pre_RSensor4,
        Pre_RSensor5,Pre_RSensor6,Pre_RSensor7,Pre_RSensor8,
        Pre_RSensor9,Pre_RSensor10,Pre_RSensor11,Pre_RSensor12,
        Pre_RSensor13,Pre_RSensor14,Pre_RSensor15,Pre_RSensor16
    };


};
#endif // MAINWINDOW_H
