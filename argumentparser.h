#pragma once

#include <cstddef>
#include <string>
#include <vector>

class FilterParams {
public:
    const char* name;
    std::vector<const char*> params;
};

class ArgumentParser {
public:
    ArgumentParser(int argc, char* argv[]) : argc_{argc}, argv_{argv} {
    }

    void Parse();

public:
    std::vector<FilterParams> GetParams() {
        return commands_;
    }

    char** GetArgv() {
        return argv_;
    }

protected:
    int argc_;
    char** argv_;
    std::vector<FilterParams> commands_;
};
