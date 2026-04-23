module FObjectManager;
 
ObjectManager ObjectManager::manager{};

ObjectManager::ObjectManager()
{

}

ObjectManager::~ObjectManager()
{
    clearObjects();
}

auto ObjectManager::getManager() -> ObjectManager&
{
    return manager;
}

auto ObjectManager::getObjects() -> std::vector<std::unique_ptr<GameObject>>&
{
    return objects;
}

void ObjectManager::clearObjects()
{ 
    for (auto& o : objects)
    {
        removeFromRenderers(*o);
    }
    objects.clear();
}

auto ObjectManager::findObject(int id) -> GameObject*
{
    auto it {std::ranges::find(objects, id, &GameObject::id)};
    if (it != objects.end())
        return it->get();
    else
        return nullptr;
}

void ObjectManager::removeObjectById(int id)
{
    auto obj{findObject(id)};
    removeObject(obj);
}

void ObjectManager::removeObject(GameObject* go)
{
    // Return if parameter is not valid
    if(!go)
        return;

    for (auto& o : objects)
    {
        if (o.get() == go)
        {
            // Cleanup
            removeFromRenderers(*go);
            
            // Reset pointer after cleanup is done
            o.reset();
        }
    }

	objects.erase(std::remove(std::begin(objects), std::end(objects), nullptr), std::end(objects));
}

void ObjectManager::addToRendererAll(Renderer& ren)
{
    for (auto& o : objects)
    {
        addToRenderer(ren, *o);
    }
}

void ObjectManager::addToRenderer(Renderer& ren, GameObject& go)
{
    // Add new renderer to references
    if (std::find(renderers.begin(), renderers.end(), &ren) == renderers.end())
        renderers.push_back(&ren);
    ren.addToRenderer(go.getSprite());
}

void ObjectManager::removeFromRenderers(GameObject& go)
{
    for (auto& r : renderers)
    {
        r->removeFromRenderer(go.getSprite());
    }

}

void ObjectManager::removeRendererRef(Renderer& ren)
{
    for (auto& o : objects)
    {
        ren.removeFromRenderer(o->getSprite());
    }
    renderers.erase(std::remove(std::begin(renderers), std::end(renderers), &ren), std::end(renderers));
}
