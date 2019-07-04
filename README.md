# What is the APE-2D Game Engine?
![tetris.png](https://bitbucket.org/repo/9pRB75n/images/812539660-apeimg.png)

APE-2D (or APE) is an experimental 2D game engine built on C++14 and OpenGL. Its founding principle is to use a data-oriented approach through its use of 
the entity-component-system (ECS) architecture. In practice this works in the following manner:

- Entities represent game objects and are simple integer IDs
- Components are classes which contain data and optionally some relevant methods
- Components can be added to entities to allow any type of game entity to be built
- Systems operate on all entities with certain components. For example, a rendering system may take all entities with a sprite and a position component and render them.

This system allows for far greater flexibility and control when compared to a traditional OOP approach in which game entities are classes with properties, and
where large inheritance trees can create confusion.

# Current and Proposed Features

 The engine is currently being rewritten.