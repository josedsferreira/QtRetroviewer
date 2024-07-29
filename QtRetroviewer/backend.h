#ifndef BACKEND_H
#define BACKEND_H

#include <opencv2/opencv.hpp>
#include <QString>
#include <QColor>

#include <QObject>
//#include <QtQml>

class Backend : public QObject
{
    Q_OBJECT
    //QML_ELEMENT

public:
    explicit Backend(QObject* parent = nullptr);

    Q_INVOKABLE void testMessage(const QString& msg);

    Q_INVOKABLE void generateImage(const QString& imagePathQs, bool bayerFlag,
                                    int colorQuantity, int brightness,
                                    double contrast, double pixelizationFactor, double gamma,
                                    const QColor& color1, const QColor& color2, const QColor& color3,
                                    const QColor& color4, const QColor& color5, const QColor& color6,
                                    const QColor& color7, const QColor& color8);

    Q_INVOKABLE void saveImage(const QString& savePathQs);

signals:
    void imageGenerated();
    void imageSaved();
};

#endif // BACKEND_H
