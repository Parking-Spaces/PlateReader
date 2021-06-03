#ifndef PLATEREADER_SERVER_CONN_H
#define PLATEREADER_SERVER_CONN_H

#include <memory>
#include "platereader.h"
#include "parkingspaces.grpc.pb.h"

#define SERVER_IP "localhost:50051"

class ServerConnection {

private:
    std::shared_ptr<PlateReader> reader;

    std::unique_ptr<parkingspaces::ParkingNotifications::Stub> connStub;

    std::shared_ptr<grpc::Channel> channel;

    int spaceID;

public:
    ServerConnection(std::shared_ptr<PlateReader> plateReader, int spaceID);

    void connectToServer();

private:
    void registerReader();
};


#endif //PLATEREADER_SERVER_CONN_H
