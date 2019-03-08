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

#include "BeastServerTests.h"
#include "../Helpers/TestRoutes.h"
#include "../Helpers/TestServerObserver.h"
#include "Beast/BeastServer.h"
#include "Ishiko/HTTP/HTTPClient.h"
#include <boost/filesystem/operations.hpp>
#include <thread>

using namespace Ishiko::Tests;

BeastServerTests::BeastServerTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "BeastServer tests", environment)
{
    append<HeapAllocationErrorsTest>("Creation test 1", CreationTest1);
    append<HeapAllocationErrorsTest>("start test 1", StartTest1);
    append<HeapAllocationErrorsTest>("start test 2", StartTest2);
    append<HeapAllocationErrorsTest>("start test 3", StartTest3);
    append<FileComparisonTest>("Request test 1", RequestTest1);
    append<FileComparisonTest>("Request test 2", RequestTest2);
    append<HeapAllocationErrorsTest>("Request test 3", RequestTest3);
    append<HeapAllocationErrorsTest>("Request test 4", RequestTest4);
    append<HeapAllocationErrorsTest>("Request test 5", RequestTest5);
}

void BeastServerTests::CreationTest1(Test& test)
{
    Nemu::Routes routes;
    Nemu::Views views;
    std::shared_ptr<Nemu::Server::Observer> observer;
    Ishiko::Error error(0);
    Nemu::BeastServer server(1, "127.0.0.1", 8088, routes, views, observer, error);

    ISHTF_FAIL_IF((bool)error);
    ISHTF_PASS();
}

void BeastServerTests::StartTest1(Test& test)
{
    TestRoutes routes;
    Nemu::Views views;
    std::shared_ptr<TestServerObserver> observer = std::make_shared<TestServerObserver>();
    Ishiko::Error error(0);
    Nemu::BeastServer server(1, "127.0.0.1", 8088, routes, views, observer, error);

    ISHTF_ABORT_IF((bool)error);

    server.start();
    server.stop();
    server.join();

    ISHTF_FAIL_UNLESS(routes.visitedRoutes().size() == 0);
    ISHTF_FAIL_UNLESS(observer->connectionEvents().size() == 0);
    ISHTF_PASS();
}

void BeastServerTests::StartTest2(Test& test)
{
    TestRoutes routes;
    Nemu::Views views;
    std::shared_ptr<TestServerObserver> observer = std::make_shared<TestServerObserver>();
    Ishiko::Error error(0);
    Nemu::BeastServer server(16, "127.0.0.1", 8088, routes, views, observer, error);

    ISHTF_ABORT_IF((bool)error);

    server.start();
    server.stop();
    server.join();

    ISHTF_FAIL_UNLESS(routes.visitedRoutes().size() == 0);
    ISHTF_FAIL_UNLESS(observer->connectionEvents().size() == 0);
    ISHTF_PASS();
}

void BeastServerTests::StartTest3(Test& test)
{
    TestRoutes routes;
    Nemu::Views views;
    std::shared_ptr<TestServerObserver> observer = std::make_shared<TestServerObserver>();
    Ishiko::Error error(0);
    Nemu::BeastServer server(128, "127.0.0.1", 8088, routes, views, observer, error);

    ISHTF_ABORT_IF((bool)error);

    server.start();
    server.stop();
    server.join();

    ISHTF_FAIL_UNLESS(routes.visitedRoutes().size() == 0);
    ISHTF_FAIL_UNLESS(observer->connectionEvents().size() == 0);
    ISHTF_PASS();
}

void BeastServerTests::RequestTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "BeastTests/BeastServerTests_RequestTest1.txt");
    boost::filesystem::remove(outputPath);
    boost::filesystem::path referencePath(test.environment().getReferenceDataDirectory() / "BeastTests/BeastServerTests_RequestTest1.txt");

    TestRoutes routes;
    Nemu::Views views;
    std::shared_ptr<TestServerObserver> observer = std::make_shared<TestServerObserver>();
    Ishiko::Error error(0);
    Nemu::BeastServer server(1, "127.0.0.1", 8088, routes, views, observer, error);

    ISHTF_ABORT_IF((bool)error);

    server.start();

    std::ofstream responseFile(outputPath.string());
    Ishiko::HTTP::HTTPClient::get("127.0.0.1", 8088, "/", responseFile, error);
    responseFile.close();

    server.stop();
    server.join();

    ISHTF_ABORT_IF((bool)error);

    const std::vector<std::tuple<TestServerObserver::EEventType, const Nemu::Server*, std::string>>& events =
        observer->connectionEvents();
    ISHTF_FAIL_UNLESS(events.size() == 2);
    ISHTF_FAIL_UNLESS(std::get<0>(events[0]) == TestServerObserver::eConnectionOpened);
    ISHTF_FAIL_UNLESS(std::get<1>(events[0]) == &server);
    ISHTF_FAIL_UNLESS(std::get<2>(events[0]).substr(0, 10) == "127.0.0.1:");
    ISHTF_FAIL_UNLESS(std::get<0>(events[1]) == TestServerObserver::eConnectionClosed);
    ISHTF_FAIL_UNLESS(std::get<1>(events[1]) == &server);
    ISHTF_FAIL_UNLESS(std::get<2>(events[0]) == std::get<2>(events[1]));
    ISHTF_FAIL_UNLESS(routes.visitedRoutes().size() == 1);
    ISHTF_FAIL_UNLESS(routes.visitedRoutes()[0] == "/");
    ISHTF_PASS();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);
}

void BeastServerTests::RequestTest2(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "BeastTests/BeastServerTests_RequestTest2.txt");
    boost::filesystem::remove(outputPath);
    boost::filesystem::path referencePath(test.environment().getReferenceDataDirectory() / "BeastTests/BeastServerTests_RequestTest2.txt");

    TestRoutes routes;
    Nemu::Views views;
    std::shared_ptr<TestServerObserver> observer = std::make_shared<TestServerObserver>();
    Ishiko::Error error(0);
    Nemu::BeastServer server(1, "127.0.0.1", 8088, routes, views, observer, error);

    ISHTF_ABORT_IF((bool)error);

    server.start();

    std::ofstream responseFile(outputPath.string());
    Ishiko::HTTP::HTTPClient::get("127.0.0.1", 8088, "/", responseFile, error);
    Ishiko::HTTP::HTTPClient::get("127.0.0.1", 8088, "/", responseFile, error);
    responseFile.close();

    server.stop();
    server.join();

    ISHTF_ABORT_IF((bool)error);

    const std::vector<std::tuple<TestServerObserver::EEventType, const Nemu::Server*, std::string>>& events =
        observer->connectionEvents();
    ISHTF_FAIL_UNLESS(events.size() == 4);
    ISHTF_FAIL_UNLESS(std::get<0>(events[0]) == TestServerObserver::eConnectionOpened);
    ISHTF_FAIL_UNLESS(std::get<1>(events[0]) == &server);
    ISHTF_FAIL_UNLESS(std::get<2>(events[0]).substr(0, 10) == "127.0.0.1:");
    ISHTF_FAIL_UNLESS(std::get<0>(events[1]) == TestServerObserver::eConnectionClosed);
    ISHTF_FAIL_UNLESS(std::get<1>(events[1]) == &server);
    ISHTF_FAIL_UNLESS(std::get<2>(events[0]) == std::get<2>(events[1]));
    ISHTF_FAIL_UNLESS(std::get<0>(events[2]) == TestServerObserver::eConnectionOpened);
    ISHTF_FAIL_UNLESS(std::get<1>(events[2]) == &server);
    ISHTF_FAIL_UNLESS(std::get<2>(events[2]).substr(0, 10) == "127.0.0.1:");
    ISHTF_FAIL_UNLESS(std::get<0>(events[3]) == TestServerObserver::eConnectionClosed);
    ISHTF_FAIL_UNLESS(std::get<1>(events[3]) == &server);
    ISHTF_FAIL_UNLESS(std::get<2>(events[2]) == std::get<2>(events[3]));
    ISHTF_FAIL_UNLESS(routes.visitedRoutes().size() == 2);
    ISHTF_FAIL_UNLESS(routes.visitedRoutes()[0] == "/");
    ISHTF_FAIL_UNLESS(routes.visitedRoutes()[1] == "/");
    ISHTF_PASS();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);
}

void BeastServerTests::RequestTest3(Test& test)
{
    TestRoutes routes;
    Nemu::Views views;
    std::shared_ptr<TestServerObserver> observer = std::make_shared<TestServerObserver>();
    Ishiko::Error error(0);
    Nemu::BeastServer server(1, "127.0.0.1", 8088, routes, views, observer, error);

    ISHTF_ABORT_IF((bool)error);

    server.start();

    for (size_t i = 0; i < 100; ++i)
    {
        std::stringstream response;
        Ishiko::HTTP::HTTPClient::get("127.0.0.1", 8088, "/", response, error);

        ISHTF_ABORT_IF((bool)error);
    }

    server.stop();
    server.join();

    const std::vector<std::tuple<TestServerObserver::EEventType, const Nemu::Server*, std::string>>& events =
        observer->connectionEvents();
    ISHTF_FAIL_UNLESS(events.size() == 200);
    ISHTF_FAIL_UNLESS(routes.visitedRoutes().size() == 100);
    ISHTF_PASS();
}

void BeastServerTests::RequestTest4(Test& test)
{
    TestRoutes routes;
    Nemu::Views views;
    std::shared_ptr<TestServerObserver> observer = std::make_shared<TestServerObserver>();
    Ishiko::Error error(0);
    Nemu::BeastServer server(1, "127.0.0.1", 8088, routes, views, observer, error);

    ISHTF_ABORT_IF((bool)error);

    server.start();

    std::vector<std::thread> threads;
    for (size_t i = 0; i < 4; ++i)
    {
        threads.push_back(std::thread(
            []()
        {
            for (size_t i = 0; i < 25; ++i)
            {
                Ishiko::Error error(0);
                std::stringstream response;
                Ishiko::HTTP::HTTPClient::get("127.0.0.1", 8088, "/", response, error);
            }
        }));
    }
    for (std::thread& t : threads)
    {
        t.join();
    }

    server.stop();
    server.join();

    const std::vector<std::tuple<TestServerObserver::EEventType, const Nemu::Server*, std::string>>& events =
        observer->connectionEvents();
    ISHTF_FAIL_UNLESS(events.size() == 200);
    ISHTF_FAIL_UNLESS(routes.visitedRoutes().size() == 100);
    ISHTF_PASS();
}

void BeastServerTests::RequestTest5(Test& test)
{
    TestRoutes routes;
    Nemu::Views views;
    std::shared_ptr<TestServerObserver> observer = std::make_shared<TestServerObserver>();
    Ishiko::Error error(0);
    Nemu::BeastServer server(16, "127.0.0.1", 8088, routes, views, observer, error);

    ISHTF_ABORT_IF((bool)error);

    server.start();

    std::vector<std::thread> threads;
    for (size_t i = 0; i < 4; ++i)
    {
        threads.push_back(std::thread(
            []()
        {
            for (size_t i = 0; i < 25; ++i)
            {
                Ishiko::Error error(0);
                std::stringstream response;
                Ishiko::HTTP::HTTPClient::get("127.0.0.1", 8088, "/", response, error);
            }
        }));
    }
    for (std::thread& t : threads)
    {
        t.join();
    }

    server.stop();
    server.join();

    const std::vector<std::tuple<TestServerObserver::EEventType, const Nemu::Server*, std::string>>& events =
        observer->connectionEvents();
    ISHTF_FAIL_UNLESS(events.size() == 200);
    ISHTF_FAIL_UNLESS(routes.visitedRoutes().size() == 100);
    ISHTF_PASS();
}
