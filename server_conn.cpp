
#include "server_conn.h"
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>
#include "parkingspaces.grpc.pb.h"

ServerConnection::ServerConnection(std::shared_ptr<PlateReader> plateReader, int spaceID) :
        reader(std::move(plateReader)),
        spaceID(spaceID) {
}

void ServerConnection::connectToServer() {

    this->channel = grpc::CreateChannel(SERVER_IP,
                                        grpc::InsecureChannelCredentials());

    this->connStub = parkingspaces::ParkingNotifications::NewStub(this->channel);

    registerReader();
}

void ServerConnection::registerReader() {

    grpc::ClientContext context;

    auto readerWriter = this->connStub->registerPlateReader(&context);

    parkingspaces::PlateReaderResult result;

    result.set_spaceid(spaceID);

    result.set_registration(true);

    readerWriter->Write(result);

    parkingspaces::PlateReadRequest req;

    while (readerWriter->Read(&req)) {

        std::cout << "Received request for plate reader " << req.spaceid() << std::endl;

        std::string plate = this->reader->takePictureAndRead(req.spaceid());

        result.set_spaceid(req.spaceid());

        result.set_registration(false);

        result.set_plate(plate);

        readerWriter->Write(result);
    }

    readerWriter->Finish();
}