#pragma once
#include <vector>
#include "filters.h"
#include "filtermaker.h"

class Pipeline {
public:
    void AddFilter(Filter* filter) {
        pipeline_.push_back(filter);
    };

    void Apply(Bitmap& image, const char* path_to_result);

public:
    std::vector<Filter*> pipeline_;
};