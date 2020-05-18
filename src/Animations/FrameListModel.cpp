#include "FrameListModel.h"

FrameListModel::FrameListModel(QObject *parent) : QAbstractListModel(parent)
{
}

int FrameListModel::rowCount(const QModelIndex &parent) const
{
    return m_frames.count();
}

QVariant FrameListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (index.row() >= rowCount()) {
        return QVariant();
    }

    if (role == Qt::DisplayRole) {
        return m_frames.at(index.row()).name;
    }
//    if (role == Qt::UserRole) {
//        return QVariant::fromValue(m_frames.at(index.row()).bitmap);
//    }

    return QVariant();
}

int FrameListModel::addFrame()
{
    const int row = m_frames.count();
    Frame frame = {
            QString("%1").arg(m_nextFrameName++, 2, 10, QLatin1Char('0')),
            Bitmap()
    };

    beginInsertRows(QModelIndex(), row, row);
    m_frames.insert(row, frame);
    endInsertRows();

    return row;
}

//bool FrameListModel::insertRows(int row, int count, const QModelIndex &parent)
//{
//    return QAbstractItemModel::insertRows(row, count, parent);
//}

bool FrameListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (parent.isValid())
        return false;

    if (row >= m_frames.size() || row + count <= 0)
        return false;

    int beginRow = qMax(0, row);
    int endRow = qMin(row + count - 1, m_frames.size() - 1);

    beginRemoveRows(parent, beginRow, endRow);

    while (beginRow <= endRow) {
        m_frames.removeAt(beginRow);
        ++beginRow;
    }

    endRemoveRows();
    return true;
}

Bitmap FrameListModel::getBitmap(int row) const
{
    if (row < 0 || row >= m_frames.size()) {
        return Bitmap();
    }

    return m_frames.at(row).bitmap;
}

void FrameListModel::setBitmap(int row, const Bitmap &bitmap)
{
    if (row < 0 || row >= m_frames.size()) {
        return;
    }

    m_frames[row].bitmap = bitmap;
    emit dataChanged(index(row), index(row));
}
