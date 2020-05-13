#ifndef LEDWALLSTUDIO_MODESLISTMODEL_H
#define LEDWALLSTUDIO_MODESLISTMODEL_H

#include <QtCore/QAbstractListModel>
#include "../HttpConnector/Mode.h"

class HttpConnector;

class ModesListModel : public QAbstractListModel
{
Q_OBJECT

public:
    explicit ModesListModel(HttpConnector *httpConnector, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    QModelIndex modeIndexToModelIndex(int modeIndex) const;

protected slots:
    void onModesChanged();

protected:
    HttpConnector *m_httpConnector;
    LedWall::ModeList m_modes; // copy of the list from http connector
};

#endif //LEDWALLSTUDIO_MODESLISTMODEL_H
