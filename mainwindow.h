#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QFileDialog>

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

    QGraphicsScene *scene;
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

    int FindFile2(const QString& _filePath);
    void Delay_MSec(unsigned int msec);

    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QString headfilepath = "/home/max/sil_workspace/GUI-code/ex/sensordata";
    QStringList infolist;

};
#endif // MAINWINDOW_H
