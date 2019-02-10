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

#include "ControlHandlerRegistration.h"

#ifdef _WIN32
#include "Application.h"
#include <windows.h>

namespace Nemu
{

std::atomic<size_t> ControlHandlerRegistration::sm_count = 0;

BOOL WINAPI ControlHandler(DWORD fdwCtrlType)
{
    switch (fdwCtrlType)
    {
    case CTRL_C_EVENT:
        Application::StopAllApplications();
        return TRUE;

    default:
        return FALSE;
    }
}

ControlHandlerRegistration::ControlHandlerRegistration()
{
    ++sm_count;
    if (sm_count == 1)
    {
        SetConsoleCtrlHandler(ControlHandler, TRUE);
    }
}

ControlHandlerRegistration::~ControlHandlerRegistration()
{
    --sm_count;
    if (sm_count == 0)
    {
        SetConsoleCtrlHandler(ControlHandler, FALSE);
    }
}

}

#endif
