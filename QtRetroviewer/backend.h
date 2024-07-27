#ifndef BACKEND_H
#define BACKEND_H

#include <opencv2/opencv.hpp>
#include <QString>

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
                                    int colorQuantity, int palette, int brightness,
                                    double contrast, double pixelizationFactor, double gamma);

    Q_INVOKABLE void saveImage(std::string savePath);

signals:
    void imageGenerated();
    void imageSaved();
};

#endif // BACKEND_H
