#pragma once
#include "argumentparser.h"
#include "filters.h"
#include "map"

namespace Preparators {
Filter* crop(const FilterParams& params);
Filter* gs(const FilterParams& params);
Filter* neg(const FilterParams& params);
Filter* sharp(const FilterParams& params);
Filter* edge(const FilterParams& params);
Filter* gb(const FilterParams& params);
Filter* strange(const FilterParams& params);
};

using PointerToFilterPrep = Filter* (*)(const FilterParams&);
class FilterMaker {
public:
   FilterMaker()
    : filter_list_{{{"crop", &Preparators::crop},
                    {"gs", &Preparators::gs},
                    {"neg", &Preparators::neg},
                    {"sharp", &Preparators::sharp},
                    {"egde", &Preparators::edge},
                    {"blur", &Preparators::gb},
                    {"strange", &Preparators::strange}}} {
   } // TODO: в cpp

    PointerToFilterPrep GetPointerToFilterPrep(const char* name) const;
    Filter* MakeFilter(const FilterParams& params) const;

protected:
    std::map<std::string, PointerToFilterPrep> filter_list_;
};
