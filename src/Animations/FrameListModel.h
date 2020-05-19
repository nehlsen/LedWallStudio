#ifndef LEDWALLSTUDIO_FRAMELISTMODEL_H
#define LEDWALLSTUDIO_FRAMELISTMODEL_H

#include <QtCore/QAbstractListModel>
#include "../Bitmap.h"
#include "Frame.h"

class FrameListModel : public QAbstractListModel
{
Q_OBJECT

public:
    explicit FrameListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    int addFrame();
    FrameList getFrames() const;

//    bool insertRows(int row, int count, const QModelIndex &parent) override;
    bool removeRows(int row, int count, const QModelIndex &parent) override;

    Bitmap getBitmap(int row) const;
    void setBitmap(int row, const Bitmap &bitmap);

protected:
    int m_nextFrameName = 0;
    FrameList m_frames;
};

#endif //LEDWALLSTUDIO_FRAMELISTMODEL_H
