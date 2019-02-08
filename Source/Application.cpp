/*
    Copyright (c) 2019 Xavier Leclercq

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
*/

#include "Application.h"
#include "HTTPServer.h"

namespace Nemu
{

Application::Application(const Configuration& configuration)
{
    m_servers.emplace_back(std::make_shared<HTTPServer>(configuration.numberOfThreads()));
}

void Application::start()
{
    // First we start all the servers, note that the Server::start()
    // function does not block
    for (std::shared_ptr<Server>& server : m_servers)
    {
        server->start();
    }

    // By default we want the Application::start() function to block
    // so we call Server::join() on all the servers
    for (std::shared_ptr<Server>& server : m_servers)
    {
        server->join();
    }
}

}
