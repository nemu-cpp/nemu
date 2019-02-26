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

#ifndef _NEMUFRAMEWORK_NEMU_CORE_ROUTES_H_
#define _NEMUFRAMEWORK_NEMU_CORE_ROUTES_H_

#include "Route.h"
#include <vector>
#include <string>

namespace Nemu
{

/// A sequence of routes.
/**
    In addition to the routes explicitly added to the sequence a default route is also stored. It is returned by the
    Routes::match function if no match is found.

    This class is used by the Application class to store the route specifications. There should usually be no need to
    create an instance of this class yourself.
*/
class Routes
{
public:
    /// Constructor.
    Routes();

    /// Appends a route to the sequence.
    /**
        @param route The route to add.
    */
    void append(const Route& route);

    /// Finds the first route in the sequence that matches the path.
    /**
        If no match is found the default route is returned.
        @param path The path to match.
    */
    const Route& match(const std::string& path) const;

    const Route& defaultRoute() const;

private:
    std::vector<Route> m_routes;
    Route m_defaultRoute;
};

}

#include "linkoptions.h"

#endif
