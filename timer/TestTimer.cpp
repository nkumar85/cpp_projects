#include <signal.h>
#include <time.h>
#include <unistd.h>

#include <functional>
#include <iostream>
#include <chrono>
#include <thread>

#include "Timer.hpp"

using namespace std::placeholders;

TimerConfiguration timerConfig = {std::chrono::seconds(3), std::chrono::nanoseconds(0), TimerFrequency::Periodic};
TimerConfiguration newTimerConfig = {std::chrono::seconds(6), std::chrono::nanoseconds(0), TimerFrequency::Once};

class TestTimer
{
    public:
        TestTimer() : ti_( [this](int i,int j)
                        {
                            timerCallbackClass(i);
                        } )
        {
        }

        void timerCallbackClass(int k)
        { 
           std::cout << "Class Timer expired : " << k << "\n";
        }

        void triggerStartTimer()
        {
            ti_.create(timerConfig,5,6);
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
        Timer<std::function<void(int,int)>,int,int> ti_;
        int context_ = 200;
};

void timerCallbackFunc(int* k)
{
    std::cout << "Timer callback function : " << *k << "\n";
}

auto timerCallbackLambda = [](int *k)
                           {
                               std::cout << "Timer callback lambda : " << *k << "\n";
                           };

int main()
{
    std::cout<<"main thread tid is "<<std::this_thread::get_id()<<std::endl;
    /* Non-class function usage */
    /* ------------------------ */
//    int contextFunc = 10;
//    Timer<std::function<void(int*)>, int*> timFunc(std::bind(timerCallbackFunc, _1));
//    timFunc.create(&contextFunc, timerConfig);
//    timFunc.start();
//
//    sleep(6);
//
//    timFunc.stop();

    /* Lambda based usage */
    /* ------------------ */
//    int contextLambda = 20;
//    Timer<decltype(timerCallbackLambda), int*> timLambda(timerCallbackLambda);
//    timLambda.create(&contextLambda, timerConfig);
//    timLambda.start();
//
//    sleep(6);
//
//    timLambda.stop();

    /* Class based usage */
    /* ----------------- */
    TestTimer t_timer;
    t_timer.triggerStartTimer();
    sleep(10);
/*
    t_timer.triggerResetTimer();
    sleep(10);

    t_timer.triggerStopTimer();
    sleep(10); */
}
