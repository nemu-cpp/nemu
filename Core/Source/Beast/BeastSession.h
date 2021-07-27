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

#ifndef _NEMUFRAMEWORK_NEMU_BEAST_BEASTSESSION_H_
#define _NEMUFRAMEWORK_NEMU_BEAST_BEASTSESSION_H_

#include "BeastRequest.h"
#include "BeastResponseBuilder.h"
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/strand.hpp>
#include <memory>

namespace Nemu
{

class BeastServer;

class BeastSession : public std::enable_shared_from_this<BeastSession>
{
public:
    BeastSession(BeastServer& server, boost::asio::ip::tcp::socket&& socket);
    void run();

private:
    void handleRequest(BeastRequest&& request);

    void read();
    void onRead(boost::system::error_code ec, size_t bytesTransferred);
    void onWrite(boost::system::error_code ec, size_t bytesTransferred, bool closed);
    void close();

private:
    BeastServer& m_server;
    boost::asio::ip::tcp::socket m_socket;
    //boost::asio::strand<boost::asio::io_context::executor_type> m_strand;
    boost::beast::flat_buffer m_buffer;
    BeastRequest m_request;
    BeastResponseBuilder m_response;
};

}

#endif
