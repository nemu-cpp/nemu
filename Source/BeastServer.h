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

#ifndef _NEMUFRAMEWORK_NEMU_BEASTSERVER_H_
#define _NEMUFRAMEWORK_NEMU_BEASTSERVER_H_

#include "Server.h"
#include "Routes.h"
#include "BeastListener.h"
#include "Ishiko/Errors/Error.h"
#include <boost/asio/io_context.hpp>
#include <thread>
#include <memory>

namespace Nemu
{

class BeastServer : public Server
{
public:
    BeastServer(size_t numberOfThreads, const std::string& address, unsigned int port,
        Routes& routes, std::shared_ptr<Observer> observer, Ishiko::Error& error);

    void start() override;
    void stop() override;
    void join() override;

    bool isRunning() const override;

private:
    Routes& m_routes;
    boost::asio::io_context m_ioContext;
    std::shared_ptr<BeastListener> m_listener;
    std::vector<std::thread> m_threads;
};

}

#endif
