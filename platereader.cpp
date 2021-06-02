#include "platereader.h"
#include "alpr.h"
#include <iostream>

PlateReader::PlateReader() : alpr("eu") {

    alpr.setTopN(1);

    if (!alpr.isLoaded()) {
        std::cerr << "Failed to load ALPR" << std::endl;

        exit(1);
    }
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

    return results.plates[plateInd].bestPlate.characters;
}