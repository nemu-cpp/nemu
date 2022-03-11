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

#include "NemuFramework/Nemu/Core/Configuration.h"
#include "NemuFramework/Nemu/Core/Log.h"
#include "NemuFramework/Nemu/Core/WebApplication.h"
#include <iostream>

int main(int argc, char* argv[])
{
    Ishiko::Error error(0);

    // Create the configuration based on the command line arguments.
    Nemu::Configuration configuration(argc, argv);

    // Create a log that sends its output to the console.
    std::shared_ptr<Nemu::Log> log = std::make_shared<Nemu::Log>("NemuHelloWorldServer", Nemu::Log::eConsole);

    Nemu::WebApplication app(configuration, log, error);
    if (error)
    {
        std::cout << "Error: " << error.code() << std::endl;
    }

    return error.code();
}
