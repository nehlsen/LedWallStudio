#ifndef LEDWALLSTUDIO_MODECONFIGWIDGET_H
#define LEDWALLSTUDIO_MODECONFIGWIDGET_H

#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE
class QComboBox;
QT_END_NAMESPACE

class WallController;

class ModeConfigWidget : public QWidget
{
Q_OBJECT

public:
    explicit ModeConfigWidget(WallController *wallController, QWidget *parent = nullptr);

protected slots:
    void onModeChanged();
    void onSetModeClicked();

protected:
    WallController *m_wallController;

    void createUi();
    QComboBox *m_selectMode;
};

#endif //LEDWALLSTUDIO_MODECONFIGWIDGET_H
