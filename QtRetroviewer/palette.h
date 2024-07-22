#ifndef PALETTE_H
#define PALETTE_H

#include <opencv2/opencv.hpp>
#include <string>
#include <vector>


struct oneBitPalette {
    std::string name;
    cv::Vec3b color0;
    cv::Vec3b color1;

    oneBitPalette(const std::string& n, const cv::Vec3b& c0, const cv::Vec3b& c1)
        : name(n), color0(c0), color1(c1) {}
};


struct twoBitPalette {
    std::string name;
    cv::Vec3b color0;
    cv::Vec3b color1;
    cv::Vec3b color2;
    cv::Vec3b color3;

    twoBitPalette(const std::string& n, const cv::Vec3b& c0, const cv::Vec3b& c1, const cv::Vec3b& c2, const cv::Vec3b& c3)
        : name(n), color0(c0), color1(c1), color2(c2), color3(c3) {}
};

struct fourBitPalette {
    std::string name;
    cv::Vec3b color0;
    cv::Vec3b color1;
    cv::Vec3b color2;
    cv::Vec3b color3;
    cv::Vec3b color4;
    cv::Vec3b color5;
    cv::Vec3b color6;
    cv::Vec3b color7;

    fourBitPalette(const std::string& n, const cv::Vec3b& c0, const cv::Vec3b& c1, const cv::Vec3b& c2, const cv::Vec3b& c3, const cv::Vec3b& c4, const cv::Vec3b& c5, const cv::Vec3b& c6, const cv::Vec3b& c7)
        : name(n), color0(c0), color1(c1), color2(c2), color3(c3), color4(c4), color5(c5), color6(c6), color7(c7) {}
};

// Define palettes here
extern oneBitPalette onebp1;
extern oneBitPalette onebp2;
extern oneBitPalette onebp3;
extern oneBitPalette onebp4;
extern oneBitPalette onebp5;
extern oneBitPalette onebp6;
extern oneBitPalette onebp7;
extern oneBitPalette onebp8;
extern oneBitPalette onebp6;

extern twoBitPalette twobp1;
extern twoBitPalette twobp2;

extern fourBitPalette fourbp1;
extern fourBitPalette fourbp2;

// Functions to get all defined palettes
std::vector<oneBitPalette>& getAllOneBitPalettes();
std::vector<twoBitPalette>& getAllTwoBitPalettes();
std::vector<fourBitPalette>& getAllFourBitPalettes();

// Function to get specific palette
oneBitPalette& getOneBitPaletteByIndex(int index);
twoBitPalette& getTwoBitPaletteByIndex(int index);
fourBitPalette& getFourBitPaletteByIndex(int index);

// Function to get palette size
size_t getOneBitPaletteSize();
size_t getTwoBitPaletteSize();
size_t getFourBitPaletteSize();

#endif
