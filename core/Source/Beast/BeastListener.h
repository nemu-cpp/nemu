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

#ifndef _NEMUFRAMEWORK_NEMU_BEAST_BEASTLISTENER_H_
#define _NEMUFRAMEWORK_NEMU_BEAST_BEASTLISTENER_H_

#include "Ishiko/Errors/Error.h"
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/io_context.hpp>

namespace Nemu
{

class BeastServer;

class BeastListener
{
public:
    BeastListener(BeastServer& server, boost::asio::io_context& ioContext, boost::asio::ip::tcp::endpoint endpoint,
        Ishiko::Error& error);

    void run();

private:
    void accept();
    void onAccept(boost::system::error_code ec);

private:
    BeastServer& m_server;
    boost::asio::ip::tcp::acceptor m_acceptor;
    boost::asio::ip::tcp::socket m_socket;
};

}

#endif
