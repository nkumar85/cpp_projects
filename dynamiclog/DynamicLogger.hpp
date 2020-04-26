#ifndef __DYNAMIC_LOGGER_HPP__
#define __DYNAMIC_LOGGER_HPP__

#include <string>
#include <array>
#include <memory>

#include "LoggerTypes.hpp"

class DynamicLogger
{
    public:
        template<class... Args>
        void logCritical(const std::string& format, Args... args)
        {
            loggerMap_[LogLevelCritical]->logCritical(format.c_str(), std::forward<Args>(args)...);
        }

        template<class... Args>
        void logError(const std::string& format, Args... args)
        {
            loggerMap_[LogLevelError]->logError(format.c_str(), std::forward<Args>(args)...);
        }

        template<class... Args>
        void logWarning(const std::string& format, Args... args)
        {
            loggerMap_[LogLevelWarning]->logWarning(format.c_str(), std::forward<Args>(args)...);
        }

        template<class... Args>
        void logInfo(const std::string& format, Args... args)
        {
            loggerMap_[LogLevelInfo]->logInfo(format.c_str(), std::forward<Args>(args)...);
        }

        template<class... Args>
        void logDebug(const std::string& format, Args... args)
        {
            loggerMap_[LogLevelDebug]->logDebug(format.c_str(), std::forward<Args>(args)...);
        }

        DynamicLogger();
        bool setAll(const std::shared_ptr<ILogger>& logger);
        bool set(std::uint8_t logLevel, const std::shared_ptr<ILogger>& logger);
        bool set(LogLevelMask, const std::shared_ptr<ILogger>& logger);

    private:
        void initLoggerInstances(const std::shared_ptr<ILogger>& logger);
        std::array<std::shared_ptr<ILogger>, LogLevelEnd> loggerMap_;
};

#endif
