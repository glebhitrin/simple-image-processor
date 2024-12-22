#include "application.h"
#include "filtermaker.h"
#include "bitmap.h"
#include "pipeline.h"
#include <iostream>

Pipeline Make_Pipeline(const std::vector<FilterParams>& params) {
    Pipeline pipeline;
    FilterMaker maker;
    for (const auto& param : params) {
        Filter* x = maker.MakeFilter(param);
        pipeline.AddFilter(x);
    }

    return pipeline;
}

void Application::Run() {
    const char* path_to_source = parser_.GetArgv()[SECOND_PARAM];
    const char* path_to_result = parser_.GetArgv()[THIRD_PARAM];

    Bitmap image;
    image.Open(path_to_source);

    FilterMaker maker;

    Pipeline pipeline = Make_Pipeline(parser_.GetParams());
    pipeline.Apply(image, path_to_result);
}
