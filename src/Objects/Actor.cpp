module FActor;

/* ACTOR */

auto Actor::getPhysics() -> PhysicsComponent&
{
    return *physics.get();
}
