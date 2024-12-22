#pragma once
#include "matrix.h"

const uint8_t MIN = 0;

class Pixel {
public:
    uint8_t blue_ = MIN;
    uint8_t green_ = MIN;
    uint8_t red_ = MIN;
};

class Bitmap : public Matrix<Pixel> {
public:
    class BMPHeader {
    public:
        uint16_t header_field;
        uint32_t size_of_file;
        uint16_t reserved_1;
        uint16_t reserved_2;
        uint32_t offset;
    } __attribute__((packed));

    class BitmapInfoHeader {
    public:
        uint32_t size_of_bitmapinfoheader;
        uint32_t width;
        uint32_t height;
        uint16_t color_planes;
        uint16_t bits_per_pixel;
        uint32_t compression_method;
        uint32_t image_size;
        uint32_t horizontal_resolution;
        uint32_t vertical_resolution;
        uint32_t colors_in_palette;
        uint32_t important_colors;
    } __attribute__((packed));

public:
    void Open(const char* path_to_source);
    void Save(const char* path_to_result);

    void SetInfoHeaderHeightWidth(uint32_t height, uint32_t width) {
        bitmapInfoHeader_.height = height;
        bitmapInfoHeader_.width = width;
    }

protected:
    BMPHeader bmp_header_;
    BitmapInfoHeader bitmapInfoHeader_;
};