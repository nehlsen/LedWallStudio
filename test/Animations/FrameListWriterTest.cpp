#include "FrameListWriterTest.h"
#include "../../src/Animations/Frame.h"
#include "../../src/Animations/FrameListWriter.h"

void FrameListWriterTest::test_toByteArray()
{
    {
        FrameList frames;
        QByteArray data = FrameListWriter::toByteArray(frames);
        QCOMPARE(data.size(), 2);
        QCOMPARE(data.at(0), 0x1a);
        QCOMPARE(data.at(1), 0x00);
    }

    {
        Bitmap b1;
        b1.insert({0, 0}, Qt::red);
        b1.insert({1, 0}, Qt::green);
        b1.insert({2, 0}, Qt::blue);

        Bitmap b2;
        b2.insert({0, 0}, Qt::black); // only this pixel has changed and will be included in the diff
        b2.insert({1, 0}, Qt::green);
        b2.insert({2, 0}, Qt::blue);

        FrameList frames;
        frames.append({"b1", 0, b1});
        frames.append({"b2", 1, b2});

        QByteArray data = FrameListWriter::toByteArray(frames);
        // 2 header + 2 header 1st frame + 3 pixel * 5 byte + 2 header 2nd frame + 1 pixel * 5 byte == 26
        QCOMPARE(data.size(), 26);
        QCOMPARE(data.at(0), 0x1a);
        QCOMPARE(data.at(1), 0x00);

        QCOMPARE(data.at(2), 0x00); // 1st frame delay
        QCOMPARE(data.at(3), 0x03); // 1st frame pixel count
        QCOMPARE(data.at(19), 0x01); // 2nd frame delay
        QCOMPARE(data.at(20), 0x01); // 2nd frame pixel count
    }
}

QTEST_MAIN(FrameListWriterTest)
