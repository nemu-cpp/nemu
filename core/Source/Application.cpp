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

#include "Application.h"
#include "Applications.h"
#ifdef _WIN32
#include "ControlHandlerRegistration.h"
#endif
#include <algorithm>

namespace Nemu
{

void Application::Observer::onApplicationStarting(const Application& source)
{
}

void Application::Observer::onApplicationStarted(const Application& source)
{
}

void Application::Observer::onApplicationStopping(const Application& source)
{
}

void Application::Observer::onApplicationStopped(const Application& source)
{
}

void Application::Observers::add(std::shared_ptr<Observer> observer)
{
    auto it = std::find_if(m_observers.begin(), m_observers.end(),
        [&observer](const std::pair<std::weak_ptr<Observer>, size_t>& o)
        {
            return (o.first.lock() == observer);
        }
    );
    if (it != m_observers.end())
    {
        ++it->second;
    }
    else
    {
        m_observers.push_back(std::pair<std::weak_ptr<Observer>, size_t>(observer, 1));
    }
}

void Application::Observers::remove(std::shared_ptr<Observer> observer)
{
    auto it = std::find_if(m_observers.begin(), m_observers.end(),
        [&observer](const std::pair<std::weak_ptr<Observer>, size_t>& o)
        {
            return (o.first.lock() == observer);
        }
    );
    if (it != m_observers.end())
    {
        --it->second;
        if (it->second == 0)
        {
            m_observers.erase(it);
        }
    }
}

void Application::Observers::notify(void (Observer::*fct)(const Application& source), const Application& source)
{
    for (std::pair<std::weak_ptr<Observer>, size_t>& o : m_observers)
    {
        std::shared_ptr<Observer> observer = o.first.lock();
        if (observer)
        {
            ((*observer).*fct)(source);
        }
        else
        {
            removeDeletedObservers();
        }
    }
}

void Application::Observers::removeDeletedObservers()
{
    auto it = std::remove_if(m_observers.begin(), m_observers.end(),
        [](const std::pair<std::weak_ptr<Observer>, size_t>& o)
        {
            return o.first.expired();
        }
    );
    m_observers.erase(it, m_observers.end());
}

Application::Application(std::shared_ptr<Observer> observer)
{
    m_observers.add(observer);
    Applications::set(this);
}

Application::~Application()
{
    Applications::unset(this);
}

void Application::start()
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

void Application::stop()
{
    m_observers.notify(&Observer::onApplicationStopping, *this);

    servers().stopAll();

#ifdef _WIN32
    m_controlHandlerRegistration.reset();
#endif
}

const Servers& Application::servers() const
{
    return m_servers;
}

Application::Observers& Application::observers()
{
    return m_observers;
}

Servers& Application::servers()
{
    return m_servers;
}

}
