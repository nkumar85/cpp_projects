#include <signal.h>
#include <time.h>
#include <unistd.h>

#include <functional>
#include <iostream>
#include <chrono>
#include <thread>

#include "Timer.hpp"

namespace {
template<typename... Args>
using Callback = std::function<void(Args... args)>;    
TimerConfiguration timerConfig = {std::chrono::seconds(3), std::chrono::nanoseconds(0), TimerFrequency::Periodic};
TimerConfiguration newTimerConfig = {std::chrono::seconds(6), std::chrono::nanoseconds(0), TimerFrequency::Once};
}

template<typename... Args>
class TestTimer
{
    public:
        TestTimer() : ti_( [this](Args&&... args)
                            {
                            timerCallbackClass(std::forward<Args>(args)...);
                            } 
                        )
        {
        }

        void timerCallbackClass(Args&&... i)
        {
           std::cout << "Class Timer expired : "  << "\n";
        }

        void triggerStartTimer()
        {
            ti_.create(timerConfig,5);
            ti_.start();
        }

        void triggerResetTimer()
        {
            ti_.reset(newTimerConfig);
        }
        void triggerStopTimer()
        {
            ti_.stop();
        }

    private:
        Timer<Callback<Args...>,Args...> ti_;
};


int main()
{
    TestTimer<int> t_timer;
    t_timer.triggerStartTimer();
    sleep(10);

    t_timer.triggerResetTimer();
    sleep(10);

    t_timer.triggerStopTimer();
    sleep(10);
}
