module FResourceManager;

ResourceManager ResourceManager::manager{};

auto ResourceManager::getManager() -> ResourceManager&
{
    return manager;
}


auto ResourceManager::getResources() -> std::map<int, std::vector<std::unique_ptr<Resource>>>&
{
    return resources;
}

auto ResourceManager::findResourceByID(int id) -> Resource*
{
    for (auto& [key, value] : resources)
    {
        auto it{std::ranges::find(value, id, &Resource::uid)};
        if(it != value.end())
            return it->get();
    }

    return nullptr;
}

void ResourceManager::clear()
{
    resources.clear();
}

bool ResourceManager::loadFromXML(const std::string& fileName, Renderer* window)
{
    using namespace tinyxml2;
    auto& error{ErrorManager::getManager()};

    // Load XML document
    XMLDocument doc{};

    if (doc.LoadFile(fileName.c_str()) != XML_SUCCESS)
    {
        error.logEvent("Failed to load file: " + fileName);
        return false;
    }
    
    // Create node from element: resources 
    XMLNode* tree{doc.FirstChildElement("resources")};
    if (!tree)
    {
        error.logEvent("Failed to create XMLNode");
        return false;
    }

    // Loop through children to create new resources
    for (XMLNode* child{tree->FirstChild()}; child; child = child->NextSibling())
    {
        XMLElement* element{child->ToElement()};
        if (!element)
        {
            error.logEvent("Failed to convert XMLNode to element");
            continue;
        }

        std::unique_ptr<Resource> res{};
        // Initialize resource values using element attribute values
        for (auto attribute{element->FirstAttribute()}; attribute; attribute = attribute->Next())
        {
            std::string name{attribute->Name()};
            std::string value{attribute->Value()};

            // Find resource type and load them using the correct managers
            if (name == "type")
            {
                if (value == "graphic")
                {
                    //res = std::make_unique<TR>();
                    // Resource = Renderer.loadFromXML(Element);
                    if (window)
                    {

                    }
                }
                else if (value == "audio")
                {

                }
                else if (value == "text")
                {

                }
            }

            if (res)
            {

                if (name == "uid")
                {
                    res->uid = atoi(value.c_str());
                }
                else if (name == "filename")
                {
                    res->filename = value;
                }
                else if (name == "scenescope")
                {
                    res->scope = atoi(value.c_str());
                }
            }
        }

        if (res)
        {
            // Check if a resource has unique id
            bool exists{false};
            for (auto& [key, value] : resources)
            {
                auto it{std::ranges::find(value, res->uid, &Resource::uid)};
                if(it != value.end())
                {
                    exists = true;
                    break;
                }
            }
            if (exists)
            {
                error.logEvent("Resource with same UID already exists");
                continue;
            }

            // Move the resource to map of resources
            resources.insert(std::make_pair(res->scope, std::vector<std::unique_ptr<Resource>>()));
            for (auto& pair : manager.getResources())
            {
                if (pair.first == res->scope)
                {
                    pair.second.push_back(std::move(res));
                    break;
                }
            }
        }
    }

    return true;
}

void ResourceManager::setScope(int scope)
{

}
