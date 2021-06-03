#include <iostream>
#include <memory>
#include "platereader.h"
//#include "server_conn.h"

int main() {

    std::cout << "Hallo" << std::endl;

    auto reader = std::make_shared<PlateReader>();

    //auto conn = std::make_shared<ServerConnection>(reader, 1);

    std::cout << "Plate: " << reader->takePictureAndRead(1) << std::endl;

    //conn->connectToServer();

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
