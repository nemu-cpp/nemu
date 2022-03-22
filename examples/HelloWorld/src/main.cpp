/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/nemu-cpp/nemu/blob/main/LICENSE.txt
*/

#include <Ishiko/HTTP.hpp>
#include <Nemu.hpp>
#include <iostream>
#include <memory>

int main(int argc, char* argv[])
{
    Ishiko::Error error;

    std::shared_ptr<Nemu::IshikoServer> server =
        std::make_shared<Nemu::IshikoServer>(Ishiko::TCPServerSocket::AllInterfaces, Ishiko::Port::http, error);

    // Create a log that sends its output to the console.
    Ishiko::StreamLoggingSink sink(std::cout);
    Nemu::Logger log(sink);

    Nemu::WebApplication app(server, log, error);
    if (error)
    {
        std::cout << "Error: " << error << std::endl;
    }
    
    app.routes().append(Nemu::Route("/",
        [](const Nemu::WebRequest& request, Nemu::WebResponseBuilder& response, void* handlerData,
            Nemu::Logger& logger)
        {
            // TODO: this doesn't work as the user would be left with specifying all the right headers. Do I assume some default?
            response.setStatus(Ishiko::HTTPStatusCode::ok);
            response.body() = "Hello World!";
        }
    ));

    app.start();

    return error.condition().value();
}
