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

#include "HTTPServer.h"

using namespace boost::asio;

namespace Nemu
{

HTTPServer::HTTPServer(size_t numberOfThreads, const std::string& address, unsigned int port,
    std::shared_ptr<Observer> observer, Ishiko::Error& error)
    : Server(observer), m_ioContext((int)numberOfThreads)
{
    ip::tcp::endpoint endpoint = ip::tcp::endpoint(ip::make_address(address), port);
    m_listener = std::make_shared<HTTPListener>(m_ioContext, endpoint, error);
    m_threads.resize(numberOfThreads);
}

void HTTPServer::start()
{
    m_listener->run();

    // Run the I/O service on the requested number of threads
    for (std::thread& t : m_threads)
    {
        t = std::thread([this]{ m_ioContext.run(); });
    }

    observers().notifyServerStarted(*this);
}

void HTTPServer::stop()
{
    m_ioContext.stop();
}

void HTTPServer::join()
{
    for (std::thread& t : m_threads)
    {
        t.join();
    }

    observers().notifyServerStopped(*this);
}

bool HTTPServer::isRunning() const
{
    return !m_ioContext.stopped();
}

}
