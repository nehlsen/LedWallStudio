#ifndef LEDWALLSTUDIO_LEDWALLCONFIGWIDGET_H
#define LEDWALLSTUDIO_LEDWALLCONFIGWIDGET_H

#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE
class QSpinBox;
class QComboBox;
class QCheckBox;
class QLineEdit;
QT_END_NAMESPACE

class HttpConnector;

namespace LedWall::Studio {

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

    QSpinBox *m_editMatrixWidth;
    QSpinBox *m_editMatrixHeight;
    QSpinBox *m_editBrightness;

    QComboBox *m_comboPowerOnResetMode;
    QCheckBox *m_checkRecoverLastMode;
    QComboBox *m_comboModeToBootInto;

    QLineEdit *m_editMqttBroker;
    QLineEdit *m_editMqttDeviceTopic;
    QLineEdit *m_editMqttGroupTopic;
};

}

#endif //LEDWALLSTUDIO_LEDWALLCONFIGWIDGET_H
