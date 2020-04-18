#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__

class ILogger
{
public:
    virtual void logCritical(const std::string& format, ...) const = 0;
    virtual void logError(const std::string& format, ...) const = 0;
    virtual void logWarning(const std::string& format, ...) const = 0;
    virtual void logInfo(const std::string& format, ...) const = 0;
    virtual void logDebug(const std::string& format, ...) const = 0;
};

#endif
