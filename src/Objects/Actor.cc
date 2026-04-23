export module FActor;
import std;
import FObjects;
import FPhysicsManager;
import FAlias;
import FError;

export
{  
    // Actor is a GameObject that has PhysicsComponent
    class Actor : public GameObject
    {
    public:
        template<class R>
	    Actor(std::in_place_type_t<R>, Vecf pos = {}, Vecf rot = {}, Vecf bou = {}) :
            GameObject{std::in_place_type_t<R>{}, pos, rot, bou},
            physics{std::make_unique<PhysicsComponent>(*this)}
        {
            name = "Actor";
        }
        auto getPhysics() -> PhysicsComponent&;

    private:
        std::unique_ptr<PhysicsComponent> physics;
    };
}
