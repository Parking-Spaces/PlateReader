#include <iostream>
#include <memory>
#include "platereader.h"

int main() {

    auto reader = std::make_shared<PlateReader>();

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
