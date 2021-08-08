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

#ifndef _NEMUFRAMEWORK_NEMU_CORE_WEBAPPLICATION_H_
#define _NEMUFRAMEWORK_NEMU_CORE_WEBAPPLICATION_H_

#include "Application.h"
#include "Configuration.h"
#include "Routes.h"
#include "Views.h"
#include "Ishiko/Errors/Error.h"
#include <vector>
#include <memory>

namespace Nemu
{

/// An application that serves requests over the HTTP or HTTPS protocol.
class WebApplication : public Application
{
public:
    /// Constructor.
    /**
        @param configuration The configuration for the application.
        @param observer The observer to add.
        @param error The result of the constructor.
    */
    WebApplication(const Configuration& configuration, std::shared_ptr<Observer> observer, Ishiko::Error& error);
    WebApplication(const Configuration& configuration, std::shared_ptr<Routes> routes,
        std::shared_ptr<Observer> observer, Ishiko::Error& error);

    /// Returns the routes.
    Routes& routes();

    Views& views();

private:
    std::shared_ptr<Routes> m_routes;
    Views m_views;
};

}

#include "linkoptions.h"

#endif
