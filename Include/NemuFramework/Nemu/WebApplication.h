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

#ifndef _NEMUFRAMEWORK_NEMU_WEBAPPLICATION_H_
#define _NEMUFRAMEWORK_NEMU_WEBAPPLICATION_H_

#include "Application.h"
#include "Configuration.h"
#include "Routes.h"
#include "Ishiko/Errors/Error.h"
#include <vector>
#include <set>
#include <mutex>
#include <memory>

namespace Nemu
{

#ifdef _WIN32
class ControlHandlerRegistration;
#endif

class WebApplication : public Application
{
public:
    WebApplication(const Configuration& configuration, std::shared_ptr<Observer> observer, Ishiko::Error& error);
    ~WebApplication();

    void start();
    void stop();

    static void StopAllApplications();

    Observers& observers();

private:
    static std::mutex sm_applicationsMutex;
    static std::set<WebApplication*> sm_applications;
#ifdef _WIN32
    std::unique_ptr<ControlHandlerRegistration> m_controlHandlerRegistration;
#endif
    Routes routes;
    Observers m_observers;
};

}

#include "linkoptions.h"

#endif
