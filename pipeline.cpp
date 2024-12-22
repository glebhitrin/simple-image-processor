#include "pipeline.h"
#include <iostream>

void Pipeline::Apply(Bitmap& image, const char* path_to_result) {
    for (const auto filter : pipeline_) {
        filter->Apply(image);
    }
    image.Save(path_to_result);
}