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

#ifndef _NEMUFRAMEWORK_NEMU_LOG_H_
#define _NEMUFRAMEWORK_NEMU_LOG_H_

#include "Application.h"
#include <g3log/g3log.hpp>
#include <g3log/logworker.hpp>
#include <string>

namespace Nemu
{

/// A log.
/**
    This is a wrapper around G3log (https://github.com/KjellKod/g3log).
*/
class Log : public Application::Observer
{
public:
    enum ELogDestination
    {
        eConsole = 0x01,
        eFile = 0x02
    };

    /// Constructor.
    /**
        @param filenamePrefix The prefix of the log file name. For instance this can be the name of the application.
    */
    Log(const std::string& filenamePrefix);
    Log(const std::string& filenamePrefix, ELogDestination destination);

    void onApplicationStarting(const Application& source) override;
    void onApplicationStarted(const Application& source) override;
    void onApplicationStopping(const Application& source) override;
    void onApplicationStopped(const Application& source) override;
    void onServerStarted(const Server& source) override;
    void onServerStopped(const Server& source) override;
    void onConnectionOpened(const Server& source, const std::string& sourceAddress) override;
    void onConnectionClosed(const Server& source, const std::string& sourceAddress) override;

private:
    static std::string FormatMessage(const g3::LogMessage& message);

private:
    std::unique_ptr<g3::LogWorker> m_worker;
    std::unique_ptr<g3::FileSinkHandle> m_handle;
};

}

#include "linkoptions.h"

#endif
