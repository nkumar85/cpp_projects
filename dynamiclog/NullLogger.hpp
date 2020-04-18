#ifndef __NULL_LOGGER_HPP_
#define __NULL_LOGGER_HPP_

#include <string>

#include "ILogger.hpp"

class NullLogger : public ILogger
{
    public:
        virtual void logCritical(const std::string& format, ...) const override final;
        virtual void logError(const std::string& format, ...) const override final;
        virtual void logWarning(const std::string& format, ...) const override final;
        virtual void logInfo(const std::string& format, ...) const override final;
        virtual void logDebug(const std::string& format, ...) const override final;
};

#endif
