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

    Nemu::IshikoServer server(Ishiko::TCPServerSocket::AllInterfaces, Ishiko::Port::http, error);

    // Create a log that sends its output to the console.
    Ishiko::StreamLoggingSink sink(std::cout);
    Nemu::Logger log(sink);

    Nemu::WebApplication app(log, error);
    if (error)
    {
        std::cout << "Error: " << error << std::endl;
    }
    
    app.routes().append(Nemu::Route("/",
        [](const Nemu::WebRequest& request, Nemu::WebResponseBuilder& response, void* handlerData,
            Nemu::Logger& logger)
        {
            response.body() = "Hello World!";
        }
    ));

    app.start();

    return error.condition().value();
}
