#include <QtWidgets/QApplication>
#include "MainWindow.h"

int main(int argc, char* argv[])
{
    QApplication::setOrganizationName("nehlsen");
    QApplication::setApplicationName("ledwall-studio-simulator");
    QApplication app(argc, argv);

    auto *mainWin = new MainWindow;
    mainWin->show();

    return app.exec();
}
