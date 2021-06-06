#include <iostream>
#include <memory>
#include "platereader.h"
#include "server_conn.h"

#define SPACE_ID 1

int main() {

    std::cout << "Hallo" << std::endl;

    auto reader = std::make_shared<PlateReader>();

    auto conn = std::make_shared<ServerConnection>(reader, SPACE_ID);

//    std::cout << "Plate: " << reader->takePictureAndRead(SPACE_ID) << std::endl;

    while (true) {
        conn->connectToServer();
    }

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
