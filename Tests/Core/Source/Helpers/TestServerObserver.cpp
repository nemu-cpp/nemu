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

#include "TestServerObserver.h"

const std::vector<std::tuple<TestServerObserver::EEventType, const Nemu::Server*, std::string>>&
TestServerObserver::connectionEvents() const
{
    return m_connectionEvents;
}

void TestServerObserver::onConnectionOpened(const Nemu::Server& source, const std::string& sourceAddress)
{
    std::lock_guard<std::mutex> guard(m_connectionEventsMutex);
    m_connectionEvents.emplace_back(eConnectionOpened, &source, sourceAddress);
}

void TestServerObserver::onConnectionClosed(const Nemu::Server& source, const std::string& sourceAddress)
{
    std::lock_guard<std::mutex> guard(m_connectionEventsMutex);
    m_connectionEvents.emplace_back(eConnectionClosed, &source, sourceAddress);
}
