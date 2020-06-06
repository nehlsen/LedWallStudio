#ifndef LEDWALLSTUDIO_MODESLISTMODEL_H
#define LEDWALLSTUDIO_MODESLISTMODEL_H

#include <QtCore/QAbstractListModel>
#include "../WallController/Mode.h"

class WallController;

class ModesListModel : public QAbstractListModel
{
Q_OBJECT

public:
    explicit ModesListModel(WallController *wallController, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    QModelIndex modeIndexToModelIndex(int modeIndex) const;

protected slots:
    void onModesChanged();

protected:
    WallController *m_wallController;
    LedWallStudio::ModeList m_modes; // copy of the list from wall-Controller
};

#endif //LEDWALLSTUDIO_MODESLISTMODEL_H
