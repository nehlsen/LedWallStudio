#include "Bitmap.h"

bool operator<(const QPoint &left, const QPoint &right)
{
    return left.x() < right.x() ? true : left.y() < right.y();
}