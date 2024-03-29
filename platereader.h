#ifndef PLATEREADER_PLATEREADER_H
#define PLATEREADER_PLATEREADER_H

#include <string>
#include "alpr.h"

class PlateReader {

private:
    alpr::Alpr alpr;
public:
    PlateReader();
public:
    std::string readPlateFromFile(const std::string &);

    std::string takePictureAndRead(const int &spaceID );
};

#endif //PLATEREADER_PLATEREADER_H
