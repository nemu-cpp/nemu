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

#ifndef _NEMUFRAMEWORK_NEMU_APPLICATION_H_
#define _NEMUFRAMEWORK_NEMU_APPLICATION_H_

#include "Servers.h"

namespace Nemu
{

#ifdef _WIN32
class ControlHandlerRegistration;
#endif

class Application
{
public:
    class Observer : public Server::Observer
    {
    public:
        virtual void onApplicationStarting(const Application& source);
        virtual void onApplicationStarted(const Application& source);
        virtual void onApplicationStopping(const Application& source);
        virtual void onApplicationStopped(const Application& source);
    };

    class Observers final
    {
    public:
        void add(std::shared_ptr<Observer> observer);
        void remove(std::shared_ptr<Observer> observer);

        void notify(void (Observer::*fct)(const Application& source), const Application& source);

    private:
        void removeDeletedObservers();

    private:
        std::vector<std::pair<std::weak_ptr<Observer>, size_t>> m_observers;
    };

    Application(std::shared_ptr<Observer> observer);
    virtual ~Application();

    void start();
    void stop();

    const Servers& servers() const;
    Observers& observers();

protected:
    Servers& servers();

private:
#ifdef _WIN32
    std::unique_ptr<ControlHandlerRegistration> m_controlHandlerRegistration;
#endif
    Servers m_servers;
    Observers m_observers;
};

}

#include "linkoptions.h"

#endif
