#include "backend.h"
#include "rvfunctions.h"
#include <iostream>
#include <qdebug.h>
#include <string>
#include <filesystem>
#include <QCoreApplication>
#include <QDir>

namespace fs = std::filesystem;


Backend::Backend(QObject* parent) : QObject{ parent }
{

}

Q_INVOKABLE void Backend::testMessage(const QString& msg)
{
    //qDebug() << msg << std::endl;
    qDebug() << msg;
}

Q_INVOKABLE void Backend::generateImage(const QString& imagePathQs, bool bayerFlag, int colorQuantity, int brightness, double contrast, double pixelizationFactor, double gamma,
                                            const QColor& color1, const QColor& color2, const QColor& color3,
                                            const QColor& color4, const QColor& color5, const QColor& color6,
                                            const QColor& color7, const QColor& color8)
{
    std::string imagePath = imagePathQs.toStdString();
    // Find the position of C to remove extra bits
    size_t pos = imagePath.find_first_of("C");
    if (pos != std::string::npos) {
        // Extract the path
        imagePath = imagePath.substr(pos);
    }

    float gammaFloat = static_cast<float>(gamma);

    qDebug() << "Generate image function called";
    qDebug() << "imagePath: " << imagePath;
    qDebug() << "Bayer Flag: " << bayerFlag;
    qDebug() << "color quantity: " << colorQuantity;
    //qDebug() << "Palette choice: " << palette;
    qDebug() << "brightness: " << brightness;
    qDebug() << "contrast: " << contrast;
    qDebug() << "Pixelization: " << pixelizationFactor;
    qDebug() << "gamma (float): " << gammaFloat;

    // Image Loading
    cv::Mat image = cv::imread(imagePath, cv::IMREAD_GRAYSCALE);

    if (image.empty()) // check if image loaded correctly
    {
        qDebug() << "Error: Could not open or find the image!";
        return;
    }

    // Bayer Dithering
    if (bayerFlag) {
        image = bayerDither(image, 2);
    }

    /*
    if (colorQuantity != 0) {
        // Quantization
        image = quantize(image, colorQuantity);

        // Change Palette
        switch (colorQuantity)
        {
        case 4:
            image = set4ColorPalette(image, palette);
            break;
        case 8:
            image = set8ColorPalette(image, palette);
            break;
        case 2:
        default:
            image = set2ColorPalette(image, palette);
            break;
        }
    }
    */
    if (colorQuantity != 0) {
        // Quantization
        image = quantize(image, colorQuantity);
        image = editPalette(image, colorQuantity, color1, color2, color3, color4, color5, color6, color7, color8);
    }
    
    if (brightness != 0 || contrast != 1) {
        // Change Brightness and contrast
        image = changeContrastAndBrightness(image, contrast, brightness);    
    }

    if (gamma != 0.5) {
        // Correct Gamma
        image = changeGamma(image, gammaFloat);
    }

    if (pixelizationFactor < 1.0) {
        // Pixelate
        image = pixelate(image, pixelizationFactor);
    }

    // Save the image to a file
    QString picsDir = QCoreApplication::applicationDirPath() + "/pics";
    QDir().mkpath(picsDir); // Create the directory if it does not exist
    std::string outFile = (picsDir + "/result.png").toStdString();

    if (!cv::imwrite(outFile, image)) // check for success or fail
    {
        qDebug() << "Error: Could not save the image!";
        return;
    }
    else
    {
        qDebug() << "Image saved successfully to " << QString::fromStdString(outFile);
        emit imageGenerated();
    }

    
}

Q_INVOKABLE void Backend::saveImage(const QString& savePathQs)
{
    qDebug() << "Save image function called";
    std::string savePath = savePathQs.toStdString();
    // Find the position of C to remove extra bits
    size_t pos = savePath.find_first_of("C");
    if (pos != std::string::npos) {
        // Extract the path
        savePath = savePath.substr(pos);
        savePath = savePath + ".png";
    }
    qDebug() << "Path to save: " << savePath;

    fs::path source = "pics/result.png";
    fs::path destination = savePath;

    try {
        fs::copy(source, destination, fs::copy_options::overwrite_existing);
        qDebug() << "File copied successfully.";
        emit imageSaved();
    }
    catch (const fs::filesystem_error& e) {
        qDebug() << "Error copying file: " << e.what() << '\n';
    }

    emit imageSaved();
}
