// SPDX-FileCopyrightText: 2020-2024 Xavier Leclercq
// SPDX-License-Identifier: MIT

#include "CommandLineSpecification.hpp"
#include <Ishiko/Configuration.hpp>
#include <Ishiko/HTTP.hpp>
#include <Ishiko/Networking.hpp>
#include <Ishiko/Terminal.hpp>
#include <Ishiko/Types.hpp>
#include <exception>
#include <sstream>

using namespace Nemu;

int main(int argc, char* argv[])
{
    try
    {
        CommandLineSpecification command_line_spec;
        Ishiko::Configuration configuration = command_line_spec.createDefaultConfiguration();
        Ishiko::CommandLineParser::parse(command_line_spec, argc, argv, configuration);

        const Ishiko::Configuration& command_configuration = configuration.value("command").asConfiguration();
        const std::string& command_name = command_configuration.value("name").asString();
        if (command_name == "get")
        {
            Ishiko::NetworkingLibraryInitialization network_library_initialization;

            Ishiko::Error error;

            // TODO
            // Nemu/0.1 Windows NT 10.0; +http://nemu.io/tool NemuTool/0.1.0

            Ishiko::URL url = command_configuration.value("url").asString();
            if (url.scheme() == "http")
            {
                Ishiko::NetworkConnectionsManager connection_manager;
                Ishiko::HostnameResolver hostname_resolver;

                Ishiko::HTTPClient http_client{connection_manager, hostname_resolver};

                // TODO: check the host, valid? IP or name?
                //Ishiko::IPv4Address address{"51.77.104.151", error};
                Ishiko::Hostname hostname{*url.host()};

                if (!error)
                {
                    Ishiko::HTTPResponse response{ Ishiko::HTTPStatusCode::internalServerError };
                    //http_client.get(address, 8003, "/", response, error);
                    http_client.get(hostname, Ishiko::Port::http, "/", response, error);

                    std::cout << response.toString() << std::endl;
                }
            }
            else if (url.scheme() == "https")
            {
                Ishiko::NetworkConnectionsManager connection_manager;
                Ishiko::HostnameResolver hostname_resolver;

                Ishiko::HTTPSClient https_client{connection_manager, hostname_resolver};

                // TODO: check the host, valid? IP or name?
                //Ishiko::IPv4Address address{"51.77.104.151", error};
                Ishiko::Hostname hostname{*url.host()};

                if (!error)
                {
                    Ishiko::HTTPResponse response{ Ishiko::HTTPStatusCode::internalServerError };
                    //http_client.get(address, 8003, "/", response, error);
                    https_client.get(hostname, Ishiko::Port::https, "/", response, error);

                    std::cout << response.toString() << std::endl;
                }
            }
        }

        // TODO: use proper error codes class
        return 0;
    }
    catch (const std::exception& e)
    {
        std::stringstream message;
        message << "EXCEPTION: " << e.what() << std::endl;
        Ishiko::TerminalOutput(stderr).write(message.str(), Ishiko::ColorName::red);

        // TODO
        return -1;
    }
    catch (...)
    {
        // TODO
        return -1;
    }
}
