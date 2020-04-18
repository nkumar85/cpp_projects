#include <stdarg.h>
#include <syslog.h>

#include "SystemLogger.hpp"

void SystemLogger::logCritical(const std::string& format, ...) const
{
    va_list args;
    va_start (args, format);
    vsyslog(LOG_CRIT, format.c_str(), args);
    va_end (args);
}

void SystemLogger::logError(const std::string& format, ...) const
{
    va_list args;
    va_start (args, format);
    vsyslog(LOG_ERR, format.c_str(), args);
    va_end (args);
}

void SystemLogger::logWarning(const std::string& format, ...) const
{
    va_list args;
    va_start (args, format);
    vsyslog(LOG_WARNING, format.c_str(), args);
    va_end (args);
}

void SystemLogger::logInfo(const std::string& format, ...) const
{
    va_list args;
    va_start (args, format);
    vsyslog(LOG_INFO, format.c_str(), args);
    va_end (args);
}

void SystemLogger::logDebug(const std::string& format, ...) const
{
    va_list args;
    va_start (args, format);
    vsyslog(LOG_DEBUG, format.c_str(), args);
    va_end (args);
}
