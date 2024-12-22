#pragma once
#include <string>
#include <vector>
#include "bitmap.h"

class Filter {
public:
    virtual void Apply(Bitmap& image) = 0;
    virtual ~Filter() = default;
};

class Crop : public Filter {
public:
    Crop(size_t new_rows, size_t new_cols): new_rows_{new_rows}, new_cols_{new_cols} {
    }

    void Apply(Bitmap& image) override;

protected:
    size_t new_rows_;
    size_t new_cols_;
};

class Gs : public Filter {
public:
    void Apply(Bitmap& image) override;
};

class Neg : public Filter {
public:
    void Apply(Bitmap& image) override;
};

class Sharp : public Filter {
public:
    void Apply(Bitmap& image) override;
};

class Edge : public Filter {
public:
    void Apply(Bitmap& image) override;
};

class Gb : public Filter {
public:
    void Apply(Bitmap& image) override;
};

class Strange : public Filter {
public:
    void Apply(Bitmap& image) override;
};