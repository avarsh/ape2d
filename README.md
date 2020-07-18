# APE-2D

## What's Going On?

APE-2D (or APE) is game development framework built on modern C++. Its founding principle is to use a data-oriented approach through its use of the entity-component-system (ECS) architecture. In practice this works in the following manner:

- Entities represent game objects and are simple integer IDs
- Components are classes which contain data
- Components can be added to entities to allow any type of game entity to be built
- Systems operate on all entities with certain components. For example, a rendering system may take all entities with a sprite and a position component and render them.

This system allows for far greater flexibility and control when compared to a traditional OOP approach in which game entities are classes with properties, and
where large inheritance trees can create confusion.

## Building and Installation

Ensure that you have `meson` installed, as well as the `SDL2` and `SDL2_image` dependencies. Then, run:

```
meson setup build
cd build
ninja
ninja install
```