#ifndef LEDWALLSTUDIO_FRAMELISTREADERTEST_H
#define LEDWALLSTUDIO_FRAMELISTREADERTEST_H

#include <QtTest/QtTest>

class FrameListReaderTest: public QObject
{
Q_OBJECT

private slots:
    void test_fromByteArray();
    void test_oneFullTwoEmptyFrames();
};

#endif //LEDWALLSTUDIO_FRAMELISTREADERTEST_H
