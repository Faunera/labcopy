module FFunctionoid;

Functionoid::~Functionoid()
{

}

void Functionoid::call()
{
    for (const auto& k : keys)
    {
        if (!k.second)
            return;
    }
    custom();
}

void Functionoid::custom()
{

}

void Functionoid::addKey(int k)
{
    // Return if we're trying to add existing key
    for (auto& key : keys)
    {
        if (key.first == k)
            return;
    }
    keys.insert({ k, false });
}

void Functionoid::removeKey(int k)
{
    std::erase_if(keys, [&](auto& kv)
    {
        const auto& [key, value] {kv};
        return key == k; 
    });
}

void Functionoid::setState(int k, bool pressed)
{
    for (auto& key : keys)
    {
        if (key.first == k)
            key.second = pressed;
    }
}
