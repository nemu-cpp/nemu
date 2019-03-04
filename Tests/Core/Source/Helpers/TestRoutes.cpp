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

#include "TestRoutes.h"

TestRoutes::TestRoutes()
    : m_visitedRoutes(std::make_shared<std::vector<std::string>>())
{
    setDefaultRoute(Nemu::Route("",
        [](const Nemu::WebRequest& request, Nemu::WebResponseBuilder& response, void* handlerData)
        {
            response.setStatus(404);

            TestRoutes* routes = reinterpret_cast<TestRoutes*>(handlerData);
            std::lock_guard<std::mutex> guard(routes->m_visitedRoutesMutex);
            routes->m_visitedRoutes->push_back(request.URI());
        },
        std::shared_ptr<TestRoutes>(this, [](TestRoutes*) {})));
}

const std::vector<std::string>& TestRoutes::visitedRoutes() const
{
    return *m_visitedRoutes;
}
