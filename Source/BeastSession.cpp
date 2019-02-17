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

#include "BeastSession.h"
#include "BeastServer.h"
#include <boost/asio/bind_executor.hpp>

namespace Nemu
{

BeastSession::BeastSession(BeastServer& server, boost::asio::ip::tcp::socket&& socket)
    : m_server(server), m_socket(std::move(socket)), m_strand(m_socket.get_executor())
{
}

void BeastSession::run()
{
    read();
}

void BeastSession::handleRequest(boost::beast::http::request<boost::beast::http::string_body>&& request)
{
    m_server.accessLog().log(m_socket, request);

    m_response = {};
    m_response.keep_alive(request.keep_alive());
    m_response.body().append("Hello World!");
    m_response.prepare_payload();

    auto handler = boost::asio::bind_executor(m_strand,
        std::bind(&BeastSession::onWrite, shared_from_this(), std::placeholders::_1, std::placeholders::_2,
            m_response.need_eof()));
    boost::beast::http::async_write(m_socket, m_response, handler);
}

void BeastSession::read()
{
    m_request = {};

    auto handler = boost::asio::bind_executor(m_strand,
        std::bind(&BeastSession::onRead, shared_from_this(), std::placeholders::_1, std::placeholders::_2));
    boost::beast::http::async_read(m_socket, m_buffer, m_request, handler);
}

void BeastSession::onRead(boost::system::error_code ec, size_t bytesTransferred)
{
    if (!ec)
    {
        handleRequest(std::move(m_request));
    }
    else if (ec == boost::beast::http::error::end_of_stream)
    {
        return close();
    }
}

void BeastSession::onWrite(boost::system::error_code ec, size_t bytesTransferred, bool closed)
{
    if (closed)
    {
        close();
    }

    m_response = {};

    read();
}

void BeastSession::close()
{
    boost::system::error_code ec;
    m_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_send, ec);

    const std::string& sourceAddress = m_socket.remote_endpoint().address().to_string() + ":" +
        std::to_string(m_socket.remote_endpoint().port());
    m_server.observers().notify(&Server::Observer::onConnectionClosed, m_server, sourceAddress);
}

}