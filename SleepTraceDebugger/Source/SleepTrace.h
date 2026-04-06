#pragma once

#include <functional>
#include <string>
#include <sstream>

namespace SleepTrace
{
    enum class LogType
    {
        Trace, // "tracing" the code and trying to find one part of a function specifically.
        Debug, // Information that is diagnostically helpful to people more than just developers
        Info, // Generally useful information to log (service start/stop, configuration assumptions, etc).
        Warn, // Anything that can potentially cause application oddities, but is automatically being recovered from. (switching from a primary to backup server, retrying an operation, missing secondary data, etc.)
        Error, // Any error which is fatal to the operation, but not the service or application (can't open a required file, missing data, etc.)
        Fatal // Any error that is forcing a shutdown of the service or application to prevent data loss (or further data loss).
    };

    class Log
    {
    public:
        static void SetCallback(std::function<void(LogType, const char*, int, const std::string&)> callback) { m_callback = callback; };

        template<typename... Args>
        static void Print(LogType logType, const char* file, int line, Args&&... args) 
        { 
            if(m_callback) 
            {
                std::ostringstream ss;
                (ss << ... << std::forward<Args>(args));
                m_callback(logType, file, line, ss.str()); 
            } 

            if(logType == LogType::Fatal)
            {
                abort();
            }
        };

    private:
        inline static std::function<void(LogType, const char*, int, const std::string&)> m_callback = nullptr;
    };

    #define LOG_TRACE(...) SleepTrace::Log::Print(SleepTrace::LogType::Trace, __FILE__, __LINE__, __VA_ARGS__)
    #define LOG_DEBUG(...) SleepTrace::Log::Print(SleepTrace::LogType::Debug, __FILE__, __LINE__, __VA_ARGS__)
    #define LOG_INFO(...) SleepTrace::Log::Print(SleepTrace::LogType::Info, __FILE__, __LINE__, __VA_ARGS__)
    #define LOG_WARN(...) SleepTrace::Log::Print(SleepTrace::LogType::Warn, __FILE__, __LINE__, __VA_ARGS__)
    #define LOG_ERROR(...) SleepTrace::Log::Print(SleepTrace::LogType::Error, __FILE__, __LINE__, __VA_ARGS__)
    #define LOG_FATAL(...) SleepTrace::Log::Print(SleepTrace::LogType::Fatal, __FILE__, __LINE__, __VA_ARGS__)
}