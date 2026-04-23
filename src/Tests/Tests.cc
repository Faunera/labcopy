export module FTests;
import std;
import FLib;

export
{
    namespace tests
    {
        bool testAll();

        // ResrouceManager
        bool testResourceManager();
        // File Read/Write
        bool testFileReadWrite();

        //Input
        bool testInputManager();

        // Object Manager 
        bool testObjectManager();
        bool testFindObject();
        // Game Object tests
        bool testGameObject(GameObject& go);
        bool testMovRotExp(GameObject& go);

        // Physics tests
        bool testPhysicsManager();

        // Renderer tests
        bool testRenderer();
    }
}

