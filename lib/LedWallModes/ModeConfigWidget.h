#ifndef LEDWALLSTUDIO_MODECONFIGWIDGET_H
#define LEDWALLSTUDIO_MODECONFIGWIDGET_H

#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE
class QComboBox;
class QPushButton;
QT_END_NAMESPACE

class WallController;
class ModeOptionsWidget;

class ModeConfigWidget : public QWidget
{
Q_OBJECT

public:
    explicit ModeConfigWidget(WallController *wallController, QWidget *parent = nullptr);

protected slots:
    void onModeChanged();
    void onSetModeClicked();
    void onSetOptionsClicked();

protected:
    WallController *m_wallController;

    void createUi();
    QComboBox *m_selectMode;

    QPushButton *m_btnSetOptions;
    ModeOptionsWidget *m_modeOptionsWidget = nullptr;
};

#endif //LEDWALLSTUDIO_MODECONFIGWIDGET_H
