#include "mainwindow.h"
#include <QApplication>
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QObject::connect(&a,
                     SIGNAL(lastWindowClosed()),
                     &a,
                     SLOT(quit())
                     );

    return a.exec();
}
