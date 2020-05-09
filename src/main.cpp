#include <QtWidgets/QApplication>
#include <QtCore/QSettings>
#include "BitmapEditorWidget.h"

int main(int argc, char* argv[])
{
    QApplication::setOrganizationName("nehlsen");
    QApplication::setApplicationName("ledwall-studio");
    QApplication app(argc, argv);

//     QSettings settings;
//     if (!settings.contains("mqtt/host")) settings.setValue("mqtt/host", "10.13.37.39");
//     settings.sync();

     auto *main = new BitmapEditorWidget();
     main->resize(250, 250);
     main->show();

    return app.exec();
}
