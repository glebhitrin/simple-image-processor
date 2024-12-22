#pragma once
#include "argumentparser.h"

class Application {
public:
    const int FIRST_PARAM = 0;
    const int SECOND_PARAM = 1;
    const int THIRD_PARAM = 2;

    Application(int argc, char* argv[]) : parser_{ArgumentParser(argc, argv)} {
        parser_.Parse();
    }

public:
    void Run();

protected:
    ArgumentParser parser_;
};