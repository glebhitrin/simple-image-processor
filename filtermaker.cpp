#include <iostream>
#include "filtermaker.h"

const int FIRST_PARAM = 0;
const int SECOND_PARAM = 1;
const int THIRD_PARAM = 2;

Filter* Preparators::crop(const FilterParams& params) {
    if (std::string_view(params.name) != "crop") {
        throw std::invalid_argument("Invalid argument.");
    }
    if (params.params.size() < 2) {
        throw std::invalid_argument("Too few parameters were given.");
    }
    return new Crop(std::stoi(params.params[FIRST_PARAM]), std::stoi(params.params[SECOND_PARAM]));
}

Filter* Preparators::gs(const FilterParams& params) {
    if (std::string_view(params.name) != "gs") {
        throw std::invalid_argument("Invalid argument.");
    }
    return new Gs();
}

Filter* Preparators::neg(const FilterParams& params) {
    if (std::string_view(params.name) != "neg") {
        throw std::invalid_argument("Invalid argument.");
    }
    return new Neg();
}

Filter* Preparators::sharp(const FilterParams& params) {
    if (std::string_view(params.name) != "sharp") {
        throw std::invalid_argument("Invalid argument.");
    }
    return new Sharp();
}

Filter* Preparators::edge(const FilterParams& params) {
    if (std::string_view(params.name) != "edge") {
        throw std::invalid_argument("Invalid argument.");
    }
    return new Edge();
}

Filter* Preparators::gb(const FilterParams& params) {
    if (std::string_view(params.name) != "gb") {
        throw std::invalid_argument("Invalid argument.");
    }
    return new Gb();
}

Filter* Preparators::strange(const FilterParams& params) {
    if (std::string_view(params.name) != "strange") {
        throw std::invalid_argument("Invalid argument.");
    }
    return new Strange();
}

Filter* FilterMaker::MakeFilter(const FilterParams& params) const {
    PointerToFilterPrep p = GetPointerToFilterPrep(params.name);
    Filter* filter = p(params);
    return filter;
}

PointerToFilterPrep FilterMaker::GetPointerToFilterPrep(const char* name) const {
    auto it_of_name = filter_list_.find(name);
    if (it_of_name != filter_list_.end()) {
        return it_of_name->second;
    }
    throw std::invalid_argument("Invalid argument.");
}
