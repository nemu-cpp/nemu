// SPDX-FileCopyrightText: 2020-2024 Xavier Leclercq
// SPDX-License-Identifier: MIT

#include "CommandLineSpecification.hpp"

using namespace Nemu;

CommandLineSpecification::CommandLineSpecification()
{
    addPositionalOption(1, "command", {Ishiko::CommandLineSpecification::OptionType::single_value});
 
    Ishiko::CommandLineSpecification::CommandDetails& get_command_details = addCommand("command", "get");
    get_command_details.addPositionalOption(2, "url", {Ishiko::CommandLineSpecification::OptionType::single_value});

    addNamedOption("output-path", {Ishiko::CommandLineSpecification::OptionType::single_value});
}
