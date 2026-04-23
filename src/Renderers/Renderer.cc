export module FRenderer;
import std;
import FResource;
import FObjects;
import FError;

export
{
    // Base class for renderers
    class Renderer
    {
    public:
        virtual ~Renderer(){};
        
        virtual void load(Resource* res){}
        virtual void unload(Resource* res){}
        virtual void update(){}

        auto getSprites() -> std::vector<RenderObject*>&
        {
            return sprites;
        }
        
        void addToRenderer(RenderObject& ro)
        {
            if (std::find(sprites.cbegin(), sprites.cend(), &ro) == sprites.end())
                sprites.push_back(&ro);
        }

        void removeFromRenderer(RenderObject& ro)
        {
            sprites.erase(std::find(std::begin(sprites), std::end(sprites), &ro));
        }
    private:
        std::vector<RenderObject*> sprites{};
    };
}
