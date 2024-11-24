// SPDX-FileCopyrightText: 2020-2024 Xavier Leclercq
// SPDX-License-Identifier: MIT

#include "GetTests.hpp"
#include <boost/filesystem.hpp>

GetTests::GetTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context)
    : Ishiko::TestSequence(number, "get command tests", context)
{
    GetTest1(*this);
}

void GetTests::GetTest1(Ishiko::TestSequence& test_sequence)
{
    const char* output_name = "GetTests_GetTest1.txt";

    boost::filesystem::path application_path = test_sequence.context().getApplicationPath();
    boost::filesystem::path output_path = test_sequence.context().getOutputPath(output_name);

    std::string command_line = application_path.string()
        + " get http://nemu.io --output-path=" + output_path.string();

    test_sequence.append<Ishiko::ConsoleApplicationTest>("get command test 1", command_line,
        [output_name](int exit_code, Ishiko::ConsoleApplicationTest& test)
        {
            ISHIKO_TEST_ABORT_IF_NEQ(exit_code, 0);
            ISHIKO_TEST_FAIL_IF_OUTPUT_AND_REFERENCE_FILES_NEQ(output_name);
            ISHIKO_TEST_PASS();
        }
    );
}
