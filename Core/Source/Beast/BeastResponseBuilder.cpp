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

#include "BeastResponseBuilder.h"

namespace Nemu
{

BeastResponseBuilder::BeastResponseBuilder(const Views& views)
    : WebResponseBuilder(views)
{
}

void BeastResponseBuilder::initialize(const boost::beast::http::request<boost::beast::http::string_body>& request)
{
    m_response = boost::beast::http::response<boost::beast::http::string_body>();
    m_response.keep_alive(request.keep_alive());
}

void BeastResponseBuilder::reset()
{
    m_response = boost::beast::http::response<boost::beast::http::string_body>();
}

void BeastResponseBuilder::setStatus(unsigned int status)
{
    m_response.result(status);
}

std::string& BeastResponseBuilder::body()
{
    return m_response.body();
}

boost::beast::http::response<boost::beast::http::string_body>& BeastResponseBuilder::response()
{
    return m_response;
}

}
