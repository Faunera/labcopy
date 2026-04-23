# ModuleEngine
Game engine library made with C++ modules.


# Requirements
Regarding libraries, see [NOTICE](./NOTICE.txt) for their sources and licenses. These libraries can be found in 'ext' folder.


Compilation:
- G++ 15.2.0
- Make
- Valgrind

Libraries:
- GLFW
- GLM
- TinyXML2


# Table of Contents

- [Documentation](./documentation.md)
- [Practices](./practices.md)
- [Bugs & issues](./bugs.md)


# TODO
Rework tests

Update readme

## Notes
**Add following rule to documentation:**

Before destroying a Renderer, you must clear objects from that renderer

**Add following rule to practices:**

Specify the use of 'override' on Derived Class' functions that are virtual.

This way there will be error e.g. if the function type isn't exactly same as Base class


### Functionnoids, function pointer stuff
[ISO CPP Functionoids](https://isocpp.org/wiki/faq/pointers-to-members)

Function pointer alias
```CXX
using FuncPtr = void(*)();
```
Functionoid usage with class functions
```CXX
// Class we want to call function of
class ABC
{
    public:
    void fp(){std::cout << "ABC\n";}
};
// Functionoid base calss
class Function
{
public:
    virtual void doit() = 0;
    virtual ~Function() = 0;
};

// Functionoid we use to call class function
class AFunc : public Function
{
public:
    AFunc(ABC* p) : parent{p}
    {

    }
    void doit(){parent->fp();}
    ABC* parent;
};

Function::~Function(){}

int main()
{
    ABC abc{};
    Function* fp{new AFunc{&abc}};
    
    fp->doit();

    delete fp;
    return 0;
}
```
