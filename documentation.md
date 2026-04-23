
# Table of contents

- [Documentation](#documentation)
- [TDD](#tdd)

# Documentation

Explain the usage of classes and such


## Doc Table of Contents



## Object creation

Object Manager is a singular class that handles the creation and destruction of *GameObjects*

Only create and remove GameObjects through *ObjectManager*. When creating a new object, y ou need to give it a class derived from *RenderObject*

```CXX
// Creating new actor

// The R is a derived class from RenderObject
createActor<R>{std::in_place_type_t<R>{}};
```

To render *GameObjects* add the *GameObjects* to a *Renderer* through *ObjectManager*

## Renderers

Renderers handle the graphics.

**IMPORTANT**: Before a *Renderer* is destructed, you must remove the reference to it from *ObjectManager* 





# TDD

## TDD Table of Contents

- [Style](#tdd-style)
- [Timer](#timer)
- [GameObject](#gameobject)
- [RenderComponent](#renderobject)
- [PhysicsComponent](#physicscomponent)


## TDD style

```markdown
## Name of the class (e.g. ObjectManager)
**Description**: General description of class' purpose
**Links**:
- Related files: Link to class' files (e.g. ObjectManager.cc, ObjectManager.cpp)
- Related classes: Links to what primary classes it calls (e.g. GameObject)
**Functionality explanation**: More in-depth explanation of class' functionality. (i.e. How it achieves its purpose)
**Example**: ```CXX Basic usage of class ```
**Last updated**: When section has last been updated
```
---

## Timer
**Description**: Returns elapsed time since construction or reset

**Functionality**: Takes time now upon construction. When elapsed() is called, returns the time difference in milliseconds. 

Timer's print() function prints the elapsed time in milliseconds. 

Timer's reset() function sets the time point to now

**Example**:
```CXX
Timer t{}; // Takes time now

t.print(); // Prints elapsed time

t.reset(); // Sets the time comparison to now, resetting the timer
```
**Last updated**: 15.01.2026

## GameObject
**Description**: Object in-game that is renderable and position, rotation and bounds.

**Functionality**: GameObject is created and managed via ObjectManager.

GameObject has methods to change its position, rotation and bounds. 

Has RenderComponent so it may be rendered via Renderer/RenderManager.

Has PhysicsComponent so it may have physical collision with other objects and to change its position based on physics.

**Example**
```CXX

```
**Last updated**: 14.01.2026

## RenderComponent
**Description**: In-game object that is renderable. Managed by Renderer/RenderManager

**Functionality**: RenderComponent is tied to some other object (expected to be GameObject).

A Renderer/RenderManager is given a pointer to this component, so it may be rendered onscreen.

**Example**
```CXX

```
**Last updated**: 14.01.2026


## PhysicsComponent

**Description**: Component that gives physics

**Functionality**: PhysicsComponent is tied to some other object (expected to be GameObject).

Component is managed by PhysicsManager that does physics calculations for PhysicsComponents. The result of those calculations are then passed to PhysicsComponent, so they may affect the GameObject in some way

**Example**
```CXX

```
**Last updated**: 14.01.2026

## ObjectManager
**Description**: Manager through which GameObjects are meant to be created, updated and deleted. 


**Functionality**: Can create new GameObjects and saves them to a GameObject vector, so they may be updated later.

**Example**
```CXX
// Creates new object and returns its ID
auto objID{ObjectManager::getManager().createObject<RenderObject>()};

// Removes the object with given ID
ObjectManager::getManager().removeObjectById(objID);
```

**Last updated**: 14.01.2026

# Notes

Floating point tests:
```CXX
float calc(float s, float d, int count)
{
    for(int i{0}; i < count; ++i)
        s -= d;
    return s;
}

const auto total{1'000'000};
int count{0};
for(int i{0}; i < total; ++i)
{
    auto exp{static_cast<float>(i)/10.0f};
    auto act{calc(9.0f + exp, 0.002f, 4500)};
    if (floatCompare(act, exp))
        ++count;
}
```
