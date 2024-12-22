#include <iostream>
#include "application.h"
#include <stdexcept>

int main(int argc, char* argv[]) {
    try {
        Application app(argc, argv);
        app.Run();
    } catch (std::exception& e) {
        std::cerr << e.what();
    } catch (...) {
        std::cerr << "Error has occurred";
    }
}
