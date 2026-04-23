module FInput;

/* INPUT KEY */
InputKey::InputKey(int k) : id{k}
{
    
}

auto InputKey::getFunctions() -> std::vector<Functionoid*>&
{
    return functions;
}

void InputKey::addFunc(Functionoid* func)
{
    if (!func)
        return;
    if (std::find(functions.begin(), functions.end(), func) == functions.end())
    {
        func->addKey(id);
        functions.push_back(func);
    }
}


void InputKey::removeFunc(Functionoid* func)
{
    if (!func)
        return;
    if (auto iter{std::find(functions.begin(), functions.end(), func)}; iter != functions.end())
    {
        func->removeKey(id);
        *iter = nullptr;
    }
	functions.erase(std::remove(std::begin(functions), std::end(functions), nullptr), std::end(functions));
}


void InputKey::callFuncs()
{
    for (auto f : functions)
    {
        if (f)
            f->call();
    }
}

void InputKey::setState(bool s)
{
    state = s;
    for (auto f : functions)
    {
        f->setState(id, state);
    }
}


/* INPUT MANAGER */
InputManager InputManager::manager{};

InputManager::InputManager()
{
    for (auto i : fg::keyArray)
        keys.push_back(std::make_unique<InputKey>(i));
    
}

InputManager::~InputManager()
{
   
}


auto InputManager::getInput() -> InputManager&
{
    return manager;
}

auto InputManager::getKeys() -> std::vector<std::unique_ptr<InputKey>>&
{
    return keys;
}

auto InputManager::findKey(int id) -> InputKey*
{
    for (auto& k : keys)
    {
        if (k.get() && k.get()->id == id)
            return k.get();
    }
    return nullptr;
}

void InputManager::addKeyFunc(int keyid, Functionoid* func)
{
    if (auto k{findKey(keyid)}; k)
    {
        k->addFunc(func);
    }
}

void InputManager::removeKeyFunc(int keyid, Functionoid* func)
{
    if (auto k{findKey(keyid)}; k)
    {
        k->removeFunc(func);
    }
}

void InputManager::switchKeyFunc(int fromkey, int tokey, Functionoid* func)
{

    if (auto from{findKey(fromkey)}; from)
    {
        if (auto to{findKey(tokey)}; to)
        {
            from->removeFunc(func);
            to->addFunc(func);
        }
    }
}

void InputManager::addMultiKeyFunc(std::vector<int> keyids, Functionoid* func)
{
    if (!func)
        return;

    for (auto k : keyids)
	{
		addKeyFunc(k, func);
	}
}

void InputManager::removeMultiKeyFunc(std::vector<int> keysid, Functionoid* func)
{
    if (!func)
        return;

    for (auto k : keysid)
	{
		removeKeyFunc(k, func);
	}
}

void InputManager::switchMultiKeyFunc(std::vector<int> fromkeys, std::vector<int> tokeys, Functionoid* func)
{
    if (!func)
        return;

    removeMultiKeyFunc(fromkeys, func);
    addMultiKeyFunc(tokeys, func);
}

 void InputManager::callKey(int keyA)
{

    if (auto k{findKey(keyA)}; k)
    {
        k->callFuncs();
    }
}


