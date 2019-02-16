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
#include "BeastServer.h"
#ifdef _WIN32
#include "ControlHandlerRegistration.h"
#endif

namespace Nemu
{

WebApplication::WebApplication(const Configuration& configuration, std::shared_ptr<Observer> observer, Ishiko::Error& error)
{
    m_observers.add(observer);

    servers().append(std::make_shared<BeastServer>(configuration.numberOfThreads(), configuration.address(),
        configuration.port(), observer, error));
}

void WebApplication::start()
{
    m_observers.notify(&Observer::onApplicationStarting, *this);

#ifdef _WIN32
    m_controlHandlerRegistration = std::make_unique<ControlHandlerRegistration>();
#endif

    // First we start all the servers, note that the Servers::startAll() function does not block
    servers().startAll();

    m_observers.notify(&Observer::onApplicationStarted, *this);

    // By default we want the Application::start() function to block so we call Servers::joinAll() which will do a join
    // on all the servers
    servers().joinAll();

    m_observers.notify(&Observer::onApplicationStopped, *this);
}

void WebApplication::stop()
{
    m_observers.notify(&Observer::onApplicationStopping, *this);

    servers().stopAll();

#ifdef _WIN32
    m_controlHandlerRegistration.reset();
#endif
}

WebApplication::Observers& WebApplication::observers()
{
    return m_observers;
}

}
