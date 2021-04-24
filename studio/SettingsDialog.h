#ifndef LEDWALLSTUDIO_SETTINGSDIALOG_H
#define LEDWALLSTUDIO_SETTINGSDIALOG_H

#include <QtWidgets/QDialog>

class QLineEdit;
class QCheckBox;
class QSpinBox;

namespace LedWall::Studio {

// configure local settings, like the host to connect to
class SettingsDialog : public QDialog
{
Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);

protected slots:
    void loadSettings();
    void saveSettings();

protected:
    void createUi();

    QLineEdit *m_editBitmapFolder;

    QLineEdit *m_editHost;
    QCheckBox *m_checkAutodetectSize;
    QSpinBox *m_editWidth;
    QSpinBox *m_editHeight;
};

}

#endif //LEDWALLSTUDIO_SETTINGSDIALOG_H
