#ifndef __LOGGERTYPES_HPP__
#define __LOGGERTYPES_HPP__

#include <cstdint>
#include <bitset>

constexpr std::uint8_t LogLevelBegin    = 0x00;
constexpr std::uint8_t LogLevelCritical = LogLevelBegin;
constexpr std::uint8_t LogLevelError    = LogLevelCritical + 1;
constexpr std::uint8_t LogLevelWarning  = LogLevelError + 1;
constexpr std::uint8_t LogLevelInfo     = LogLevelWarning + 1;
constexpr std::uint8_t LogLevelDebug    = LogLevelInfo + 1;
constexpr std::uint8_t LogLevelEnd      = LogLevelDebug + 1;

using LogLevelMask = std::bitset<LogLevelEnd>;

#endif
