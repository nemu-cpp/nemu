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

#ifndef _NEMUFRAMEWORK_NEMU_SERVERS_H_
#define _NEMUFRAMEWORK_NEMU_SERVERS_H_

#include "Server.h"
#include <vector>
#include <memory>

namespace Nemu
{

/// A list of servers.
/**
    This class is used by the Application class to store its list of servers. There should usually be no need to create
    an instance of this class yourself.
*/
class Servers
{
public:
    /// Starts all the servers in the list.
    /**
        This function doesn't block and returns immediately. It simply calls Server::start on each server in the list.
    */
    void startAll();
    /// Stops all the servers in the list.
    /**
        This function simply calls Server::stop on each server in the list.
    */
    void stopAll();
    /// Wait until all servers in the list have stopped.
    /**
        This function simply calls Server::join on each server in the list.
    */
    void joinAll();

    /// Appends a server to the list.
    /**
        @param server The server to add to the list.
    */
    void append(std::shared_ptr<Server> server);

    /// Returns the number of servers that have been stated and are running.
    size_t numberOfRunningServers() const;

private:
    std::vector<std::shared_ptr<Server>> m_servers;
};

}

#include "linkoptions.h"

#endif
