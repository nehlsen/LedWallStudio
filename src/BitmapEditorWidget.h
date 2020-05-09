#ifndef LEDWALLSTUDIO_BITMAPEDITORWIDGET_H
#define LEDWALLSTUDIO_BITMAPEDITORWIDGET_H

#include <QtWidgets/QWidget>
#include <QtWidgets/QGraphicsView>
#include "BitmapEditorCanvas.h"

/**
 * widget to edit one bitmap / not a stream of bitmaps / animations
 * display grid, provide color chooser, click to set color, etc
 *
 * NOT IN HERE
 *   animations
 *   convert from/to bmp file
 *   convert to proprietary quad-tree binary data
 *   stream via udp to wall...
 */
class BitmapEditorWidget : public QWidget
{
Q_OBJECT

public:
    explicit BitmapEditorWidget(QWidget *parent = nullptr);

protected slots:
    void onBitmapChanged();

protected:
    QGraphicsView *m_view;
    BitmapEditorCanvas *m_scene;
};

#endif //LEDWALLSTUDIO_BITMAPEDITORWIDGET_H
