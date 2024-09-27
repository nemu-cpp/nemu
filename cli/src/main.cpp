// SPDX-FileCopyrightText: 2020-2024 Xavier Leclercq
// SPDX-License-Identifier: MIT

#include <Ishiko/HTTP.hpp>
#include <Ishiko/Networking.hpp>

int main(int argc, char* argv[])
{
    Ishiko::Error error;

    Ishiko::NetworkingLibraryInitialization::Startup(error);

    Ishiko::NetworkConnectionsManager connection_manager;

    Ishiko::HTTPClient http_client{connection_manager};

    Ishiko::IPv4Address address{"51.77.104.151", error};
    
    if (!error)
    {
        Ishiko::HTTPResponse response{Ishiko::HTTPStatusCode::internalServerError};
        http_client.get(address, 8003, "/", response, error);

        std::cout << response.toString() << std::endl;
    }

    Ishiko::NetworkingLibraryInitialization::Cleanup(error);

    // TODO: use proper error codes class
    return 0;
}
