/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/nemu-cpp/nemu/blob/main/LICENSE.txt
*/

#include <Nemu/WebFramework.hpp>
#include <iostream>

int main(int argc, char* argv[])
{
    // Create a log that sends its output to the console.
    Ishiko::StreamLoggingSink sink(std::cout);
    Ishiko::Logger log(sink);

    // TODO: use the async server
    std::shared_ptr<Nemu::SingleConnectionWebServer> server =
        std::make_shared<Nemu::SingleConnectionWebServer>(Ishiko::TCPServerSocket::AllInterfaces,
            Ishiko::Port::http, log);

    // TODO: use exceptions
    Nemu::WebApplication app(server, log);
    
    app.routes().add(
        Nemu::Route("/", 
            std::make_shared<Nemu::HardcodedWebRequestHandler>(Ishiko::HTTPStatusCode::ok, "Hello World!")));

    app.run();

    return 0;
}
