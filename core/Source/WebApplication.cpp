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

#include "WebApplication.h"
#include "Beast/BeastServer.h"

namespace Nemu
{

WebApplication::WebApplication(const Configuration& configuration, std::shared_ptr<Observer> observer, Ishiko::Error& error)
    : Application(observer), m_routes(std::make_shared<Routes>())
{
    servers().append(std::make_shared<BeastServer>(configuration.numberOfThreads(), configuration.address(),
        configuration.port(), *m_routes, m_views, observer, error));
}

WebApplication::WebApplication(const Configuration& configuration, std::shared_ptr<Routes> routes,
    std::shared_ptr<Observer> observer, Ishiko::Error& error)
    : Application(observer), m_routes(routes)
{
    servers().append(std::make_shared<BeastServer>(configuration.numberOfThreads(), configuration.address(),
        configuration.port(), *m_routes, m_views, observer, error));
}

Routes& WebApplication::routes()
{
    return *m_routes;
}

Views& WebApplication::views()
{
    return m_views;
}

}
