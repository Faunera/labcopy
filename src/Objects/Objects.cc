export module FObjects;
import std;
import FAlias;
import FError;

export
{ 
    // RenderObject is abstrac class for objects that are to be rendered
    // RenderObjects should be handled through their owning class
    // e.g. GameObjects sets flags to its renderobject etc.

    // Consider refactoring RenderObject to be RenderResource, for ResourceManager purposes
    class RenderObject
    {
    public:
        virtual ~RenderObject() {};
        virtual void update() = 0;
    };

    // Game object has Position/Rotation/Bounds and pointer to renderobject
    class GameObject
    {
    public:
        template<class R>
	    GameObject(std::in_place_type_t<R>, Vecf pos = {}, Vecf rot = {}, Vecf bou = {}) 
            : sprite{ std::make_unique<R>() }, position{pos}, rotation{rot}, bounds{bou}
        {
            // Resize position/rotation/bounds to 3, if they're smaller than that
            if (position.size() < 3)
                position.resize(3);
            if (rotation.size() < 3)
                rotation.resize(3);
            if (bounds.size() < 3)
                bounds.resize(3);
        }

        virtual ~GameObject() {}
        
        auto getSprite() -> RenderObject&;

        auto getPosition() -> Vecf&;
        auto getRotation() -> Vecf&;
        auto getBounds() -> Vecf&;

        virtual void move(Vecf xyz);
        virtual void rotate(Vecf ypr);
        virtual void expand(Vecf xyz);

        std::string name{"GameObject"};
        const int32 id{ids::auid++};
    private:
        std::unique_ptr<RenderObject> sprite;
        Vecf position;
        Vecf rotation;
        Vecf bounds;
    };
}
