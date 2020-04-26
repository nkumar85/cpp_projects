#include <stdio.h>
#include <stdarg.h>
#include <syslog.h>

#include <string>
#include <iostream>
#include <memory>

#include "LoggerTypes.hpp"
#include "ILogger.hpp"
#include "NullLogger.hpp"
#include "SystemLogger.hpp"
#include "DynamicLogger.hpp"

void log_syslog(int type, const char* format, ...)
{
    va_list args;
    va_start (args, format);
    vsyslog(type, format, args);
    va_end (args);
}

template<class... Args>
void logCustom(int type, const std::string& format, Args&&... args)
{
    log_syslog(type, format.c_str(), std::forward<Args>(args)...);
}

int main()
{
//    logCustom(LOG_EMERG, "%s : %u\n", "Nandaa", 100);

    std::shared_ptr<SystemLogger> sysLogger = std::make_shared<SystemLogger>();
    DynamicLogger dLogger;
    dLogger.set(LogLevelError, sysLogger);
    dLogger.set(LogLevelDebug, sysLogger);
    dLogger.set(LogLevelInfo, sysLogger);

    dLogger.logDebug("%s - %d\n", "Debug", 10);
    dLogger.logError("%s - %d\n", "Error", 20);
    dLogger.logInfo("%s - %d\n", "Info", 20);
}
