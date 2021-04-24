#include "FrameListWriteReadbackTest.h"
#include "../../studio/Animations/Frame.h"
#include "../../studio/Animations/FrameListWriter.h"
#include "../../studio/Animations/FrameListReader.h"

void FrameListWriteReadbackTest::test_writeAndReadBack()
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

    auto framesRead = FrameListReader::fromByteArray(data);
    if (frames != framesRead) {
        qDebug()
                << "\n\nframes\n"
                << frames
                << "\n\nframesRead\n"
                << framesRead
                << "\n\n";
    }
    QCOMPARE(framesRead, frames);
}

void FrameListWriteReadbackTest::test_writeAndReadBackMultipleFullFrames()
{
    const int frameCount = 5;
    const int frameSize = 25;

    FrameList frames;
    for (int frame = 0; frame < frameCount; ++frame) {
        Bitmap bitmap;
        for (int x = 0; x < frameSize; ++x) {
            for (int y = 0; y < frameSize; ++y) {
                bitmap.insert({x, y}, QColor(frame, frame, frame));
            }
        }

        frames.append({QString::number(frame), 38, bitmap});
    }

    QByteArray data = FrameListWriter::toByteArray(frames);
    auto framesRead = FrameListReader::fromByteArray(data);
    QCOMPARE(framesRead, frames);
}

void FrameListWriteReadbackTest::test_writeAndReadBackMultipleNoChangeFrames()
{
    const int frameCount = 5;
    const int frameSize = 25;
    const QColor frameColor(11, 22, 33);

    FrameList frames;
    for (int frame = 0; frame < frameCount; ++frame) {
        Bitmap bitmap;
        for (int x = 0; x < frameSize; ++x) {
            for (int y = 0; y < frameSize; ++y) {
                bitmap.insert({x, y}, frameColor);
            }
        }

        frames.append({QString::number(frame), 38, bitmap});
    }

    QByteArray data = FrameListWriter::toByteArray(frames);
    auto framesRead = FrameListReader::fromByteArray(data);
    QCOMPARE(framesRead, frames);
}


QTEST_MAIN(FrameListWriteReadbackTest)
