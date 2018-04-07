# Artemis
Artemis is a 2D vector graphics library that I & a few friends built. It is a step in modern graphics development to ease the difficulties faced by all kinds of game programmers. It is similar to SVG except that I have chosen simplicty over complexity. It involves some very basic renderable primitives inspired from Processing(p5.js). 

It allows you to separate out your game logic from your rendering part. You write your renderable descriptions in a separate file and then import it using Artemis' parser into your game and render them. This has two advantages:
1. You are able to write & change your renderables without doing any modification to your existing game code.
2. Designers and Programmers can now work separtely!

Alright, enough talking! Let's get into some code now.

## Repository Details
Artemis comes with a parser and an example Breakout Game which should give you enough details on how to use Artemis! 

Plus, I also included some examples inside the tests folder, like the ```us_map.aml"``` which shows the usage of the ```<polygon>``` tag.

## Usage
Clone the repository onto your machine.
Launch the solution, select your build configuration: x86 or x64 & set ArtemisBreakout as your startup Project.