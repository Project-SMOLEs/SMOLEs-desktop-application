#include "mainwindow.h"
#include "SmolesManager.h"
#include <QApplication>
#include <QUiLoader>
#include <QFile>
#include <QWidget>
#include <QPushButton>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QColor>
#include <QTextStream>
#include <QDebug>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    // 加载并应用.qss文件
    QString qssPath = "D:\\GUI\\demo\\SMOLEs-desktop-application\\style1.qss";
    QFile file(qssPath);

    // 打印文件路径进行调试
    qDebug() << "Attempting to open:" << QFileInfo(file).absoluteFilePath();

    if (QFileInfo::exists(qssPath) && QFileInfo(qssPath).isFile()) {
        qDebug() << "File exists.";
    } else {
        qDebug() << "File does not exist.";
    }

    if (file.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(file.readAll());
        a.setStyleSheet(styleSheet);
        file.close(); // 关闭文件
    } else {
        qWarning() << "Could not open the stylesheet file.";
    }


    w.show();
    return a.exec();
}
