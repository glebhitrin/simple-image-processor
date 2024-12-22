#include "filters.h"

void Crop::Apply(Bitmap &image) { // Здесь тестирующая система сказала мне прилепить амперсанд к image
    if (new_rows_ > image.GetRowsNum()) {
        new_rows_ = image.GetRowsNum();
    }
    if (new_cols_ > image.GetColsNum()) {
        new_cols_ = image.GetColsNum();
    }
    image.Resize(new_rows_, new_cols_);
    image.SetInfoHeaderHeightWidth(new_rows_, new_cols_);
}

void Gs::Apply(Bitmap &image) {
}

void Neg::Apply(Bitmap &image) {
}

void Sharp::Apply(Bitmap &image) {
}

void Edge::Apply(Bitmap &image) {
}

void Gb::Apply(Bitmap &image) {
}

void Strange::Apply(Bitmap &image) {
}