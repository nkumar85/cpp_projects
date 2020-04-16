#ifndef TIMER_HPP_
#define TIMER_HPP_

#include <signal.h>
#include <time.h>

#include <functional>
#include <iostream>
#include <chrono>

using TimeInSec  = std::chrono::seconds;
using TimeInNSec = std::chrono::nanoseconds;

enum class TimerFrequency
{
    Once,
    Periodic
};

struct TimerConfiguration
{
    TimeInSec      timeInSec  = std::chrono::seconds(0);
    TimeInNSec     timeInNSec = std::chrono::nanoseconds(0);
    TimerFrequency tFreq = TimerFrequency::Once;
};

template<typename Callback, typename Context>
class Timer
{
    public:
        explicit Timer(Callback cbFunc);
        bool create(Context ctx, const TimerConfiguration&);
        bool start();
        bool stop();
        bool reset(const TimerConfiguration&);
        ~Timer();

    private:
        void timerExpired() const;
        static void syscallTimerExpiryFunction(union sigval sval);
        bool setTime(const struct itimerspec&) const;
        void destroy();
        Callback callback_;
        Context ctx_;
        timer_t tid_;
        TimerConfiguration timerConfig_;
};

template<typename Callback, typename Context>
Timer<Callback, Context>::Timer(Callback cbFunc) : callback_(cbFunc)
{
}

template<typename Callback, typename Context>
Timer<Callback, Context>::~Timer()
{
    destroy();
}

template<typename Callback, typename Context>
bool Timer<Callback, Context>::create(Context ctx, const TimerConfiguration& timerConfig)
{
    ctx_ = ctx;
    timerConfig_ = timerConfig;

    struct sigevent s_event = {0};
    union sigval si_val = {0};

    si_val.sival_ptr = this;
    s_event.sigev_notify = SIGEV_THREAD;
    s_event.sigev_value = si_val;
    s_event.sigev_notify_function = &Timer<Callback, Context>::syscallTimerExpiryFunction;
    int retVal = timer_create(CLOCK_MONOTONIC, &s_event, &tid_);

    return (0 == retVal);
}

template<typename Callback, typename Context>
bool Timer<Callback, Context>::start()
{
    struct itimerspec timerVal = {{0, 0}, {timerConfig_.timeInSec.count(), timerConfig_.timeInNSec.count()}};

    if (TimerFrequency::Periodic == timerConfig_.tFreq)
    {
       timerVal.it_interval.tv_sec = timerConfig_.timeInSec.count(); 
       timerVal.it_interval.tv_nsec = timerConfig_.timeInNSec.count(); 
    }

    return setTime(timerVal);
}

template<typename Callback, typename Context>
bool Timer<Callback, Context>::stop()
{
    struct itimerspec stopTimerVal = {{0, 0}, {0, 0}};
    return setTime(stopTimerVal);
}

template<typename Callback, typename Context>
bool Timer<Callback, Context>::reset(const TimerConfiguration& newTimerVal)
{
    stop();
    timerConfig_ = newTimerVal;
    return start();
}

template<typename Callback, typename Context>
void Timer<Callback, Context>::destroy()
{
    stop();
    timer_delete(tid_);
}

template<typename Callback, typename Context>
void Timer<Callback, Context>::timerExpired() const
{
    callback_(ctx_);
}

template<typename Callback, typename Context>
void Timer<Callback, Context>::syscallTimerExpiryFunction(union sigval sval)
{
    const Timer *timerCtx = reinterpret_cast<const Timer*>(sval.sival_ptr);
    timerCtx->timerExpired();
}

template<typename Callback, typename Context>
bool Timer<Callback, Context>::setTime(const struct itimerspec& timerVal) const
{
    return (0 == timer_settime(tid_, 0, &timerVal, NULL));
}

#endif
