#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include <QQuickImageProvider>
#include <QImage>

class imageProvider : public QQuickImageProvider {
public:
    imageProvider();

    QImage requestImage(const QString& id, QSize* size, const QSize& requestedSize) override;
};

#endif // IMAGEPROVIDER_H
