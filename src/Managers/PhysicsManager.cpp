module FPhysicsManager;

PhysicsManager PhysicsManager::manager{};

/* PHYSICS COMPONENT */
//
//
PhysicsComponent::PhysicsComponent(GameObject& p) : parent{p}
{
    PhysicsManager::getManager().addComponent(this);
}

PhysicsComponent::~PhysicsComponent()
{
    PhysicsManager::getManager().removeComponent(this);
}

void PhysicsComponent::update()
{
    ErrorManager::getManager().logEvent("Updating PhysComp: " + std::to_string(id));
}

auto PhysicsComponent::getParent() -> GameObject&
{
    return parent;
}

/* PHYSICS MANAGER */
//
//

PhysicsManager::PhysicsManager()
{

}

PhysicsManager::~PhysicsManager()
{

}

auto PhysicsManager::getManager() -> PhysicsManager&
{
    return manager;
}


auto PhysicsManager::getComponents() -> std::vector<PhysicsComponent*>&
{
    return components;
}

void PhysicsManager::update()
{
    for (auto& c : components)
    {
        c->update();
    }
}

void PhysicsManager::addComponent(PhysicsComponent* pc)
{
    if (pc)
    {
        if (std::find(components.begin(), components.end(), pc) == components.end())
            components.push_back(pc);
    }
}

void PhysicsManager::removeComponent(PhysicsComponent* pc)
{
    if (pc)
    {
	    components.erase(std::remove(std::begin(components), std::end(components), pc), std::end(components));
    }
}
