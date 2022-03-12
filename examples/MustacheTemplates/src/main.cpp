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

    // Create the configuration based on the command line arguments.
    Nemu::Configuration configuration(argc, argv);

    // Create a log that sends its output to the console.
    Ishiko::StreamLoggingSink sink(std::cout);
    Nemu::Logger log(sink);

    // Create the web application
    Nemu::WebApplication app(configuration, log, error);

    // Set the mustache engine as the default templating engine
    app.views() = Nemu::Views(std::make_shared<Nemu::MustacheTemplatingEngine>());

    // Add a single route that only handled the "/" path
    app.routes().append(Nemu::Route("/",
        [](const Nemu::WebRequest& request, Nemu::WebResponseBuilder& response, void* handlerData,
            Nemu::Logger& logger)
        {
            response.view("index");
        }
    ));

    app.start();

    if (error)
    {
        std::cout << "Error: " << error << std::endl;
    }

    return error.condition().value();
}
