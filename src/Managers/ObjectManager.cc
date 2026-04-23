export module FObjectManager;
import std;
import FAlias;
import FError;
import FObjects;
import FActor;
import FRenderer;

export
{
    class ObjectManager
    {
    public:
        static auto getManager() -> ObjectManager&;

        auto getObjects() -> std::vector<std::unique_ptr<GameObject>>&;

        // Create new GameObject with given RenderObject/
        template<class R>
        auto createObject(Vecf pos = {0.0f, 0.0f, 0.0f}, Vecf rot = {0.0f, 0.0f, 0.0f},
                          Vecf bound = {0.0f, 0.0f, 0.0f}) -> GameObject*
        {
            objects.push_back(std::make_unique<GameObject>(std::in_place_type_t<R>{}, pos, rot, bound));
            return objects.back().get();
        }

        // Create new Actor with given RenderObject
        template<class R>
        auto createActor(Vecf pos = {0.0f, 0.0f, 0.0f}, Vecf rot = {0.0f, 0.0f, 0.0f},
                         Vecf bound = {0.0f, 0.0f, 0.0f}) -> GameObject*
        {
            objects.push_back(std::make_unique<Actor>(std::in_place_type_t<R>{}, pos, rot, bound));
            return objects.back().get();
        }

        // Find object by id
        auto findObject(int id) -> GameObject*;
        // Remove by Id
        void removeObjectById(int id);
        void removeObject(GameObject* go);

        void clearObjects();

        // Adds every object to given renderer
        void addToRendererAll(Renderer& ren);

        // Adds given object to given renderer
        void addToRenderer(Renderer& ren, GameObject& go);
        // Removes object from all renderers
        void removeFromRenderers(GameObject& go);

        // Removes given renderer from references
        void removeRendererRef(Renderer& ren);
    private:
        ObjectManager();
        ~ObjectManager();

        static ObjectManager manager;
        std::vector<std::unique_ptr<GameObject>> objects{};
        std::vector<Renderer*> renderers{};
    };
}
