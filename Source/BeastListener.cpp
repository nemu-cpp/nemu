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

#include "BeastListener.h"
#include "BeastServer.h"
#include "BeastSession.h"

namespace Nemu
{

BeastListener::BeastListener(BeastServer& server, boost::asio::io_context& ioContext,
    boost::asio::ip::tcp::endpoint endpoint, Ishiko::Error& error)
    : m_server(server), m_acceptor(ioContext), m_socket(ioContext)
{
    boost::system::error_code ec;
    m_acceptor.open(endpoint.protocol(), ec);
    if (ec)
    {
        error.fail(ec.value(), ec.message(), __FILE__, __LINE__);
        return;
    }
    m_acceptor.set_option(boost::asio::socket_base::reuse_address(true), ec);
    if (ec)
    {
        m_acceptor.close();
        error.fail(ec.value(), ec.message(), __FILE__, __LINE__);
        return;
    }
    m_acceptor.bind(endpoint, ec);
    if (ec)
    {
        m_acceptor.close();
        error.fail(ec.value(), ec.message(), __FILE__, __LINE__);
        return;
    }
    m_acceptor.listen(boost::asio::socket_base::max_listen_connections, ec);
    if (ec)
    {
        m_acceptor.close();
        error.fail(ec.value(), ec.message(), __FILE__, __LINE__);
        return;
    }
}

void BeastListener::run()
{
    if (m_acceptor.is_open())
    {
        accept();
    }
}

void BeastListener::accept()
{
    m_acceptor.async_accept(m_socket, std::bind(&BeastListener::onAccept, this, std::placeholders::_1));
}

void BeastListener::onAccept(boost::system::error_code ec)
{
    if (!ec)
    {
        const std::string& sourceAddress = m_socket.remote_endpoint().address().to_string();
        m_server.observers().notify(&Server::Observer::onConnection, m_server, sourceAddress);
        std::shared_ptr<BeastSession> session = std::make_shared<BeastSession>(std::move(m_socket));
        session->run();
    }

    accept();
}

}
