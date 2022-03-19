/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/nemu-cpp/nemu/blob/main/LICENSE.txt
*/

#include <Nemu.hpp>
#include <iostream>

int main(int argc, char* argv[])
{
    Ishiko::Error error;

    Nemu::IshikoServer server(Ishiko::Networking::TCPServerSocket::AllInterfaces, Ishiko::Networking::Port::http, error);

    // Create the configuration based on the command line arguments.
    Nemu::Configuration configuration(argc, argv, Ishiko::Networking::IPv4Address::Localhost(),
        8082);

    // Create a log that sends its output to the console.
    Ishiko::StreamLoggingSink sink(std::cout);
    Nemu::Logger log(sink);

    Nemu::WebApplication app(configuration, log, error);
    if (error)
    {
        std::cout << "Error: " << error << std::endl;
    }

    server.start();

    server.join();

    return error.condition().value();
}
