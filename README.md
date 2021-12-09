# Astroids-Box2D
Something small I made to practice with box2D. An astroids clone with realistic phisics. Control the ship with the arrow keys and shoot with the spacebar. 
Spawn new astroids by left clicking with the mouse. Enjoy! ;)

# Explanation
The project has 4 major classes.
- Gameloop/ Game: The gameloop gets the user input, updates the logic of the game and renders it on the screen. The gameloop defines an interface Game for the gameloop to interact with. 
- Box: Box is an concrete implementation of the Game interface. This object contains the Box2D world that contains all the physical elements. It repositions the astroids when they go out of bounds and removes the bullets when they hit an object. It renders all the objects by converting the points from meters to pixels.
- KeyListener: An interface used by the Box object to raise Key-Events
- Ship: Contains the data for the ship and implements the KeyListener interface. 

# Installation
Download the zip file and unpack it.

Open the solution file with Visual Studio.

Right click on the solution in the solution explorer and press build.

Right click on the project in the solution explorer -> debug -> start new instance.

-----------------------------------------------------------------------------------------------------------
Or download the executable together with the SDL2.dll. Both files should be in the same folder.
