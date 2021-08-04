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

#include "BeastServer.h"

using namespace boost::asio;

namespace Nemu
{

BeastServer::BeastServer(size_t numberOfThreads, const std::string& address, unsigned int port, Routes& routes,
    Views& views, std::shared_ptr<Observer> observer, Ishiko::Error& error)
    : Server(observer), m_routes(routes), m_views(views), m_ioContext((int)numberOfThreads),
    m_listener(*this, m_ioContext, ip::tcp::endpoint(ip::make_address(address), port), error)
{
    m_threads.resize(numberOfThreads);
}

void BeastServer::start()
{
    m_listener.run();

    // Run the I/O service on the requested number of threads
    for (std::thread& t : m_threads)
    {
        t = std::thread([this]{ m_ioContext.run(); });
    }

    observers().notify(&Observer::onServerStarted, *this);
}

void BeastServer::stop()
{
    m_ioContext.stop();
}

void BeastServer::join()
{
    for (std::thread& t : m_threads)
    {
        t.join();
    }

    observers().notify(&Observer::onServerStopped, *this);
}

bool BeastServer::isRunning() const
{
    return !m_ioContext.stopped();
}

const Routes& BeastServer::routes() const
{
    return m_routes;
}

const Views& BeastServer::views() const
{
    return m_views;
}

AccessLog& BeastServer::accessLog()
{
    return m_accessLog;
}

}
