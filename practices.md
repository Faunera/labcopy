
# Practices

## Practices Table of Contents

**Informative**
- [Terminology](#terminology)
- [Style](#practices-style)
- [Project specific](#project-specific)
---
**Practical**
- [Readability](#0-readability)
- [Modules](#1-modules)
- [Headers](#2-headers)
- [Variables](#3-variables)
- [Functions](#4-functions)
- [Classes](#5-classes)

## Terminology

- **Setter/Getter** - Member function meant for the modification (*setter*) of a member variable or for returning (*getter*) of said member variable.

## Practices style
```markdown
## x. General Practice
### x.x Specific Practice
**Description**: Explanation of practice
**Reasoning**:  Why this practice
**Example**
```CXX Example of the practice.```
**Misc**: Links to related examples etc. 
**Last updated**: When last udpated
```

## Project specific
### Class code files should be in same directory
---
**Description**: Aside from possible class header-files, its code-files (.cpp, .cc) ought to be put in the same directory.

**Reasoning**: This is important due to how build has been set up in Makefile. Additionally, when they're expected to be in the same directory, then they should be easier to find.

**Example folder structure**:
```
root
|   src
|       Object.cc
|       Object.cpp
|   header
|       Object.h
```

### Use C++
---
**Reasoning**: C++ provides a lot of features for memory management and type safety.

E.g. instead of using C-style arrays, you use std::vector or std::array

### Import external libraries as modules
---
**Reasoning**: General benefits of modules AND by making them into modules they're easier to use with other modules.


## 0. Readability

### Readability is more important than 'clever' solutions
---

### 0.1 Scope brackets should be aligned
**Description**: Scope brackets ought to be aligned either vertically or horizontally.

**Reasoning**: This makes it easier to tell where scope begins or ends

#### Example BAD:
```CXX
// Difficult to tell where particular scope begins
function(){
    for (int i{}; i < 10; ++i){
        if (i > 5){
            std::cout << i << "\n";
        }
    }
}
```
#### Example GOOD:
```CXX
// Scope brackets are on the same indentation level
// thus easier to tell where scope begins and ends
function()
{
    for (int i{}; i < 10; ++i)
    {
        if (i > 5)
        {
            std::cout << i << "\n";
        }
    }
}
```

### 0.2 Use comments when necessary
**Reasoning**: Your code is unlikely to be self-documenting, even if you wish it were.

If you cannot explain the code after 5 minutes, perhaps it is good to comment it.

**Comments should explain the intent of the code**

### 0.3 Naming conventions
Use the following conventions for naming:
- Variables: camelCase
- Functions: camelCase
- Classes: PascalCase
- Files: Files use the most prominent's class' name (e.g. ObjectManager.cc)
- Modules: Use the file's name, with F prefix (e.g. FObjectManager)

```CXX
// In ManagerClass.cc
// As ManagerClass is the most prominent class, the file is named after it

// Module is named after the file with F prefix
export module FManagerClass;

// Classes follow PascalCasing
class ManagerClass
{
public:
    int managerIdentifier{}; // Variables follow camelCasing

    void printMessage() // Functions follow camelCasing
};
```

### 0.4 Name identifiers in relative to their scope
**Description**: Larger the scope that identifier is visible to, the longer its name ought to be. Conversely, smaller the scope, the shorter the name can be.

Ideally variables with large scopes should be put in their own namespace.

**Example**
```CXX
// Namespace for variables with large scope
namespace globalvars
{
    std::string businessName;   
}

class A
{
public:
    std::string name; // Short name, as it's scope is limited to class

    void action()
    {
        int i{}; // Only relevant within function
    }

}

int main()
{
    int identifier{0}; // In main scope, so somewhat long identifier

    {
        int i{}; // Limited to short scope, so short identifier
    }
}

```

### 0.5 Use aliases for complex types
**Reasoning**: Readability.

**Example**
```CXX
std::array<float, 3>; // Somewhat long type

using Array3f = std::array<float, 3>; // Simpler
```

### 0.6 Prefer auto with leading type, when declaring function return type
**Reasoning**: Return types can get pretty long and this can negatively affect readability of functions. This will make function declarations more uniform in their style and with this, should improve readability.

In addition, with auto the function names are better indented at same level
 
**Example BAD**
```CXX
class Timer
{
public:
    Timer();

    // Oof, a little long
    std::chrono::duration<double, std::milli> elapsed() const;
    void print();
}
```
**Example GOOD**
```CXX
class Timer
{
public:
    Timer();

    // Better, and function names are closer to each other
    auto elapsed() const -> std::chrono::duration<double, std::milli> 
    void print();
 
}
```


## 1. Modules
### 1.1 Prefer modules to headers
**Reasoning**: Use of modules provides generally faster compile times.

```CXX
// Header-style
#include <iostream>

int main()
{
    std::cout << "Hello world\n";
    return 0;
}

// Module-style
import std;

int main()
{
    std::cout << "Hello world\n";
    return 0;
}
```
**Comparison**:
- Header-style compiled in about ~0.53s
- Module-style compiled in about ~0.15s
- Module-style imports whole std library, it isn't limited only to iostream
- While difference is negligible in a program so small, the benefit of modules on compile times should still be obvious

### 1.2 Make modules by default into .CC files
**Description**: Simply the practice I use.

### 1.3 Put function declarations into .CC files and definitions into .CPP files
**Reasoning**: Readability. By separating the declarations and definitions into separate files, it prevents a singular file from becoming too cluttered.

**Example**
```CXX
// A.cc
export module A;
import std;

class A
{
public:
    // Declaration
    void print(); 
};

// A.cpp
module A;

// Definition
void A::print()
{
    std::cout << "A";
}
```




## 2. Headers
### 2.1 Use include guards instead of pragma once
**Reasoning**: #pragma once is not standard
**Example**:
```CXX
#ifndef MY_INCLUDE_GUARD
#define MY_INCLUDE_GUARD

// code

#endif
```

**Additionally**: Use the following convention for naming include guards
```CXX
#ifndef MYLIBRARY_MYHEADER_HEADER
#define MYLIBRARY_MYHEADER_HEADER

// code

#endif
```

### 2.2 When headers must be used, turn them into modules
**Description**: At times headers must be used (e.g. circular dependencies). At such times, only include the declarations into the header file then import the header into a .cc-file.

This way the headers can be made into modules.




## 3. Variables
### 3.1 Use list-initialization or direct-list-initialization

[See C++ Core Guidelines ES.23](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Res-list)

**Example**:
```CXX
int index{}; // Direct-list-initialization
std::string {"Hello"}; // List-initialization
```



## 4. Functions




## 5. Classes
### 5.1 Use 'setters'/'getters' to ensure member variables are handled in expected manner
**Reasoning**: By restricting the usage of member variables to their related functions, we can 'ideally' prevent users from modifying those values in unexpected manner.

Doesn't apply to const members.

Our classes should be 'intuitive' enough that the user will understand what will happen, but not have to worry about the specifics of the implementation.

[See terminology](#terminology)

### 5.2 Give member get-functions const return type by default
**Reasoning**: We ought to minimize access to class members by default. If it turns out that access is required, either add a function for it or remove the const from return type.
**Example**
```CXX
class GameObject
{
public:
    GameObject();

    auto getPhysicsComponent() const -> const PhysicsComponent&;
private:
    std::unique_ptr<PhysicsComponent> physics;
}
```
