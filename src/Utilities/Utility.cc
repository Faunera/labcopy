export module FUtility;
import std;
import FAlias;

export
{
    bool floatCompare(auto f1, auto f2)
    {
        static constexpr auto epsilon = 10.e-05;
        if (std::fabs(f1 - f2) <= epsilon)
            return true;
        return std::fabs(f1 - f2) <= epsilon * std::max(std::fabs(f1), std::fabs(f2));
    }

    template<typename Signed>
    constexpr std::size_t toUZ(Signed value)
    {
        // Make sure Signed is integral type or return 0
        if (!(std::is_integral<Signed>() || std::is_enum<Signed>()))
            return 0;
        return static_cast<std::size_t>(value);
    }
    
    // Read file content into char vector
    auto readFile(const std::string& filename) -> std::vector<char>;

    // Write to end of file
    void writeFile(const std::string& filename, const std::string& content);

    // Remove old content of file and write to it
    void rewriteFile(const std::string& filename, const std::string& content);


    /* BYTE STUFF */
    std::ostream& operator<<(std::ostream& os, std::byte b);

}
