#include "SettingsDialog.h"
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QPushButton>
#include <QtCore/QSettings>
#include <QtWidgets/QFileDialog>

namespace LedWall::Studio {

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle(tr("Settings"));
    createUi();
    loadSettings();
}

void SettingsDialog::loadSettings()
{
    QSettings settings;
    settings.beginGroup("Settings");

    m_editBitmapFolder->setText(settings.value("bitmap_folder", QDir::homePath()).toString());
    m_editHost->setText(settings.value("host").toString());
    m_checkAutodetectSize->setChecked(settings.value("autodetect_size", true).toBool());
    m_editWidth->setValue(settings.value("width", 1).toInt());
    m_editHeight->setValue(settings.value("height", 1).toInt());
}

void SettingsDialog::saveSettings()
{
    QSettings settings;
    settings.beginGroup("Settings");

    settings.setValue("bitmap_folder", m_editBitmapFolder->text());
    settings.setValue("host", m_editHost->text());
    settings.setValue("autodetect_size", m_checkAutodetectSize->isChecked());
    settings.setValue("width", m_editWidth->value());
    settings.setValue("height", m_editHeight->value());
}

void SettingsDialog::createUi()
{
    m_editBitmapFolder = new QLineEdit(this);
    auto *btnChooseFolder = new QPushButton(tr("..."), this);
    connect(btnChooseFolder, &QPushButton::clicked, [this](){
        QString dir = QFileDialog::getExistingDirectory(
                this,
                tr("Select Bitmaps Folder"),
                "/home",
                QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

        if (!dir.isEmpty()) {
            m_editBitmapFolder->setText(dir);
        }
    });
    auto *chooseFolderLayout = new QHBoxLayout;
    chooseFolderLayout->addWidget(m_editBitmapFolder);
    chooseFolderLayout->addWidget(btnChooseFolder);

    m_editHost = new QLineEdit(this);

    m_checkAutodetectSize = new QCheckBox(this);
    m_checkAutodetectSize->setText(tr("&Autodetect Size"));

    m_editWidth = new QSpinBox(this);
    m_editWidth->setMinimum(1);
    m_editWidth->setMaximum(255);
    m_editHeight = new QSpinBox(this);
    m_editHeight->setMinimum(1);
    m_editHeight->setMaximum(255);

    connect(m_checkAutodetectSize, SIGNAL(toggled(bool)), m_editWidth, SLOT(setDisabled(bool)));
    connect(m_checkAutodetectSize, SIGNAL(toggled(bool)), m_editHeight, SLOT(setDisabled(bool)));

    auto *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel, this);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &SettingsDialog::saveSettings);

    auto *layout = new QFormLayout;
    layout->addRow(tr("Bitmaps Folder"), chooseFolderLayout);
    layout->addRow(tr("Host"), m_editHost);
    layout->addRow(m_checkAutodetectSize);
    layout->addRow(tr("Width"), m_editWidth);
    layout->addRow(tr("Height"), m_editHeight);
    layout->addRow(buttonBox);
    setLayout(layout);
}

}
