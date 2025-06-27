#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    qInstallMessageHandler(nullptr);
    MainWindow window;
    window.show();
    return app.exec();


}
