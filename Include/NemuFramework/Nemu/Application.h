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

#include "Configuration.h"
#include "Server.h"
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

class Application
{
public:
    class Observer : public Server::Observer
    {
    public:
        virtual void onApplicationStarted(const Application& source);
    };

    class Observers final
    {
    public:
        void add(std::shared_ptr<Observer> observer);
        void remove(std::shared_ptr<Observer> observer);

        void notifyApplicationStarted(const Application& source);

    private:
        void removeDeletedObservers();

    private:
        std::vector<std::pair<std::weak_ptr<Observer>, size_t>> m_observers;
    };

    Application(const Configuration& configuration, std::shared_ptr<Observer> observer, Ishiko::Error& error);
    ~Application();

    void start();
    void stop();

    static void StopAllApplications();

    Observers& observers();

private:
    static std::mutex sm_applicationsMutex;
    static std::set<Application*> sm_applications;
#ifdef _WIN32
    std::unique_ptr<ControlHandlerRegistration> m_controlHandlerRegistration;
#endif
    std::vector<std::shared_ptr<Server>> m_servers;
    Observers m_observers;
};

}

#include "linkoptions.h"

#endif
