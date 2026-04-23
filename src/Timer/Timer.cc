export module FTimer;
import std;
import FAlias;

export
{
    class Timer
    {
    public:
        constexpr auto elapsed() const -> time::Duration_ms
        {
            return { time::SteadyClock::now() - clock };
        }
        void reset()
        {
            clock = time::SteadyClock::now();
        }

        // Returns elapsed time count in hh mm ss
        void print()
        {
            // Convert elapsed time to different durations
            auto t{elapsed()};
            std::chrono::duration<double, std::ratio<3600>> h{t};
            std::chrono::duration<double, std::ratio<60>> min{t};
            std::chrono::duration<double, std::ratio<1>> sec{t};
            
            // Print out the time in HH MM SS format, if duration is long enough
            // for full HH or MM
            if (h.count() >= 1.0)
                std::cout << h << ":";
            if (min.count() >= 1.0)
                std::cout << min << ":";
            std::cout << sec <<  "\n";
            //std::cout << elapsed().count() << " ms\n";
        }
    private:
        time::SteadyPoint clock{time::SteadyClock::now()};
    };
}
