# ECS

The **ECS framework** contains entities, components, and systems.

## Entities

Entities are *game objects*. They contain zero or more components that are bundles of data (no logic). For example, if an entity needs to be animated, it would contain the `ECS::Animation::Component`.

## Components

Components are *data-only objects* that are stored on entities.

## Systems

A system updates components at specific intervals. For example, the `ECS::Animation::System` manages the updating of animation components, while the `ECS::Animation::Renderer` (also a system) manages the display of those components via the graphics system. In order for its components to be updated, an entity must register itself with a system.
