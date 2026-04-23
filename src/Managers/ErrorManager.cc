export module FError;
import std;
import FTimer;
import FUtility;

export
{
    // Singleton class to log events to a file
    class ErrorManager
    {
    public:
        static auto getManager() -> ErrorManager&;

        void logEvent(const std::string& msg);

        std::string errorFile{"./errorlog.txt"};
        Timer errorTime{};
    private:
        ErrorManager();
        ~ErrorManager(){}
        static ErrorManager manager;
    };
}

