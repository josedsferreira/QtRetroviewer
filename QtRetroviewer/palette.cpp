#include "palette.h"

// TO ADD MORE PALETTES
/*
    Add the below but also to the vector at the bottom and to the header file
*/

// one-bit palette
// 1 Bit Monitor Glow by Polyducks https://lospec.com/palette-list/1bit-monitor-glow
oneBitPalette onebp1("1Bit Monitor Glow",
    cv::Vec3b(0x22, 0x23, 0x23),
    cv::Vec3b(0xF0, 0xF6, 0xF0));
// Casio Basic by graph100 https://lospec.com/palette-list/casio-basic
oneBitPalette onebp2("Casio Basic",
    cv::Vec3b(0x00, 0x00, 0x00),
    cv::Vec3b(0x83, 0xB0, 0x7E));
// Paperback-2 by Doph https://lospec.com/palette-list/paperback-2
oneBitPalette onebp3("Paperback-2",
    cv::Vec3b(0x38, 0x2B, 0x26),
    cv::Vec3b(0xB8, 0xC2, 0xB9));
// 1 Bit Apple Green by gabs https://lospec.com/palette-list/1-bit-apple-green
oneBitPalette onebp4("1 Bit Apple Green",
    cv::Vec3b(0x00, 0x00, 0x00),
    cv::Vec3b(0x26, 0xC3, 0x0F));
// Obra Dinn - IBM 5151 by PureAsbestos https://lospec.com/palette-list/obra-dinn-ibm-5151
oneBitPalette onebp5("Obra Dinn - IBM 5151",
    cv::Vec3b(0x25, 0x34, 0x2F),
    cv::Vec3b(0x01, 0xEB, 0x5F));
// Gato Roboto - Grape by PureAsbestos https://lospec.com/palette-list/gato-roboto-grape
oneBitPalette onebp6("Gato Roboto - Grape",
    cv::Vec3b(0x04, 0x06, 0x12),
    cv::Vec3b(0xD4, 0x00, 0xFF));
// Bluerown 1Bit by P0kePanda https://lospec.com/palette-list/bluerown-1bit
oneBitPalette onebp7("Bluerown 1Bit",
    cv::Vec3b(0xAF, 0x55, 0x34),
    cv::Vec3b(0xB4, 0xE7, 0xEF));
// 1Bit Night by Joker/Adem https://lospec.com/palette-list/1-bit-night
oneBitPalette onebp8("1Bit Night",
    cv::Vec3b(0x1F, 0x20, 0x21),
    cv::Vec3b(0x74, 0x95, 0xFF));
// Cloods by technicolor https://lospec.com/palette-list/cloods
oneBitPalette onebp9("Cloods",
    cv::Vec3b(0x11, 0x22, 0x33),
    cv::Vec3b(0xFF, 0xFF, 0x11));


// two-bit palette
// Lava-GB created by Aero https://lospec.com/palette-list/lava-gb
twoBitPalette twobp1("Lava-GB",
    cv::Vec3b(0x05, 0x1F, 0x39),
    cv::Vec3b(0x4A, 0x24, 0x80),
    cv::Vec3b(0xC5, 0x3A, 0x9D),
    cv::Vec3b(0xFF, 0x8E, 0x80));
// Moonlight created by Tofu https://lospec.com/palette-list/moonlight-gb
twoBitPalette twobp2("Moonlight",
    cv::Vec3b(0x0F, 0x05, 0x2D),
    cv::Vec3b(0x20, 0x36, 0x71),
    cv::Vec3b(0x36, 0x85, 0x8F),
    cv::Vec3b(0x5F, 0xC7, 0x5D));

// four-bit (8 colors max actually) palette
// Retrocal-8 by polyphrog https://lospec.com/palette-list/retrocal-8
fourBitPalette fourbp1("Retrocal-8",
    cv::Vec3b(0x2F, 0x14, 0x2F),
    cv::Vec3b(0x2A, 0x58, 0x4F),
    cv::Vec3b(0x74, 0xA3, 0x3F),
    cv::Vec3b(0xC6, 0x50, 0x5A),
    cv::Vec3b(0x77, 0x44, 0x48),
    cv::Vec3b(0xEE, 0x9C, 0x5D),
    cv::Vec3b(0x6E, 0xB8, 0xA8),
    cv::Vec3b(0xFC, 0xFF, 0xC0)
);
// Dawnbringer's 8 Color by dawnbringer https://lospec.com/palette-list/dawnbringers-8-color
fourBitPalette fourbp2("Dawnbringer",
    cv::Vec3b(0x00, 0x00, 0x00),
    cv::Vec3b(0x55, 0x41, 0x5F),
    cv::Vec3b(0x64, 0x69, 0x64),
    cv::Vec3b(0xD7, 0x73, 0x55),
    cv::Vec3b(0x50, 0x8C, 0xD7),
    cv::Vec3b(0x64, 0xB9, 0x64),
    cv::Vec3b(0xE6, 0xC8, 0x6E),
    cv::Vec3b(0xDC, 0xF5, 0xFF));

// Functions to get all defined palettes
std::vector<oneBitPalette>& getAllOneBitPalettes() {
    static std::vector<oneBitPalette> allOneBitPalettes = {
        onebp1,
        onebp2,
        onebp3,
        onebp4,
        onebp5,
        onebp6,
        onebp7,
        onebp8,
        onebp9
    };
    return allOneBitPalettes;
}

std::vector<twoBitPalette>& getAllTwoBitPalettes() {
    static std::vector<twoBitPalette> allTwoBitPalettes = {
        twobp1,
        twobp2
    };
    return allTwoBitPalettes;
}

std::vector<fourBitPalette>& getAllFourBitPalettes() {
    static std::vector<fourBitPalette> allFourBitPalettes = {
        fourbp1,
        fourbp2
    };
    return allFourBitPalettes;
}

// Function to get a specific palette
oneBitPalette& getOneBitPaletteByIndex(int index) {
    std::vector<oneBitPalette>& palettes = getAllOneBitPalettes();
    if (index >= 0 && index < palettes.size()) {
        return palettes[index];
    }
    else {
        throw std::out_of_range("Index out of bounds");
    }
}

twoBitPalette& getTwoBitPaletteByIndex(int index) {
    std::vector<twoBitPalette>& palettes = getAllTwoBitPalettes();
    if (index >= 0 && index < palettes.size()) {
        return palettes[index];
    }
    else {
        throw std::out_of_range("Index out of bounds");
    }
}

fourBitPalette& getFourBitPaletteByIndex(int index) {
    std::vector<fourBitPalette>& palettes = getAllFourBitPalettes();
    if (index >= 0 && index < palettes.size()) {
        return palettes[index];
    }
    else {
        throw std::out_of_range("Index out of bounds");
    }
}

// Function to get palette size
size_t getOneBitPaletteSize() {
    std::vector<oneBitPalette>& palettes = getAllOneBitPalettes();
    return palettes.size();
}
size_t getTwoBitPaletteSize() {
    std::vector<twoBitPalette>& palettes = getAllTwoBitPalettes();
    return palettes.size();
}
size_t getFourBitPaletteSize() {
    std::vector<fourBitPalette>& palettes = getAllFourBitPalettes();
    return palettes.size();
}
