#ifndef LEDWALLSTUDIO_LEDWALLCONFIGWIDGET_H
#define LEDWALLSTUDIO_LEDWALLCONFIGWIDGET_H

#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE
class QSpinBox;
QT_END_NAMESPACE

class HttpConnector;

// configure remote settings
class LedWallConfigWidget : public QWidget
{
Q_OBJECT

public:
    explicit LedWallConfigWidget(HttpConnector *httpConnector, QWidget *parent = nullptr);

protected slots:
    void loadConfig();
    void saveConfig();

protected:
    HttpConnector *m_httpConnector;

    void createUi();
    QSpinBox *m_editBrightness;
};

#endif //LEDWALLSTUDIO_LEDWALLCONFIGWIDGET_H
