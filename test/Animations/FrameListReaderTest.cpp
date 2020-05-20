#include "FrameListReaderTest.h"

#include "../../src/Animations/FrameListReader.h"

void FrameListReaderTest::test_fromByteArray()
{
    {
        QByteArray data;
        FrameList frames = FrameListReader::fromByteArray(data);
        QCOMPARE(frames.length(), 0);
    }

    {
        QByteArray data;
        data.append((quint8) 0x1a).append((quint8) 0x00);
        FrameList frames = FrameListReader::fromByteArray(data);
        QCOMPARE(frames.length(), 0);
    }

    {
        QByteArray data;
        data.append((quint8) 0x1a); // protocol
        data.append((quint8) 0x00); // options

        data.append((quint8) 0x00); // delay
        data.append((quint8) 0x03); // pixel count
        data.append((quint8) 0x00).append((quint8) 0x00).append((quint8) 0xff).append((quint8) 0x00).append((quint8) 0x00); // x, y, r, g, b
        data.append((quint8) 0x01).append((quint8) 0x01).append((quint8) 0x00).append((quint8) 0xff).append((quint8) 0x00); // x, y, r, g, b
        data.append((quint8) 0x02).append((quint8) 0x02).append((quint8) 0x00).append((quint8) 0x00).append((quint8) 0xff); // x, y, r, g, b

        data.append((quint8) 0x0a); // delay
        data.append((quint8) 0x01); // pixel count
        data.append((quint8) 0x01).append((quint8) 0x01).append((quint8) 0x00).append((quint8) 0x00).append((quint8) 0x00); // x, y, r, g, b

        FrameList frames = FrameListReader::fromByteArray(data);
        QCOMPARE(frames.length(), 2);

        const Bitmap &bitmap0 = frames.at(0).bitmap;
        QCOMPARE(bitmap0.value({0, 0}), Qt::red);
        QCOMPARE(bitmap0.value({1, 1}), Qt::green);
        QCOMPARE(bitmap0.value({2, 2}), Qt::blue);

        const Bitmap &bitmap1 = frames.at(1).bitmap;
        QVERIFY(bitmap1.value({0, 0}).isValid());
        QCOMPARE(bitmap1.value({0, 0}), Qt::red);
        QCOMPARE(bitmap1.value({1, 1}), Qt::black);
        QVERIFY(bitmap1.value({2, 2}).isValid());
        QCOMPARE(bitmap1.value({2, 2}), Qt::blue);
    }

    {
        QByteArray data;
        data.append((quint8) 0x1a); // protocol
        data.append((quint8) 0x00); // options

        data.append((quint8) 0x00); // delay
        data.append((quint8) 0x03); // pixel count
        data.append((quint8) 0x00).append((quint8) 0x00).append((quint8) 0xff).append((quint8) 0x00).append((quint8) 0x00); // x, y, r, g, b
        data.append((quint8) 0x01).append((quint8) 0x01).append((quint8) 0x00).append((quint8) 0xff).append((quint8) 0x00); // x, y, r, g, b
        data.append((quint8) 0x02).append((quint8) 0x02).append((quint8) 0x00).append((quint8) 0x00).append((quint8) 0xff); // x, y, r, g, b

        data.append((quint8) 0x00); // no delay -> frames should be merged
        data.append((quint8) 0x01); // pixel count
        data.append((quint8) 0x02).append((quint8) 0x00).append((quint8) 0xff).append((quint8) 0xff).append((quint8) 0xff); // x, y, r, g, b

        FrameList frames = FrameListReader::fromByteArray(data);
        QCOMPARE(frames.length(), 1);

        QCOMPARE(frames.at(0).bitmap.value({0, 0}), Qt::red);
        QCOMPARE(frames.at(0).bitmap.value({1, 1}), Qt::green);
        QCOMPARE(frames.at(0).bitmap.value({2, 2}), Qt::blue);
        QCOMPARE(frames.at(0).bitmap.value({2, 0}), Qt::white);
    }
}

QTEST_MAIN(FrameListReaderTest)
