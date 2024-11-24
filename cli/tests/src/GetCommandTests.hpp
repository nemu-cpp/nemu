// SPDX-FileCopyrightText: 2020-2024 Xavier Leclercq
// SPDX-License-Identifier: MIT

#ifndef GUARD_NEMU_CPP_NEMU_CLI_TESTS_GETCOMMANDTESTS_HPP
#define GUARD_NEMU_CPP_NEMU_CLI_TESTS_GETCOMMANDTESTS_HPP

#include <Ishiko/TestFramework.hpp>

class GetCommandTests : public Ishiko::TestSequence
{
public:
    GetCommandTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context);

private:
    static void GetTest1(Ishiko::TestSequence& test_sequence);
};

#endif
