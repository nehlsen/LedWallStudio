#ifndef LEDWALLSTUDIO_BITMAPTEST_H
#define LEDWALLSTUDIO_BITMAPTEST_H

#include <QtTest/QtTest>

class BitmapTest: public QObject
{
Q_OBJECT

private slots:
    void test_toPixelStream();
    void test_toPixelStreamChunked();
    void test_toPixelStream1a();
    void test_topRight();
    void test_diff();
};

#endif //LEDWALLSTUDIO_BITMAPTEST_H
