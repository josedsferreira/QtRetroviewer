#include "ImageProvider.h"

imageProvider::imageProvider() : QQuickImageProvider(QQuickImageProvider::Image) {}

QImage imageProvider::requestImage(const QString& id, QSize* size, const QSize& requestedSize) {
    QImage image("pics/result"); // Load the image dynamically here
    if (size) {
        *size = image.size();
    }
    return image;
}
