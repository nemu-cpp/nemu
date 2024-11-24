// SPDX-FileCopyrightText: 2020-2024 Xavier Leclercq
// SPDX-License-Identifier: MIT

#include <Ishiko/HTTP.hpp>
#include <Ishiko/Networking.hpp>

int main(int argc, char* argv[])
{
    // Nemu/0.1 Windows NT 10.0; +http://nemu.io/tool NemuTool/0.1.0

    /*
    // TODO: HTTP case: put back in
    Ishiko::Error error;

    Ishiko::NetworkingLibraryInitialization::Startup(error);

    Ishiko::NetworkConnectionsManager connection_manager;
    Ishiko::HostnameResolver hostname_resolver;

    Ishiko::HTTPClient http_client{connection_manager, hostname_resolver};

    //Ishiko::IPv4Address address{"51.77.104.151", error};
    Ishiko::Hostname hostname{"ishiko.org"};
    
    if (!error)
    {
        Ishiko::HTTPResponse response{Ishiko::HTTPStatusCode::internalServerError};
        //http_client.get(address, 8003, "/", response, error);
        http_client.get(hostname, Ishiko::Port::http, "/", response, error);

        std::cout << response.toString() << std::endl;
    }

    Ishiko::NetworkingLibraryInitialization::Cleanup(error);
    */

    Ishiko::Error error;

    Ishiko::NetworkingLibraryInitialization network_library_initialization;

    Ishiko::NetworkConnectionsManager connection_manager;
    Ishiko::HostnameResolver hostname_resolver;

    Ishiko::HTTPSClient https_client{connection_manager, hostname_resolver};

    //Ishiko::IPv4Address address{"51.77.104.151", error};
    Ishiko::Hostname hostname{"ishiko.org"};
    
    if (!error)
    {
        Ishiko::HTTPResponse response{Ishiko::HTTPStatusCode::internalServerError};
        //http_client.get(address, 8003, "/", response, error);
        https_client.get(hostname, Ishiko::Port::https, "/", response, error);

        std::cout << response.toString() << std::endl;
    }

    // TODO: use proper error codes class
    return 0;
}
