#include "RVfunctions.h"

cv::Mat bayerDither(const cv::Mat& image, int matrixSize = 2) {

    cv::Mat matrix;

    switch (matrixSize)
    {
    case 4:
        matrix = (cv::Mat_<int>(4, 4) << 0, 8, 2, 10,
            12, 4, 14, 6,
            3, 11, 1, 9,
            15, 7, 13, 5);
        break;
    case 8:
        matrix = (cv::Mat_<int>(8, 8) << 0, 32, 8, 40, 2, 34, 10, 42,
            48, 16, 56, 24, 50, 18, 58, 26,
            12, 44, 4, 36, 14, 46, 6, 38,
            60, 28, 52, 20, 62, 30, 54, 22,
            3, 35, 11, 43, 1, 33, 9, 41,
            51, 19, 59, 27, 49, 17, 57, 25,
            15, 47, 7, 39, 13, 45, 5, 37,
            63, 31, 55, 23, 61, 29, 53, 12);
        break;
    default:
    case 2:
        matrix = (cv::Mat_<int>(2, 2) << 0, 2,
            3, 1);
        break;
    }

    /*// Debugging
    std::cout << "Matrix selected size: " << matrixSize << std::endl;
    std::cout << "Matrix rows: " << matrix.rows << std::endl;
    std::cout << "Matrix cols: " << matrix.cols << std::endl;
    // Print the matrix
    std::cout << "Matrix:" << std::endl;
    for (int i = 0; i < matrix.rows; ++i) {
        for (int j = 0; j < matrix.cols; ++j) {
            std::cout << matrix.at<int>(i, j) << "\t";
        }
        std::cout << std::endl;
    }
    */

    cv::Mat ditheredImage = image.clone(); // Make a copy to store the dithered image

    for (int i = 0; i < image.rows; ++i) {
        for (int j = 0; j < image.cols; ++j) {
            int bayerValue = matrix.at<int>(i % matrix.rows, j % matrix.cols);
            ditheredImage.at<uchar>(i, j) += bayerValue * 255 / 16; // Add Bayer value to each pixel
        }
    }
    return ditheredImage;
}

cv::Mat quantize(const cv::Mat& image, int quantity = 4) {

    cv::Mat quantizedImage = image.clone(); // Make a copy to store the quantized image

    /*
    brightness increment level = 255 / (quantity - 1)
    quantizedValue = pixelValue / (255 / quantity) * (255 / (quantity - 1))

    example:
    for color quantity 4
    brightness increment level = 255 / (4 - 1) = 85, therefore brightness levels are quantized to 0, 85, 170, 255
    256 divided by 4 is 64 (i call this value divisionValue for lack of better name)
    quantizedValue = pixelValue / 64 * 85, the result will be 0, 85, 170 or 255
    */

    int incrementLevel = 255 / (quantity - 1);
    int divisionValue = 255 / quantity;
    int pixelValue = 0, quantizedValue = 0;


    for (int i = 0; i < image.rows; ++i) {
        for (int j = 0; j < image.cols; ++j) {

            pixelValue = image.at<uchar>(i, j);
            quantizedValue = pixelValue / divisionValue * incrementLevel;
            quantizedImage.at<uchar>(i, j) = quantizedValue;
        }
    }
    return quantizedImage;
}

cv::Mat pixelate(const cv::Mat& image, double factor = 1) {

    //std::cout << "Pixelization Factor: " << factor << std::endl;

    // Downsample the image
    cv::Size newSize(static_cast<int>(image.cols * factor), static_cast<int>(image.rows * factor)); // resolution for downsampling

    cv::Mat resizedImage;

    cv::resize(image, resizedImage, newSize, 0, 0, cv::INTER_AREA);

    // Upsample the image back to original size
    cv::Mat pixelatedImage;

    cv::resize(resizedImage, pixelatedImage, image.size(), 0, 0, cv::INTER_NEAREST);

    return pixelatedImage;
}

cv::Mat set2ColorPalette(const cv::Mat& image, int choice) {

    //std::cout << "Choice: " << choice << std::endl;
    if (choice >= getOneBitPaletteSize()) { choice = 0; }
    //std::cout << "Choice: " << choice << std::endl;
    //std::cout << "Palette size: " << getOneBitPaletteSize() << std::endl;

    oneBitPalette& palette = getOneBitPaletteByIndex(choice);

    // Create an output image of the same size but with 3 channels (color image)
    cv::Mat colorImage(image.size(), CV_8UC3);

    for (int i = 0; i < image.rows; ++i) {
        for (int j = 0; j < image.cols; ++j) {
            if (image.at<uchar>(i, j) == 0) {
                colorImage.at<cv::Vec3b>(i, j) = palette.color0;
                //std::cout << "changed black pixel " << static_cast<int>(image.at<uchar>(i, j)) << " to " << palette.color0 << std::endl;
            }
            else
            {
                colorImage.at<cv::Vec3b>(i, j) = palette.color1;
                //std::cout << "changed white pixel " << static_cast<int>(image.at<uchar>(i, j)) << " to " << palette.color1 << std::endl;
            }
        }
    }
    return colorImage;
}

cv::Mat set4ColorPalette(const cv::Mat& image, int choice) {

    if (choice >= getTwoBitPaletteSize()) { choice = 0; }

    twoBitPalette& palette = getTwoBitPaletteByIndex(choice);

    // Create an output image of the same size but with 3 channels (color image)
    cv::Mat colorImage(image.size(), CV_8UC3);

    for (int i = 0; i < image.rows; ++i) {
        for (int j = 0; j < image.cols; ++j) {

            switch (image.at<uchar>(i, j))
            {
            case 0:
                colorImage.at<cv::Vec3b>(i, j) = palette.color0;
                break;
            case 85:
                colorImage.at<cv::Vec3b>(i, j) = palette.color1;
                break;
            case 170:
                colorImage.at<cv::Vec3b>(i, j) = palette.color2;
                break;
            case 255:
            default:
                colorImage.at<cv::Vec3b>(i, j) = palette.color3;
                break;
            }
        }
    }
    return colorImage;
}

cv::Mat set8ColorPalette(const cv::Mat& image, int choice) {

    if (choice >= getFourBitPaletteSize()) { choice = 0; }

    fourBitPalette& palette = getFourBitPaletteByIndex(choice);

    // Create an output image of the same size but with 3 channels (color image)
    cv::Mat colorImage(image.size(), CV_8UC3);

    for (int i = 0; i < image.rows; ++i) {
        for (int j = 0; j < image.cols; ++j) {

            switch (image.at<uchar>(i, j))
            {
            case 0:
                colorImage.at<cv::Vec3b>(i, j) = palette.color0;
                break;
            case 36:
                colorImage.at<cv::Vec3b>(i, j) = palette.color1;
                break;
            case 72:
                colorImage.at<cv::Vec3b>(i, j) = palette.color2;
                break;
            case 108:
                colorImage.at<cv::Vec3b>(i, j) = palette.color3;
                break;
            case 144:
                colorImage.at<cv::Vec3b>(i, j) = palette.color4;
                break;
            case 180:
                colorImage.at<cv::Vec3b>(i, j) = palette.color5;
                break;
            case 216:
                colorImage.at<cv::Vec3b>(i, j) = palette.color6;
                break;
            case 252:
            case 288:
            default:
                colorImage.at<cv::Vec3b>(i, j) = palette.color7;
                break;
            }
        }
    }
    return colorImage;
}

cv::Mat changeContrastAndBrightness(const cv::Mat& image, double alpha = 1.0, int beta = 0) {

    /* Alpha: Simple contrast control */
    // alpha value [1.0-3.0]

    /* Beta: Simple brightness control */
    // beta value [0-100]

    if (alpha < 1.0) { alpha = 1.0; }
    else if (alpha > 3.0) { alpha = 3.0; }
    if (beta < 0) { beta = 0; }
    else if (beta > 100) { beta = 100; }

    // Check if the image is grayscale
    cv::Mat bgrImage;
    if (image.channels() == 1) {
        // Convert the grayscale image to a 3-channel BGR image
        cv::cvtColor(image, bgrImage, cv::COLOR_GRAY2BGR);
    }
    else {
        // If the image is already in color, just use the original image
        bgrImage = image; // Clone to avoid modifying the original image
    }

    cv::Mat new_image = cv::Mat::zeros(bgrImage.size(), bgrImage.type()); // new image with pixels set to zero

    for (int y = 0; y < bgrImage.rows; y++) {
        for (int x = 0; x < bgrImage.cols; x++) {
            for (int c = 0; c < bgrImage.channels(); c++) {
                new_image.at<cv::Vec3b>(y, x)[c] =
                    cv::saturate_cast<uchar>(alpha * bgrImage.at<cv::Vec3b>(y, x)[c] + beta);
            }
        }
    }

    return new_image;
}

cv::Mat changeGamma(const cv::Mat& image, float gamma) {

    if (gamma < 0.5) { gamma = 0.5; }
    if (gamma > 3.0) { gamma = 3.0; }

    cv::Mat alteredImage = image.clone();
    float invGamma = 1 / gamma;

    cv::Mat table(1, 256, CV_8U);
    uchar* p = table.ptr();
    for (int i = 0; i < 256; ++i) {
        p[i] = (uchar)(pow(i / 255.0, invGamma) * 255);
    }

    cv::LUT(image, table, alteredImage);
    return alteredImage;
}
