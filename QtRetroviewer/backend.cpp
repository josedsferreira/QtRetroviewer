#include "backend.h"

Backend::Backend(QObject* parent)
    : QObject{ parent }
{}

void Backend::generateImage(std::string imagePath, bool bayerFlag, int colorQuantity, int palette, int brightness, double contrast, double pixelizationFactor, float gamma)
{


    emit imageGenerated();
}

void Backend::saveImage(std::string savePath)
{


    emit imageSaved();
}
