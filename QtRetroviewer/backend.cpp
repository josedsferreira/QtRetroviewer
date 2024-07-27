#include "backend.h"
#include "rvfunctions.h"
#include <iostream>
#include <qdebug.h>
#include <string>

Backend::Backend(QObject* parent) : QObject{ parent }
{

}

Q_INVOKABLE void Backend::testMessage(const QString& msg)
{
    //qDebug() << msg << std::endl;
    qDebug() << msg;
}

Q_INVOKABLE void Backend::generateImage(const QString& imagePathQs, bool bayerFlag, int colorQuantity, int palette, int brightness, double contrast, double pixelizationFactor, double gamma)
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
    qDebug() << "Palette choice: " << palette;
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
    std::string outFile = "pics/result.png";
    if (!cv::imwrite(outFile, image)) // check for success or fail
    {
        qDebug() << "Error: Could not save the image!";
        return;
    }
    else
    {
        qDebug() << "Image saved successfully to " << outFile;
        emit imageGenerated();
    }

    
}

Q_INVOKABLE void Backend::saveImage(std::string savePath)
{
    qDebug() << "Save image function called";

    qDebug() << "Path to save: " << savePath;

    emit imageSaved();
}
