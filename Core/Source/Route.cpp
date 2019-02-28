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

#include "Route.h"

namespace Nemu
{

Route::Route(const std::string& path, RequestHandler handler)
    : m_path(path), m_handler(handler)
{
}

Route::Route(const std::string& path, RequestHandler handler, std::shared_ptr<void> handlerData)
    : m_path(path), m_handler(handler), m_handlerData(handlerData)
{
}

const std::string& Route::path() const
{
    return m_path;
}

Route::RequestHandler Route::handler() const
{
    return m_handler;
}

void* Route::handlerData() const
{
    return m_handlerData.get();
}

void Route::runHandler(const WebRequest& request, WebResponseBuilder& response) const
{
    m_handler(request, response, m_handlerData.get());
}

}
