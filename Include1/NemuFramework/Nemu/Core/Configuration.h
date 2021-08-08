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

#ifndef _NEMUFRAMEWORK_NEMU_CORE_CONFIGURATION_H_
#define _NEMUFRAMEWORK_NEMU_CORE_CONFIGURATION_H_

#include <string>

namespace Nemu
{

class Configuration
{
public:
    Configuration(int argc, char* argv[], const std::string& defaultAddress = "0.0.0.0", unsigned short defaultPort = 80);
    Configuration(const std::string& address, unsigned short port);

    size_t numberOfThreads() const;
    const std::string& address() const;
    unsigned short port() const;

private:
    size_t m_numberOfThreads;
    std::string m_address;
    unsigned short m_port;
};

}

#include "linkoptions.h"

#endif
