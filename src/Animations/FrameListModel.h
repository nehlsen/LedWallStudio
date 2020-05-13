#ifndef LEDWALLSTUDIO_FRAMELISTMODEL_H
#define LEDWALLSTUDIO_FRAMELISTMODEL_H

#include <QtCore/QAbstractListModel>
#include "../Bitmap.h"

class FrameListModel : public QAbstractListModel
{
Q_OBJECT

public:
    explicit FrameListModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    void addFrame();
//    bool insertRows(int row, int count, const QModelIndex &parent) override;
    bool removeRows(int row, int count, const QModelIndex &parent) override;

    Bitmap getBitmap(int row) const;
    void setBitmap(int row, const Bitmap &bitmap);

protected:
    struct Frame {
        QString name;
        Bitmap bitmap;
    };
    int m_nextFrameName = 0;
    QList<Frame> m_frames;
};

#endif //LEDWALLSTUDIO_FRAMELISTMODEL_H
