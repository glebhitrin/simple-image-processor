#include "argumentparser.h"
#include "stdexcept"
#include "iostream"

void ArgumentParser::Parse() {
    if (argc_ < 3) {
        throw std::invalid_argument("Too few parameters were given.");
    }
    for (int i = 3; i < argc_; ++i) {
        if (argv_[i][0] == '-') {
            FilterParams filter;
            filter.name = ++argv_[i];
            commands_.push_back(filter);
        } else if (!commands_.empty()) {
            commands_.back().params.push_back(argv_[i]);
        } else {
            throw std::invalid_argument("Bad parameters were given.");
        }
    }
}
