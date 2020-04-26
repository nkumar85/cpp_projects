#ifndef __SYSTEM_LOGGER_HPP__
#define __SYSTEM_LOGGER_HPP__

#include <string>

#include "ILogger.hpp"

class SystemLogger : public ILogger
{
    public:
        virtual void logCritical(const std::string& format, ...) const override final;
        virtual void logError(const std::string& format, ...) const override final;
        virtual void logWarning(const std::string& format, ...) const override final;
        virtual void logInfo(const std::string& format, ...) const override final;
        virtual void logDebug(const std::string& format, ...) const override final;
};

#endif
