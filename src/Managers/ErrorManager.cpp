module FError;

ErrorManager ErrorManager::manager{};

ErrorManager::ErrorManager()
{
    // Clear errorfile
    rewriteFile(errorFile, "");
}

auto ErrorManager::getManager() -> ErrorManager&
{
    return manager;
}

void ErrorManager::logEvent(const std::string& msg)
{
    std::stringstream buffer{};
    buffer << errorTime.elapsed().count() << " ms: " << msg;
    writeFile(errorFile, buffer.str());
    std::cout << buffer.str() << "\n";
}
