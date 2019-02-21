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

#ifndef _NEMUFRAMEWORK_NEMU_CORE_APPLICATIONS_H_
#define _NEMUFRAMEWORK_NEMU_CORE_APPLICATIONS_H_

#include "Application.h"
#include <set>
#include <mutex>

namespace Nemu
{

/// The list of applications in the program.
/**
    This class behaves as a singleton that stores the list of Application instances in the program. The constructors
    and destructor of the Application class automatically add and remove instances to this class.
    
    On Windows, it is used by the Ctrl-C handler to stop all applications when a Ctrl-C event is received. But it can
    be used for other purposes if needed.
*/
class Applications
{
public:
    /// Stops all applications in the list.
    static void StopAllApplications();

    /// Adds an application to the list.
    /**
        This function is automatically called by the Application constructors so there should be no need to call it
        directly.
        @param application The application to add to the list.
    */
    static void set(Application* application);
    // Removes an application from the list.
    /**
        This function is automatically called by the Application destructor so there should be no need to call it
        directly.
        @param application The application to remove from the list.
    */
    static void unset(Application* application);

private:
    static std::mutex sm_applicationsMutex;
    static std::set<Application*> sm_applications;
};

}

#include "linkoptions.h"

#endif
