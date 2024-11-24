// SPDX-FileCopyrightText: 2020-2024 Xavier Leclercq
// SPDX-License-Identifier: MIT

#include "GetCommandTests.hpp"
#include <Ishiko/BasePlatform.hpp>
#include <Ishiko/TestFramework.hpp>
#include <exception>

int main(int argc, char* argv[])
{
    try
    {
        Ishiko::TestHarness::CommandLineSpecification command_line_spec;
        Ishiko::Configuration configuration = command_line_spec.createDefaultConfiguration();
        configuration.set("context.data", "../../data");
        configuration.set("context.reference", "../../reference");
        configuration.set("context.output", "../../output");
#if ISHIKO_OS == ISHIKO_OS_LINUX
        configuration.set("context.application-path", "../../../../bin/NemuCLI");
#elif ISHIKO_OS == ISHIKO_OS_WINDOWS
        configuration.set("context.application-path", "../../../../bin/x64/NemuCLI.exe");
#else
#error Unsupported or unrecognized OS
#endif
        Ishiko::CommandLineParser::parse(command_line_spec, argc, argv, configuration);

        Ishiko::TestHarness the_test_harness("Nemu CLI Tests", configuration);

        Ishiko::TestSequence& the_tests = the_test_harness.tests();
        the_tests.append<GetCommandTests>();

        return the_test_harness.run();
    }
    catch (const std::exception& e)
    {
        return Ishiko::TestApplicationReturnCode::exception;
    }
    catch (...)
    {
        return Ishiko::TestApplicationReturnCode::exception;
    }
}
