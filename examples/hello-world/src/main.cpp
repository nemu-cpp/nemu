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

    // TODO: use the async server
    std::shared_ptr<Nemu::IshikoSingleConnectionServer> server =
        std::make_shared<Nemu::IshikoSingleConnectionServer>(Ishiko::TCPServerSocket::AllInterfaces,
            Ishiko::Port::http, error);

    // Create a log that sends its output to the console.
    Ishiko::StreamLoggingSink sink(std::cout);
    Ishiko::Logger log(sink);

    // TODO: use exceptions
    Nemu::WebApplication app(server, log, error);
    if (error)
    {
        std::cout << "Error: " << error << std::endl;
    }
    
    app.routes().append(
        Nemu::Route("/", 
            std::make_shared<Nemu::HardcodedWebRequestHandler>(Ishiko::HTTPStatusCode::ok, "Hello World!")));

    app.run();

    return error.condition().value();
}