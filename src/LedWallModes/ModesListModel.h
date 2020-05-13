#ifndef LEDWALLSTUDIO_MODESLISTMODEL_H
#define LEDWALLSTUDIO_MODESLISTMODEL_H

#include <QtCore/QAbstractListModel>

class HttpConnector;

class ModesListModel : public QAbstractListModel
{
Q_OBJECT

public:
    explicit ModesListModel(HttpConnector *httpConnector, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;

protected slots:
    void onModesChanged();

protected:
    HttpConnector *m_httpConnector;
};

#endif //LEDWALLSTUDIO_MODESLISTMODEL_H
