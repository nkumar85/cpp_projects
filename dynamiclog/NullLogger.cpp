#include "NullLogger.hpp"

void NullLogger::logCritical(const std::string& format, ...) const
{
}

void NullLogger::logError(const std::string& format, ...) const
{
}

void NullLogger::logWarning(const std::string& format, ...) const
{
}

void NullLogger::logInfo(const std::string& format, ...) const
{
}

void NullLogger::logDebug(const std::string& format, ...) const
{
}
