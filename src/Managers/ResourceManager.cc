export module FResourceManager;
import std;
import FResource;
import FUtility;
import FAlias;
import FError;
import FRenderer;
import "tinyxml2.h";

export
{

    // ResourceManager handles the loading and unloading of assets
    class ResourceManager
    {
    public:
        static auto getManager() -> ResourceManager&;
        // Returns map of resources
        auto getResources() -> std::map<int, std::vector<std::unique_ptr<Resource>>>&;
        // Returns resource ptr with given id, or nullptr if unsuccessful
        auto findResourceByID(int id) -> Resource*;
        // Clears resources and scopes
        void clear();

        // Load resources from given XML file. Window is the renderer you wish to load graphical resources into
        bool loadFromXML(const std::string& fileName, Renderer* window = nullptr);

        void setScope(int scope);

    private:
        ResourceManager(){}
        ~ResourceManager(){}

        static ResourceManager manager;

        int resourceCount{0}; // Total number of resources, both loaded and unloaded
        
        // Map<Scope, resources>
        // Each scope contains vector of resources for that scope
        std::map<int, std::vector<std::unique_ptr<Resource>>> resources;
    };
}
