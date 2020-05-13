#include "ModesListModel.h"
#include "../HttpConnector/HttpConnector.h"

ModesListModel::ModesListModel(HttpConnector *httpConnector, QObject *parent):
    QAbstractListModel(parent), m_httpConnector(httpConnector)
{
    // TODO clear on loss of connection?
//    connect(m_httpConnector, &HttpConnector::connectionStatusChanged, this, &ModesListModel::setEnabled);
    connect(m_httpConnector, &HttpConnector::modesChanged, this, &ModesListModel::onModesChanged);
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
    return QModelIndex();
}

void ModesListModel::onModesChanged()
{
    beginResetModel();
    m_modes = m_httpConnector->getModes();
    endResetModel();
}
