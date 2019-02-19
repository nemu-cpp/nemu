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

#include "Log.h"

namespace Nemu
{

Log::Log(const std::string& filenamePrefix)
{
    m_worker = g3::LogWorker::createLogWorker();
    m_handle = m_worker->addDefaultLogger(filenamePrefix, ".");
    g3::initializeLogging(m_worker.get());
    m_handle->call(&g3::FileSink::overrideLogDetails, &FormatMessage);
}

void Log::onApplicationStarting(const Application& source)
{
    LOG(INFO) << "Application starting";
}

void Log::onApplicationStarted(const Application& source)
{
    size_t running = source.servers().numberOfRunningServers();
    LOG(INFO) << "Application started (" << running << " server" << ((running != 1) ? "s" : "") << " running)";
}

void Log::onApplicationStopping(const Application& source)
{
    LOG(INFO) << "Application stopping";
}

void Log::onApplicationStopped(const Application& source)
{
    size_t running = source.servers().numberOfRunningServers();
    LOG(INFO) << "Application stopped (" << running << " server" << ((running != 1) ? "s" : "") << " running)";
}

void Log::onServerStarted(const Server& source)
{
    LOG(INFO) << "Server started";
}

void Log::onServerStopped(const Server& source)
{
    LOG(INFO) << "Server stopped";
}

void Log::onConnectionOpened(const Server& source, const std::string& sourceAddress)
{
    LOG(INFO) << "Connection from " << sourceAddress << " opened";
}

void Log::onConnectionClosed(const Server& source, const std::string& sourceAddress)
{
    LOG(INFO) << "Connection from " << sourceAddress << " closed";
}

std::string Log::FormatMessage(const g3::LogMessage& message)
{
    std::string out;
    out.append(message.timestamp({"%Y-%m-%dT%H:%M:%S.%f6"}) + " (" + message.threadID() + ") [" + message.file() + ":"
        + message.line() + "] " + message.level() + " ");
    return out;
}

}
