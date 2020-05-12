#ifndef LEDWALLSTUDIO_MODECONFIGWIDGET_H
#define LEDWALLSTUDIO_MODECONFIGWIDGET_H

#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE
class QComboBox;
QT_END_NAMESPACE

class HttpConnector;

class ModeConfigWidget : public QWidget
{
Q_OBJECT

public:
    explicit ModeConfigWidget(HttpConnector *httpConnector, QWidget *parent = nullptr);

protected slots:
    void onActiveModeChanged();

protected:
    HttpConnector *m_httpConnector;

    void createUi();
    QComboBox *m_selectMode;
};

#endif //LEDWALLSTUDIO_MODECONFIGWIDGET_H
