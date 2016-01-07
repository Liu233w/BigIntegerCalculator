#include "mainwindow.h"
#include <QApplication>
#include <QObject>
#include <QScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //主窗口退出之后即使about_dialog没有退出也会关闭程序
    QObject::connect(&a,
                     SIGNAL(lastWindowClosed()),
                     &a,
                     SLOT(quit())
                     );

    return a.exec();
}
