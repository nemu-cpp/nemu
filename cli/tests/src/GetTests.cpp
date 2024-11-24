// SPDX-FileCopyrightText: 2020-2024 Xavier Leclercq
// SPDX-License-Identifier: MIT

#include "GetTests.hpp"

GetTests::GetTests(const Ishiko::TestNumber& number, const Ishiko::TestContext& context)
    : Ishiko::TestSequence(number, "get command tests", context)
{
    GetTest1(*this);
}

void GetTests::GetTest1(Ishiko::TestSequence& test_sequence)
{
}
