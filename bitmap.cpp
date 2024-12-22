#include "bitmap.h"
#include "iostream"

void StreamStatusChecker(std::ifstream& f) {
    if (f.fail()) {
        throw std::runtime_error("Could not read file.");
    }
}

void StreamStatusChecker(std::ofstream& f) {
    if (f.fail()) {
        throw std::runtime_error("Could not write to file.");
    }
}

void Bitmap::Open(const char* path_to_source) {
    std::ifstream f;
    f.open(path_to_source, std::ios::in);
    StreamStatusChecker(f);

    f.read(reinterpret_cast<char*>(&bmp_header_), sizeof(bmp_header_));
    StreamStatusChecker(f);
    f.read(reinterpret_cast<char*>(&bitmapInfoHeader_), sizeof(bitmapInfoHeader_));
    StreamStatusChecker(f);

    if (bitmapInfoHeader_.bits_per_pixel != 24 || bitmapInfoHeader_.color_planes != 1) {
        throw std::runtime_error("Wrong file format.");
    }

    rows_num_ = bitmapInfoHeader_.height;
    cols_num_ = bitmapInfoHeader_.width;
    table_ = AllocateMatrix(rows_num_, cols_num_);

    const uint32_t EXTRA = (4 - (bitmapInfoHeader_.width * 3) % 4) % 4;

    for (size_t i = 0; i < bitmapInfoHeader_.height; ++i) {
        for (size_t j = 0; j < bitmapInfoHeader_.width; ++j) {
            Pixel pixel;
            f.read(reinterpret_cast<char*>(&pixel), sizeof(pixel));
            StreamStatusChecker(f);
            this->operator()(i, j) = pixel;
        }
        f.seekg(EXTRA, std::ios_base::cur);
    }

    f.close();
}

void Bitmap::Save(const char* path_to_result) {
    std::ofstream f;
    f.open(path_to_result, std::ios::out);
    StreamStatusChecker(f);

    f.write(reinterpret_cast<char*>(&bmp_header_), sizeof(bmp_header_));
    StreamStatusChecker(f);
    f.write(reinterpret_cast<char*>(&bitmapInfoHeader_), sizeof(bitmapInfoHeader_));

    const uint32_t EXTRA = (4 - (bitmapInfoHeader_.width * 3) % 4) % 4;

    for (size_t i = 0; i < bitmapInfoHeader_.height; ++i) {
        for (size_t j = 0; j < bitmapInfoHeader_.width; ++j) {
            f.write(reinterpret_cast<char*>(&this->At(i, j)), sizeof(this->At(i, j)));
        }
        f.seekp(EXTRA, std::ios_base::cur);
    }

    f.close();
}
