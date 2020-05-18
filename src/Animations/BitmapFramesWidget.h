#ifndef LEDWALLSTUDIO_BITMAPFRAMESWIDGET_H
#define LEDWALLSTUDIO_BITMAPFRAMESWIDGET_H

#include <QtWidgets/QWidget>
#include <QtCore/QItemSelection>

QT_BEGIN_NAMESPACE
class QListView;
class QPushButton;
QT_END_NAMESPACE

class BitmapEditor;
class FrameListModel;

class BitmapFramesWidget : public QWidget
{
Q_OBJECT

public:
    explicit BitmapFramesWidget(BitmapEditor *bitmapEditor, QWidget *parent = nullptr);

protected slots:
    void onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    void onBtnCopyClicked();
    void onBtnAddClicked();
    void onBtnRemoveClicked();

protected:
    BitmapEditor *m_bitmapEditor;

    void createUi();
    FrameListModel *m_frames;
    QListView *m_view;
    QPushButton *m_btnCopy;
    QPushButton *m_btnAdd;
    QPushButton *m_btnRemove;
};

#endif //LEDWALLSTUDIO_BITMAPFRAMESWIDGET_H
