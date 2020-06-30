#include "ModesListModel.h"
#include "../WallController/WallController.h"
#include <QtCore/QTimer>

ModesListModel::ModesListModel(WallController *wallController, QObject *parent):
    QAbstractListModel(parent), m_wallController(wallController)
{
    // TODO clear on loss of connection?
//    connect(m_httpConnector, &HttpConnector::connectionStatusChanged, this, &ModesListModel::setEnabled);
    connect(m_wallController, &WallController::modesChanged, this, &ModesListModel::onModesChanged);
    QTimer::singleShot(0, this, &ModesListModel::onModesChanged);
}

int ModesListModel::rowCount(const QModelIndex &parent) const
{
    return m_modes.count();
}

QVariant ModesListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (index.row() >= rowCount()) {
        return QVariant();
    }

    if (role == Qt::DisplayRole) {
        return m_modes.at(index.row()).Name;
    }
    if (role == Qt::UserRole) {
        return m_modes.at(index.row()).Index;
    }

    return QVariant();
}

QModelIndex ModesListModel::modeIndexToModelIndex(int modeIndex) const
{
    for (int idx = 0; idx < m_modes.count(); ++idx) {
        if (m_modes.at(idx).Index == modeIndex) {
            return createIndex(idx, 0);
        }
    }

    return {};
}

void ModesListModel::onModesChanged()
{
    beginResetModel();
    m_modes = m_wallController->getModes();
    endResetModel();
}
