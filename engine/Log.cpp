#include "Engine.h"

#include <chrono>
#include <cstdarg>
#include <cstdio>
#include <ctime>
#include <mutex>

namespace Log
{

enum class Level : int
{
    Debug = 0,
    Info = 1,
    Warn = 2,
    Error = 3
};

static std::mutex g_logMutex;

static const char *levelToString(Level level_)
{
    switch (level_)
    {
    case Level::Debug:
        return "DEBUG";
    case Level::Info:
        return "INFO ";
    case Level::Warn:
        return "WARN ";
    case Level::Error:
        return "ERROR";
    default:
        return "     ";
    }
}

static void logInternal(Level level_, const char *fmt_, va_list args_)
{
    using namespace std::chrono;
    auto now = system_clock::now();
    auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;
    auto timer = system_clock::to_time_t(now);

    std::tm tm_info;
#ifdef _WIN32
    localtime_s(&tm_info, &timer);
#else
    localtime_r(&timer, &tm_info);
#endif

    char msg[4096];
    int msgLen = vsnprintf(msg, sizeof(msg), fmt_, args_);
    if (msgLen < 0 || msgLen >= static_cast<int>(sizeof(msg)))
    {
        msg[sizeof(msg) - 1] = '\0';
    }

    std::lock_guard<std::mutex> lock(g_logMutex);
    std::printf("[%04d-%02d-%02d %02d:%02d:%02d.%03d][%s] %s\n", tm_info.tm_year + 1900, tm_info.tm_mon + 1, tm_info.tm_mday, tm_info.tm_hour, tm_info.tm_min, tm_info.tm_sec,
                static_cast<int>(ms.count()), levelToString(level_), msg);
}

void debug(const char *fmt_, ...)
{
    va_list args;
    va_start(args, fmt_);
    logInternal(Level::Debug, fmt_, args);
    va_end(args);
}

void info(const char *fmt_, ...)
{
    va_list args;
    va_start(args, fmt_);
    logInternal(Level::Info, fmt_, args);
    va_end(args);
}

void warn(const char *fmt_, ...)
{
    va_list args;
    va_start(args, fmt_);
    logInternal(Level::Warn, fmt_, args);
    va_end(args);
}

void error(const char *fmt_, ...)
{
    va_list args;
    va_start(args, fmt_);
    logInternal(Level::Error, fmt_, args);
    va_end(args);
}

} // namespace Log