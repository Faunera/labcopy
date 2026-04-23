module FObjects;

/* GAME OBJECT */
//
//
auto GameObject::getSprite() -> RenderObject&
{
    return *sprite.get();
}

auto GameObject::getPosition() -> Vecf&
{
    return position;
}

auto GameObject::getRotation() -> Vecf&
{
    return rotation;
}

auto GameObject::getBounds() -> Vecf&
{
    return bounds;
}

void GameObject::move(Vecf xyz)
{
    if (position.size() <= xyz.size())
    {
        for (std::size_t i{0}; i < position.size(); ++i)
        {
            position[i] += xyz[i];
        }
    }
    else
    {
        for (std::size_t i{0}; i < xyz.size(); ++i)
        {
            position[i] += xyz[i];
        }
    }
}

void GameObject::rotate(Vecf ypr)
{
    if (rotation.size() <= ypr.size())
    {
        for (std::size_t i{0}; i < rotation.size(); ++i)
        {
            rotation[i] += ypr[i];
        }
    }
    else
    {
        for (std::size_t i{0}; i < ypr.size(); ++i)
        {
            rotation[i] += ypr[i];
        }
    }
}

void GameObject::expand(Vecf xyz)
{
    if (bounds.size() <= xyz.size())
    {
        for (std::size_t i{0}; i < bounds.size(); ++i)
        {
            bounds[i] += xyz[i];
        }
    }
    else
    {
        for (std::size_t i{0}; i < xyz.size(); ++i)
        {
            bounds[i] += xyz[i];
        }
    }
}

