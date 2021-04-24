#ifndef LEDWALLSTUDIO_FRAMELISTWRITEREADBACKTEST_H
#define LEDWALLSTUDIO_FRAMELISTWRITEREADBACKTEST_H

#include <QtTest/QtTest>

class FrameListWriteReadbackTest: public QObject
{
Q_OBJECT

private slots:
    void test_writeAndReadBack();
    void test_writeAndReadBackMultipleFullFrames();
    void test_writeAndReadBackMultipleNoChangeFrames();
};

#endif //LEDWALLSTUDIO_FRAMELISTWRITEREADBACKTEST_H
