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

#include "Configuration.h"
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/parsers.hpp>

namespace Nemu
{

Configuration::Configuration(int argc, char* argv[], const std::string& defaultAddress, unsigned short defaultPort)
{
    boost::program_options::options_description description("Command line arguments");
    description.add_options()
        ("address", boost::program_options::value<std::string>(&m_address)->value_name("str")->default_value(defaultAddress),
            "the listening IP address")
        ("port", boost::program_options::value<unsigned short>(&m_port)->value_name("p")->default_value(defaultPort),
            "the listening port")
        ("threads", boost::program_options::value<size_t>(&m_numberOfThreads)->value_name("n")->default_value(1),
            "the number of threads that will be used to process incoming requests");

    boost::program_options::variables_map vm;
    boost::program_options::store(boost::program_options::parse_command_line(argc, argv, description), vm);
    boost::program_options::notify(vm);
}

Configuration::Configuration(const std::string& address, unsigned short port)
    : m_address(address), m_port(port)
{
}

size_t Configuration::numberOfThreads() const
{
    return m_numberOfThreads;
}

const std::string& Configuration::address() const
{
    return m_address;
}

unsigned short Configuration::port() const
{
    return m_port;
}

}
