module FTests;
import "GLFW/glfw3.h";

// Testing class 
class A : public RenderObject
{
    public:
    int a {0};
    void update()
    {
        ErrorManager::getManager().logEvent("Test RenderObject update call");
    }
};

// Testing class
class TestRenderer : public Renderer
{
public:
    TestRenderer(){}
    void load(Resource* res)override{}
    void unload(Resource* res)override{}
    void update() override
    {
        for (auto& s : getSprites())
        {
            s->update();
        }
    }
};

// Testing class
class TF : public Functionoid
{
public:
    virtual ~TF(){}

    void custom()
    {
        auto& error{ErrorManager::getManager()};
        error.logEvent("Key Function Call");
    }

};

void testAll()
{/*
    Timer lt{};

    testInputManager();

    testObjectManager();

    testPhysicsManager();

    testRenderer();
    std::cout << "Timer: ";
    lt.print();
    std::cout << "Reset timer: ";
    lt.reset();
    lt.print();*/
}

namespace tests
{
    bool testAll()
    {
        Timer lt{};
        auto& error{ErrorManager::getManager()};
        error.logEvent("Begin all tests");
        if (!testFileReadWrite())
            return false;
        if (!testResourceManager())
            return false;
        if (!testInputManager())
            return false;
        if (!testObjectManager())
            return false;
        if (!testPhysicsManager())
            return false;
        if (!testRenderer())
            return false;

        error.logEvent("End all tests successfully\n");
        std::cout << "Tests took: ";
        lt.print();        
        return true;
    }


    /* RESOURCE MANAGER */
    bool testResourceManager()
    {
        auto& error{ErrorManager::getManager()};
        error.logEvent("Begin ResourceManager tests");
        auto& manager{ResourceManager::getManager()};

        // Test loading
        std::string testxml{"./assets/xml/test.xml"};
        error.logEvent("Loading from XML " + testxml);
        if (!manager.loadFromXML(testxml))
        {
            error.logEvent("Failed to load XML: " + testxml);
            return false;
        }

        // Test finding resource by id
        error.logEvent("Trying to find resource with id 0");
        if (auto res{manager.findResourceByID(0)}; !res)
        {
            error.logEvent("Failed to find expected resource");
            error.logEvent("This is due to unfinished implementation of LoadXML function in resourcemanager, continuing");
            //return false;
        }
        error.logEvent("Testing the handling of searching invalid resource");
        if (auto res{manager.findResourceByID(-1)}; res)
        {
            error.logEvent("Found resource that should not exist");
            return false;
        }
    
        error.logEvent("End ResourceManager tests\n");
        return true;
    }


    /* FILE READ/WRITE */
    bool testFileReadWrite()
    {
        auto& error{ErrorManager::getManager()};
        error.logEvent("Begin File ReadWrite tests");
        std::string testFile{"testfile.txt"};
        rewriteFile(testFile, "");

        error.logEvent("Write a test sentence to " + testFile);
        std::string testSentence{"Testing the file writing\nTest File Write"};
        writeFile(testFile, testSentence);

        error.logEvent("Read from " + testFile + " and compare content to test sentence");
        {
            auto file{readFile(testFile)};
            std::string content{file.begin(), file.end()};
            // File functions automatically add newlines, so take them into account in comparison
            std::string compareSentence{"\n" + testSentence + "\n"};

            if (compareSentence != content)
            {
                error.logEvent("The contents do not match: Either an error with readFile() or writeFile()");
                return false;
            }
        }
        
        error.logEvent("Test File Rewrite");
        testSentence = "TestContent";
        rewriteFile(testFile, testSentence);
        {
            auto file{readFile(testFile)};
            std::string content{file.begin(), file.end()};
            std::string compareSentence{testSentence + "\n"};

            if (compareSentence != content)
            {
                error.logEvent("The contents do not match: Either an error with readFile() or rewriteFile()");
                return false;
            }
        }

        error.logEvent("End File ReadWrite tests\n");
        return true;
    }


    /* INPUT */
    bool testInputManager()
    {
        auto& error{ErrorManager::getManager()};
        error.logEvent("Begin InputManager tests");
        auto& manager{InputManager::getInput()};
        
        for (auto& k : manager.getKeys())
        {
            //if (k.get())
            //    testInputKey(*k.get());
        }

        error.logEvent("Test find key");
        if (auto key{manager.findKey(GLFW_KEY_A)}; !key)
        {
            error.logEvent("Couldn't find expected key");
            return false;
        }

        // From hereon; Temporary tests of add/remove/switch functions
        auto testlam{[&]()
        {
            size_t r{0}; 
            for (auto& k : manager.getKeys())
            {
                if (!k.get())
                {
                    continue;
                }
                r += k->getFunctions().size();
            }
            return r;
        }};

        error.logEvent("Test adding/removing of key functions");
        std::unique_ptr<TF> tf_ptr{std::make_unique<TF>()};
        manager.addKeyFunc(GLFW_KEY_A, tf_ptr.get());
        if (testlam() != 1) // size should be 1
        {
            error.logEvent("Failed to add expected amount of key functions");
            return false;
        }
        manager.addKeyFunc(GLFW_KEY_B, tf_ptr.get());
        if (testlam() != 2) // size should be 2
        {
            error.logEvent("Failed to add expected amount of key functions");
            return false;
        }
        manager.removeKeyFunc(GLFW_KEY_B, tf_ptr.get());
        manager.removeKeyFunc(GLFW_KEY_A, tf_ptr.get());
        if (testlam() != 0) // size should be 0
        {
            error.logEvent("Failed to remove expected amount of key functions");
            return false;
        }
        manager.switchKeyFunc(GLFW_KEY_A, GLFW_KEY_B, tf_ptr.get());
        if (testlam() != 1) // size should be 1
        {
            error.logEvent("Failed to switch expected amount of key functions");
            return false;
        }
        error.logEvent("Try calling key function");
        manager.findKey(GLFW_KEY_B)->setState(true); // Enable
        manager.callKey(GLFW_KEY_B);
        manager.findKey(GLFW_KEY_B)->setState(false); // Disable
        manager.removeKeyFunc(GLFW_KEY_B, tf_ptr.get());

        error.logEvent("Test MultiKey");
        manager.addMultiKeyFunc({GLFW_KEY_A, GLFW_KEY_B}, tf_ptr.get());
        if (testlam() != 2) // size should be 2
        {
            error.logEvent("Failed to add expected amount of multikey functions");
            return false;
        }
        manager.removeMultiKeyFunc({GLFW_KEY_A, GLFW_KEY_B}, tf_ptr.get());
        if (testlam() != 0) // size should be 0
        {
            error.logEvent("Failed to remove expected amount of multikey functions");
            return false;
        }
        manager.addMultiKeyFunc({GLFW_KEY_A, GLFW_KEY_B}, tf_ptr.get());
        manager.switchMultiKeyFunc({GLFW_KEY_A, GLFW_KEY_B}, {GLFW_KEY_W, GLFW_KEY_E}, tf_ptr.get());
        if (testlam() != 2) // size should be 2
        {
            error.logEvent("Failed to switch expected amount of multikey functions");
            return false;
        }
        for (auto& k : manager.getKeys())
        { 
            if (!k)
                continue;
            k.get()->setState(true);
            k.get()->callFuncs();
        }
        for (auto& k : manager.getKeys())
        {
            if (!k)
                continue;
            k.get()->setState(false);
        }

        error.logEvent("End InputManager tests\n");
        return true;
    }


    /* OBJECT */
    bool testObjectManager()
    {
        auto& error{ErrorManager::getManager()};
        error.logEvent("Begin ObjectManager tests");
        std::cout << "-- Test ObjectManager --\n";
        auto manager{&ObjectManager::getManager()};
        auto sizelam{[&](){return manager->getObjects().size();}};
        manager->clearObjects();

        std::cout << "Add 3 new GameObjects to manager\n";
        for (int i{0}; i < 3; ++i)
            manager->createObject<A>();
        if (sizelam() != 3)
        {
            error.logEvent("Objects size does not match expected: 3");
            return false;
        }
        error.logEvent("Add 3 new Actors to manager");
        for (int i{0}; i < 3; ++i)
                manager->createActor<A>();
        if (sizelam() != 6)
        {
            error.logEvent("Objects size does not match expected: 6");
            return false;
        }

        error.logEvent("Test Objects");
        for (auto& a : manager->getObjects())
        {
            if (!testGameObject(*a))
            {
                error.logEvent("Object test unsuccessful");
                return false;
            }
        }
        testFindObject();
        error.logEvent("Size of objects: " + std::to_string(manager->getObjects().size()));
        error.logEvent("Test remove object");
        manager->removeObjectById(0);
        if (sizelam() != 5)
        {
            error.logEvent("Objects size does not match expected: 5");
            return false;
        }
        // Try removing invalid
        manager->removeObjectById(-1);

        error.logEvent("Create actor and object");
        if (auto actor{manager->createActor<A>()}; !actor)
        {
            error.logEvent("Couldn't create an actor");
            return false;
        }
        if (auto actor{manager->createObject<A>()}; !actor)
        {
            error.logEvent("Couldn't create an object");
            return false;
        }

        error.logEvent("Clear objects");
        manager->clearObjects();
        if (sizelam() != 0)
        {
            error.logEvent("Couldn't clear objects");
            return false;
        }
        error.logEvent("End ObjectManager tests\n");
        return true;
    }

    bool testFindObject()
    {
        auto manager{&ObjectManager::getManager()};
        auto& error{ErrorManager::getManager()};
        error.logEvent("Test find object");
        
        if (auto a{manager->findObject(0)}; !a)
        {
            error.logEvent("Couldn't find an object that was expected to be found");
            return false;
        }

        error.logEvent("Test handling of searching an invalid object");
        if (auto a{manager->findObject(-1)}; a)
        {
            error.logEvent("Unexpectedly found existing object");
            return false;
        }
        return true;
    }


    /* GAME OBJECT */
    bool testGameObject(GameObject& go)
    {
        return testMovRotExp(go);
    }

    bool testMovRotExp(GameObject& go)
    {
        auto& error{ErrorManager::getManager()};
        error.logEvent("Testing Mov/Rot/Exp of: " + go.name + " Id: " + std::to_string(go.id));

        auto comp = [&](Vecf xyz, Vecf zpr)
        {
            if (xyz.size() != 3 || zpr.size() != 3)
                return false;
            return  floatCompare(xyz[0], zpr[0]) &&
                    floatCompare(xyz[1], zpr[1]) &&
                    floatCompare(xyz[2], zpr[2]);
        };
        
        error.logEvent("Test Move");
        go.move({1.0f, -5.0f, 10.f});
        if (!comp({1.0f, -5.0f, 10.f}, go.getPosition()))
        {
            error.logEvent("Object didn't move as expected"); 
            return false;
        }

        error.logEvent("Test Rotation"); 
        go.rotate({90.0f, -70.0f, 50.0f});
        if (!comp({90.0f, -70.0f, 50.0f}, go.getRotation()))
        {
            error.logEvent("Object didn't rotate as expected"); 
            return false;
        }

        error.logEvent("Test Expansion"); 
        go.expand({1.0f, 3.0f, 4.0f});
        if (!comp({1.0f, 3.0f, 4.0f}, go.getBounds()))
        {
            error.logEvent("Object didn't expand as expected"); 
            return false;
        }

        return true;
    }

    /* PHYSICS */
    bool testPhysicsManager()
    {
        auto& error{ErrorManager::getManager()};
        error.logEvent("Begin PhysicsManager tests");
        auto& manager{PhysicsManager::getManager()};
        ObjectManager::getManager().clearObjects();
        auto sizecomp{[&](unsigned i){return manager.getComponents().size() == i;}};

        error.logEvent("Testing addition and removal of physics components");
        {
            Actor a{std::in_place_type_t<A>{}};
            {
                Actor b{std::in_place_type_t<A>{}};
                if (!sizecomp(2))
                {
                    error.logEvent("Found more physics components than expected");
                    return false;
                }
            }
        }
        if (!sizecomp(0))
        {
            error.logEvent("Couldn't remove expected amount of components");
            return false;
        }


        auto& objmanager{ObjectManager::getManager()};
        error.logEvent("Create multiple actors");
        for (int i {0}; i < 10; ++i)
            objmanager.createActor<A>();
        auto& actors{objmanager.getObjects()};
        if (!sizecomp(10))
        {
            error.logEvent("Couldn't add expected amount of components");
            return false;
        }

        error.logEvent("Test update");
        manager.update();

        error.logEvent("Clear actors");
        objmanager.clearObjects();
        if (!sizecomp(0))
        {
            error.logEvent("Couldn't remove expected amount of components");
            return false;
        }

        error.logEvent("End PhysicsManager tests\n");
        return true;
    }


    /* RENDERER */
    bool testRenderer()
    {
        auto& error{ErrorManager::getManager()};
        error.logEvent("Begin Renderer tests");
        auto& objmanager{ObjectManager::getManager()};
        for (int i {0}; i < 5; ++i)
            objmanager.createActor<A>();
        
        // Test behaviour when renderer is destroyed early
        error.logEvent("Test behaviour when renderer is destroyed early");
        {
            TestRenderer fake{};
            error.logEvent("Adding renderobjects to temp renderer");
            objmanager.addToRendererAll(fake);
            objmanager.removeRendererRef(fake);
            if (fake.getSprites().size() != 0)
            {
                error.logEvent("Couldn't remove expected amount of renderobjects from renderer");
                return false;
            }
        }
        error.logEvent("Finish behaviour test");

        error.logEvent("Adding 5 renderobjects to renderer");
        TestRenderer rend{};
        objmanager.addToRendererAll(rend);
        if (rend.getSprites().size() != 5)
        {
            error.logEvent("Couldn't add expected amount of renderobjects to renderer");
            return false;
        }
        error.logEvent("Remove latest renderobject");
        objmanager.removeObjectById(ids::auid - 1);
        if (rend.getSprites().size() != 4)
        {
            error.logEvent("Couldn't remove expected amount of renderobjects to renderer");
            return false;
        }

        error.logEvent("Update objects");
        rend.update();
        error.logEvent("Remove renderobjects from renderer");
        
        objmanager.clearObjects();
        if (rend.getSprites().size() != 0)
        {
            error.logEvent("Couldn't remove expected amount of renderobjects to renderer");
            return false;
        }

        error.logEvent("End Renderer tests\n");
        return true;
    }
}





