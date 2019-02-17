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

#include "Server.h"
#include <algorithm>

namespace Nemu
{

void Server::Observer::onServerStarted(const Server& source)
{
}

void Server::Observer::onServerStopped(const Server& source)
{
}

void Server::Observer::onConnectionOpened(const Server& source, const std::string& sourceAddress)
{
}

void Server::Observer::onConnectionClosed(const Server& source, const std::string& sourceAddress)
{
}

void Server::Observers::add(std::shared_ptr<Observer> observer)
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

void Server::Observers::remove(std::shared_ptr<Observer> observer)
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

void Server::Observers::notify(void (Observer::*fct)(const Server& source), const Server& source)
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

void Server::Observers::notify(void (Observer::*fct)(const Server& source, const std::string& sourceAddress),
    const Server& source, const std::string& sourceAddress)
{
    for (std::pair<std::weak_ptr<Observer>, size_t>& o : m_observers)
    {
        std::shared_ptr<Observer> observer = o.first.lock();
        if (observer)
        {
            ((*observer).*fct)(source, sourceAddress);
        }
        else
        {
            removeDeletedObservers();
        }
    }
}

void Server::Observers::removeDeletedObservers()
{
    auto it = std::remove_if(m_observers.begin(), m_observers.end(),
        [](const std::pair<std::weak_ptr<Observer>, size_t>& o)
        {
            return o.first.expired();
        }
    );
    m_observers.erase(it, m_observers.end());
}

Server::Server(std::shared_ptr<Observer> observer)
{
    m_observers.add(observer);
}

Server::Observers& Server::observers()
{
    return m_observers;
}

}
