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

#include "ConfigurationTests.h"
#include "NemuFramework/Nemu/Core/Configuration.h"

using namespace Ishiko::Tests;

ConfigurationTests::ConfigurationTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "Configuration tests", environment)
{
    append<HeapAllocationErrorsTest>("Creation test 1", CreationTest1);
    append<HeapAllocationErrorsTest>("Creation test 2", CreationTest2);
    append<HeapAllocationErrorsTest>("Creation test 3", CreationTest3);
}

void ConfigurationTests::CreationTest1(Test& test)
{
    int argc = 1;
    char* argv[] = { "NemuTests" };
    Nemu::Configuration configuration(argc, argv);

    ISHTF_FAIL_UNLESS(configuration.address() == "0.0.0.0");
    ISHTF_FAIL_UNLESS(configuration.port() == 80);
    ISHTF_PASS();
}

void ConfigurationTests::CreationTest2(Test& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    int argc = 1;
    char* argv[] = { "NemuTests" };
    Nemu::Configuration configuration(argc, argv, "127.0.0.1", 8080);
    if ((configuration.address() == "127.0.0.1") && (configuration.port() == 8080))
    {
        result = TestResult::ePassed;
    }

    return result;
}

void ConfigurationTests::CreationTest3(Test& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    Nemu::Configuration configuration("0.0.0.0", 80);
    if ((configuration.address() == "0.0.0.0") && (configuration.port() == 80))
    {
        result = TestResult::ePassed;
    }

    return result;
}
