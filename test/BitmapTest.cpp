#include "BitmapTest.h"
#include <Bitmap.h>

void BitmapTest::test_toPixelStream()
{
    Bitmap bitmap;
    QVERIFY(bitmap.toPixelStream().isEmpty());

    bitmap.insert({5, 5}, Qt::red);
    const QByteArray &pixelStream1 = bitmap.toPixelStream();
    QCOMPARE(pixelStream1.length(), 7);
    QCOMPARE(pixelStream1.at(0), 0x10); // protocol
    QCOMPARE(pixelStream1.at(1), 0x00); // protocol options
    QCOMPARE(pixelStream1.at(2), 5); // x
    QCOMPARE(pixelStream1.at(3), 5); // y
    QCOMPARE((quint8)pixelStream1.at(4), 0xff); // r
    QCOMPARE((quint8)pixelStream1.at(5), 0x00); // g
    QCOMPARE((quint8)pixelStream1.at(6), 0x00); // b

    bitmap.insert({3, 3}, Qt::green);
    bitmap.insert({7, 7}, Qt::blue);
    const QByteArray &pixelStream2 = bitmap.toPixelStream();
    QCOMPARE(pixelStream2.length(), 17);
    QCOMPARE(pixelStream2.at(0), 0x10); // protocol
    QCOMPARE(pixelStream2.at(1), 0x00); // protocol options
    QCOMPARE(pixelStream2.at(2), 3); // x
    QCOMPARE(pixelStream2.at(3), 3); // y
    QCOMPARE((quint8)pixelStream2.at(4), 0x00); // r
    QCOMPARE((quint8)pixelStream2.at(5), 0xff); // g
    QCOMPARE((quint8)pixelStream2.at(6), 0x00); // b
    QCOMPARE(pixelStream2.at(7), 5); // x
    QCOMPARE(pixelStream2.at(8), 5); // y
    QCOMPARE((quint8)pixelStream2.at(9), 0xff); // r
    QCOMPARE((quint8)pixelStream2.at(10), 0x00); // g
    QCOMPARE((quint8)pixelStream2.at(11), 0x00); // b
    QCOMPARE(pixelStream2.at(12), 7); // x
    QCOMPARE(pixelStream2.at(13), 7); // y
    QCOMPARE((quint8)pixelStream2.at(14), 0x00); // r
    QCOMPARE((quint8)pixelStream2.at(15), 0x00); // g
    QCOMPARE((quint8)pixelStream2.at(16), 0xff); // b
}

void BitmapTest::test_toPixelStreamChunked()
{
    Bitmap bitmap;
    bitmap.insert({5, 5}, Qt::red);
    bitmap.insert({3, 3}, Qt::green);
    bitmap.insert({7, 7}, Qt::blue);

    QVERIFY(bitmap.toPixelStreamChunked(6).isEmpty());

    const QByteArrayList &chunks7bytesPerChunk = bitmap.toPixelStreamChunked(7);
    QCOMPARE(chunks7bytesPerChunk.count(), 3);
    QCOMPARE(chunks7bytesPerChunk.at(0).length(), 7);
    QCOMPARE(chunks7bytesPerChunk.at(1).length(), 7);
    QCOMPARE(chunks7bytesPerChunk.at(2).length(), 7);
}

void BitmapTest::test_toPixelStream1a()
{
    // empty bitmap to stream has only header
    {
        Bitmap bitmap;
        const QByteArray &pixelStream = bitmap.toPixelStream1a(9);
        QCOMPARE(pixelStream.count(), 2);
        QCOMPARE(pixelStream.at(0), 0x09); // delay
        QCOMPARE(pixelStream.at(1), 0x00); // number of pixels
    }

    // one pixel
    {
        Bitmap bitmap;
        bitmap.insert({5, 5}, Qt::green);
        const QByteArray &pixelStream = bitmap.toPixelStream1a(255);
        QCOMPARE(pixelStream.count(), 7);
        QCOMPARE((quint8)pixelStream.at(0), 0xff); // delay
        QCOMPARE(pixelStream.at(1), 0x01); // number of pixels
        QCOMPARE(pixelStream.at(2), 5); // x
        QCOMPARE(pixelStream.at(3), 5); // y
        QCOMPARE((quint8) pixelStream.at(4), 0x00); // r
        QCOMPARE((quint8) pixelStream.at(5), 0xff); // g
        QCOMPARE((quint8) pixelStream.at(6), 0x00); // b
    }

    // more than 255 pixels
    {
        Bitmap bitmap;
        for (int x = 0; x < 20; ++x) {
            for (int y = 0; y < 20; ++y) {
                bitmap.insert({x, y}, Qt::white);
            }
        }
        const QByteArray &pixelStream = bitmap.toPixelStream1a(15);
        // 400 pixels x 5byte + 2 chunks x 2byte chunk header
        QCOMPARE(pixelStream.count(), (400*5 + 2*2));
        QCOMPARE(pixelStream.at(0), 0x0f); // 1st chunk delay
        QCOMPARE((quint8)pixelStream.at(1), 0xff); // 1st chunk number of pixels

        QCOMPARE((quint8)pixelStream.at(2 + 255 * 5 - 3), 0xff); // 1st chunk, last pixel is white - r
        QCOMPARE((quint8)pixelStream.at(2 + 255 * 5 - 2), 0xff); // 1st chunk, last pixel is white - g
        QCOMPARE((quint8)pixelStream.at(2 + 255 * 5 - 1), 0xff); // 1st chunk, last pixel is white - b

        QCOMPARE(pixelStream.at(2 + 255 * 5 + 0), 0x00); // 2nd chunk delay
        QCOMPARE((quint8)pixelStream.at(2 + 255 * 5 + 1), (400-255)); // 2nd chunk number of pixels
    }
}

void BitmapTest::test_topRight()
{
    Bitmap bitmap;
    QCOMPARE(bitmap.count(), 0);
    QCOMPARE(bitmap.topRight(), QPoint(0, 0));

    bitmap.insert({5, 5}, Qt::red);
    QCOMPARE(bitmap.count(), 1);
    QCOMPARE(bitmap.topRight(), QPoint(5, 5));

    bitmap.insert({9, 5}, Qt::blue);
    QCOMPARE(bitmap.count(), 2);
    QCOMPARE(bitmap.topRight(), QPoint(9, 5));

    bitmap.insert({5, 9}, Qt::green);
    QCOMPARE(bitmap.count(), 3);
    QCOMPARE(bitmap.topRight(), QPoint(9, 9));

    bitmap.insert({11, 11}, Qt::yellow);
    QCOMPARE(bitmap.count(), 4);
    QCOMPARE(bitmap.topRight(), QPoint(11, 11));
}

void BitmapTest::test_diff()
{
    // one pixel, both same color
    {
        Bitmap bitmap1a;
        bitmap1a.insert({1, 1}, Qt::red);
        Bitmap bitmap1b;
        bitmap1b.insert({1, 1}, Qt::red);
        Bitmap diff1(bitmap1a.diff(bitmap1b));
        QVERIFY(diff1.isEmpty());
    }

    // one pixel, both set different colors
    {
        Bitmap bitmap2a;
        bitmap2a.insert({1, 1}, Qt::red);
        Bitmap bitmap2b;
        bitmap2b.insert({1, 1}, Qt::green);
        Bitmap diff2(bitmap2a.diff(bitmap2b));
        QCOMPARE(diff2.count(), 1);
        QCOMPARE(diff2.value({1, 1}), Qt::green);
    }

    // one pixel, first unset, second set to color
    {
        Bitmap bitmap3a;
        Bitmap bitmap3b;
        bitmap3b.insert({1, 1}, Qt::green);
        Bitmap diff3(bitmap3a.diff(bitmap3b));
        QCOMPARE(diff3.count(), 1);
        QCOMPARE(diff3.value({1, 1}), Qt::green);
    }

    // one pixel, first set to color, second unset
    {
        Bitmap bitmap4a;
        bitmap4a.insert({1, 1}, Qt::green);
        Bitmap bitmap4b;
        Bitmap diff4(bitmap4a.diff(bitmap4b));
        QCOMPARE(diff4.count(), 1);
        QCOMPARE(diff4.value({1, 1}), Qt::black);
    }

    {
        // 3x3, change one
        Bitmap bitmap5a;
        Bitmap bitmap5b;
        for (int x = 0; x < 3; ++x) {
            for (int y = 0; y < 3; ++y) {
                bitmap5a.insert({x, y}, Qt::black);
                bitmap5b.insert({x, y}, Qt::black);
            }
        }

        bitmap5a[{0, 0}] = Qt::red; // will be changed
        bitmap5b[{0, 0}] = Qt::green;

        bitmap5a[{0, 1}] = Qt::red; // will be kept
        bitmap5b[{0, 1}] = Qt::red; // will be kept

        Bitmap diff5(bitmap5a.diff(bitmap5b));
        QCOMPARE(diff5.count(), 1);
        QCOMPARE(diff5.value({0, 0}), Qt::green);
    }

    {
        // 3x3, add one
        Bitmap bitmap5a;
        Bitmap bitmap5b;
        for (int x = 0; x < 3; ++x) {
            for (int y = 0; y < 3; ++y) {
                bitmap5a.insert({x, y}, Qt::black);
                bitmap5b.insert({x, y}, Qt::black);
            }
        }

        bitmap5a[{0, 0}] = Qt::red; // will be kept
        bitmap5b[{0, 0}] = Qt::red; // will be kept

        bitmap5a[{0, 1}] = Qt::red; // will be kept
        bitmap5b[{0, 1}] = Qt::red; // will be kept

        bitmap5b[{1, 1}] = Qt::green; // added

        Bitmap diff5(bitmap5a.diff(bitmap5b));
        QCOMPARE(diff5.count(), 1);
        QCOMPARE(diff5.value({1, 1}), Qt::green);
    }

    {
        // 3x3, remove one
        Bitmap bitmap5a;
        Bitmap bitmap5b;
        for (int x = 0; x < 3; ++x) {
            for (int y = 0; y < 3; ++y) {
                bitmap5a.insert({x, y}, Qt::black);
                bitmap5b.insert({x, y}, Qt::black);
            }
        }

        bitmap5a[{0, 0}] = Qt::red; // will be removed
        bitmap5b.remove({0, 0});

        bitmap5a[{0, 1}] = Qt::red; // will be kept
        bitmap5b[{0, 1}] = Qt::red; // will be kept

        Bitmap diff5(bitmap5a.diff(bitmap5b));
        QCOMPARE(diff5.count(), 1);
        QCOMPARE(diff5.value({0, 0}), Qt::black);
    }

    {
        // all different
        for (const int bitmapSize : {2, 4, 5}) {
            Bitmap bitmap6a;
            Bitmap bitmap6b;
            for (int x = 0; x < bitmapSize; ++x) {
                for (int y = 0; y < bitmapSize; ++y) {
                    bitmap6a.insert({x, y}, QColor(1, 1, 1));
                    bitmap6b.insert({x, y}, QColor(2, 2, 2));
                }
            }

            Bitmap diff6(bitmap6a.diff(bitmap6b));
            QCOMPARE(diff6.count(), bitmapSize*bitmapSize);
        }
    }
}

QTEST_MAIN(BitmapTest)
