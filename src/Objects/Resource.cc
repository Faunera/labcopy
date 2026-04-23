 export module FResource;
 import std;
 import FAlias;

 export
 {
      // Base class for Resource
    class Resource
    {
    public:
        virtual ~Resource(){}

        virtual void load() {}
        virtual void unload() {}

        int32 uid{0};
        int scope{0};
        RType type{RType::Null};
        std::string filename{};
    };
 }
