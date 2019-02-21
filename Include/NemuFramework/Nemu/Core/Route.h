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

#ifndef _NEMUFRAMEWORK_NEMU_CORE_ROUTE_H_
#define _NEMUFRAMEWORK_NEMU_CORE_ROUTE_H_

#include "WebRequest.h"
#include "WebResponse.h"
#include <string>

namespace Nemu
{

/// A request routing specification for a web application.
class Route
{
public:
    /// The type definition for the request handlers.
    /**
        @param request The request that was received from the client.
        @param response This argument is used to build the response that will be returned to the client.
    */
    typedef void (*RequestHandler)(const WebRequest& request, WebResponse& response);

    /// Constructor.
    /**
        @param path The handler handles requests that match this path.
        @param handler The request handler.
    */
    Route(const std::string& path, RequestHandler handler);

    /// Returns the path.
    const std::string& path() const;
    /// Returns the handler.
    RequestHandler handler() const;

private:
    std::string m_path;
    RequestHandler m_handler;
};

}

#include "linkoptions.h"

#endif
