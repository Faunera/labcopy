export module FInput;
import std;
import Fglfw;
import FFunctionoid;
import FError;

export
{
    class InputKey
    {
    public:
        InputKey(int k);
    
        auto getFunctions() -> std::vector<Functionoid*>&;

        // Add func
        void addFunc(Functionoid* func);
        // Remove func
        void removeFunc(Functionoid* func);

        // Call funcs
        void callFuncs();

        void setState(bool s);

        bool state{false};
        const int id;
    private:
        std::vector<Functionoid*> functions{};
    };

    class InputManager
    {
    public:
        static auto getInput() -> InputManager&;
        auto getKeys() -> std::vector<std::unique_ptr<InputKey>>&;

        // Get key for public use
        auto findKey(int id) -> InputKey*;

        // Adds the function to given key
        void addKeyFunc(int keyid, Functionoid* func);

        // Removes function from given key
        void removeKeyFunc(int keyid, Functionoid* func);

        // Switches function from key BY removing it from FROMKEY and adding it to TOKEY
        void switchKeyFunc(int fromkey, int tokey, Functionoid* func);

        // Add function for key combination
        void addMultiKeyFunc(std::vector<int> keyids, Functionoid* func);

        // Remove function from key combination
        void removeMultiKeyFunc(std::vector<int> keysid, Functionoid* func);

        // Switch function to differenet key combination
        void switchMultiKeyFunc(std::vector<int> fromkeys, std::vector<int> tokeys, Functionoid* func);

        // Calls key's functions
        void callKey(int keyA);

    private:
        InputManager();
        ~InputManager();    

        static InputManager manager;
        std::vector<std::unique_ptr<InputKey>> keys{};
    };
}
