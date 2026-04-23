export module FAlias;
import std;

export namespace time
{
    using SteadyClock = std::chrono::steady_clock;
    using SteadyPoint = std::chrono::time_point<SteadyClock>;
    using Duration_ms = std::chrono::duration<double, std::milli>;

}

export
{
    using int32 = std::int_least32_t;

    using uint8 = std::int_least8_t;

    using Vecf = std::vector<float>;
    using Vecd = std::vector<double>;
    using Veci = std::vector<int>;
    
    // Resource Type
    enum class RType
    {
        Null,
        Graphic,
        Movie,
        Audio,
        Text,
    };
}

export namespace ids
{
    int32 auid{0}; // Actor unique id
    int32 pcuid{0}; // Physicscomponent unique id
    //int32 ruid{0}; // Resource unique id
}

