# What is the APE-2D Game Engine?

APE-2D (or APE) is an experimental 2D game engine built on C++14 and OpenGL. Its founding principle is to use a data-oriented approach through its use of the entity-component-system (ECS) architecture. In practice this works in the following manner:

- Entities represent game objects and are simple integer IDs
- Components are classes which contain data and optionally some relevant methods
- Components can be added to entities to allow any type of game entity to be built
- Systems operate on all entities with certain components. For example, a rendering system may take all entities with a sprite and a position component and render them.

This system allows for far greater flexibility and control when compared to a traditional OOP approach in which game entities are classes with properties, and where large inheritance trees can create confusion. 

# Current and Proposed Features

Currently, the following features have been implemented:

- 2D texture loading and sprite rendering through OpenGL
- A sprite batch rendering system for added efficiency
- Sprite transformation
- Featured ECS library built in
- A scene graph based system for rendering

These features are proposed or are being worked on:

- Input system using "contexts" which allow for flexibility
- Sound playback
- More comprehensive scene graph system, allowing for collated transformations and node removal
- Further graphical features, such as primitives
