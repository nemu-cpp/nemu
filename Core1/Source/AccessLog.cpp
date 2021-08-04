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

#include "AccessLog.h"
#include <g3log/g3log.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace Nemu
{

void AccessLog::log(const std::string& address, const std::string& requestLine, unsigned int statusCode, size_t size)
{
    boost::posix_time::ptime currentTime = boost::posix_time::second_clock::universal_time();
    const auto& date = currentTime.date();
    const auto& time = currentTime.time_of_day();
    LOG(INFO) << address << " - - [" << date.day() << "/" << date.month().as_short_string() << "/" << date.year()
        << ":" << time.hours() << ":" << time.minutes() << ":" << time.seconds() << " " << currentTime.zone_name(true)
        << "] \"" << requestLine << "\" " << statusCode << " " << size;
}

}
