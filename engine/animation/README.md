# Animation

## System

The _animation system_ updates all objects with an _animation component_. It updates each _animation state machine_.

## Component

Each _animation component_ contains an _animation state machine_.

## State Machine

An _animation state machine_ dictates which _animation clip_ is currently being played.

There are different types of nodes in the state machine:

- Animation clip nodes play a single animation clip when that node is selected.

- Blend space nodes take in one or more parameters (such as velocity or direction) and a number of animation clips that are represented in a normalized ([-1, 1]) space. The blend space selects the closest clip based on the input parameters.

Each directed edge returns true if a transition can be made from the current node to another. When a node is visited, its animation clip is started and any other animation clips playing are stopped. A transition can be tied to any system (for example, there might be a transtion based on input or player velocity).

## Clip

An _animation clip_ is composed of a number of _animation frames_. It also contains playback information, such as whether or not to loop, and the duration of each frame.

A clip also contains an array of events with attached timestamps. These events communicate to other game systems (for example, to play a sound effect) when that timestamp of the animation is reached.

## Frame

An _animation frame_ holds a reference to the texture atlas and a cel within that atlas.
