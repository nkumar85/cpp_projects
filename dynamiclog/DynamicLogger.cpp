#include "NullLogger.hpp"

#include "DynamicLogger.hpp"

DynamicLogger::DynamicLogger()
{
     initLoggerInstances(std::make_shared<NullLogger>());
}

void DynamicLogger::initLoggerInstances(const std::shared_ptr<ILogger>& logger)
{
    std::shared_ptr<ILogger> defaultLogger(logger);
    for (std::uint8_t logLevelIter = LogLevelBegin; logLevelIter < LogLevelEnd; ++logLevelIter)
    {
        loggerMap_[logLevelIter] = defaultLogger;
    }
}

bool DynamicLogger::setAll(const std::shared_ptr<ILogger>& logger)
{
    if (logger)
    {
        initLoggerInstances(logger);
    }

   return not(nullptr == logger.get());
}

bool DynamicLogger::set(std::uint8_t logLevel, const std::shared_ptr<ILogger>& logger)
{
    bool retVal = ((logLevel < LogLevelEnd) && logger);

    if (retVal)
    {
        loggerMap_[logLevel] = logger;
    }

    return retVal;
}
