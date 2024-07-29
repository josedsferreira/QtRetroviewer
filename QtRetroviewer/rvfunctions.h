#pragma once
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <opencv2/opencv.hpp>
#include <QColor>
#include "palette.h"


cv::Mat bayerDither(const cv::Mat& image, int matrixSize); // apply Bayer Dithering, returns new image with dithering

cv::Mat quantize(const cv::Mat& image, int colorQuantity); // apply quantization, returns new quantized image

cv::Mat pixelate(const cv::Mat& image, double factor); // downsample and upsample image to pixelate

cv::Mat set2ColorPalette(const cv::Mat& image, int choice); // set a palette with 2 colors

cv::Mat set4ColorPalette(const cv::Mat& image, int choice); // set a palette with 4 colors

cv::Mat set8ColorPalette(const cv::Mat& image, int choice); // set a palette with 8 colors

cv::Mat changeContrastAndBrightness(const cv::Mat& image, double alpha, int beta); // adjust contrast and/or brightness

cv::Mat changeGamma(const cv::Mat& image, const float gamma); // adjust gamma

cv::Mat editPalette(const cv::Mat& image, int colorQuantity, const QColor& color1, const QColor& color2, const QColor& color3,
                                            const QColor& color4, const QColor& color5, const QColor& color6,
                                            const QColor& color7, const QColor& color8); // set a personalized palette


#endif // FUNCTIONS_H
