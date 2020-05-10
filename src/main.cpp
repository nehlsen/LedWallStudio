#include <QtWidgets/QApplication>
#include "MainWindow.h"

int main(int argc, char* argv[])
{
    QApplication::setOrganizationName("nehlsen");
    QApplication::setApplicationName("ledwall-studio");
    QApplication app(argc, argv);

     auto *main = new MainWindow();
     main->show();

    return app.exec();
}
