export module FPhysicsManager;
import std;
import FAlias;
import FObjects;
import FError;

export
{
    // PhysicsComponent allows the object to be taken into physics calculations
    // It has non-owning pointer to it's parent GameObject
    class PhysicsComponent
    {
    public:
        PhysicsComponent(GameObject& p);
        ~PhysicsComponent();
        
        auto getParent() -> GameObject&;

        void update();

        const int32 id{ids::pcuid++};
    private:
        GameObject& parent;
    };

    class PhysicsManager
    {
    public:
        static auto getManager() -> PhysicsManager&;

        auto getComponents() -> std::vector<PhysicsComponent*>&;

        void update();

        void addComponent(PhysicsComponent* pc);
        void removeComponent(PhysicsComponent* pc);
    private:
        PhysicsManager();
        ~PhysicsManager();

        static PhysicsManager manager;

        std::vector<PhysicsComponent*> components{};
    };
}
