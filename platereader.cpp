#include "platereader.h"
#include "alpr.h"
#include <iostream>
#include <cstdlib>
#include <filesystem>

#define SCRIPT_NAME "./take_picture.sh "
#define DESTINATION_FOLDER "./pictures/"
#define DESTINATION_SUFFIX ".jpg"

PlateReader::PlateReader() : alpr("eu") {

    alpr.setTopN(1);

    if (!alpr.isLoaded()) {
        std::cerr << "Failed to load ALPR" << std::endl;

        exit(1);
    }

    alpr.setDefaultRegion("pt");
}

std::string PlateReader::readPlateFromFile(const std::string &plateFile) {

    alpr::AlprResults results = this->alpr.recognize(plateFile);

    float best = 0;

    int plateInd = -1;

    for (int i = 0; i < results.plates.size(); i++) {

        alpr::AlprPlateResult plate = results.plates[i];

        auto bestPlate = plate.bestPlate;

        if (best < bestPlate.overall_confidence) {
            best = bestPlate.overall_confidence;

            plateInd = i;
        }
    }

    if (plateInd < 0) {
        return "";
    }

    for (const auto &plate : results.plates[plateInd].topNPlates) {
        std::cout << "Possible: " << plate.characters << " " << plate.overall_confidence << std::endl;
    }

    return results.plates[plateInd].bestPlate.characters;
}

std::string PlateReader::takePictureAndRead(const int &spaceID) {

    std::string base_str(SCRIPT_NAME);

    std::string dest(DESTINATION_FOLDER);

    dest += std::to_string(spaceID);

    dest += DESTINATION_SUFFIX;

    base_str += dest;

    std::system(base_str.c_str());

    return readPlateFromFile(dest);
}