#ifndef LEDWALLSTUDIO_FRAMELISTWRITERTEST_H
#define LEDWALLSTUDIO_FRAMELISTWRITERTEST_H

#include <QtTest/QtTest>

class FrameListWriterTest: public QObject
{
Q_OBJECT

private slots:
    void test_toByteArray();
};

#endif //LEDWALLSTUDIO_FRAMELISTWRITERTEST_H
