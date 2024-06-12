# 2048_SFML_final

This project is a version of the popular game 2048, implemented using the SFML library for the graphical user interface.
This is also a project in the course "Kỹ thuật lập trình" - HCMUS.

## Features

- Different game modes: The game supports different board sizes, from 4x4 up to 10x10.
- Score tracking: The game keeps track of the player's current score and the best score achieved.
- Player registration: Players can register with a username and password.
- Game state saving: The game state can be saved and loaded, allowing players to continue their game later.
- Top 20 list: The game keeps a list of the top 20 scores achieved by players.
- Undo/Redo: Players can undo and redo their moves.

## Files

- `UI.cpp` and `UI.hpp`: These files contain the `UI` class, which handles the game's user interface.
- `PlayerList.cpp` and `PlayerList.hpp`: These files contain the `PlayerList` class, which manages the list of players and their scores.
- `Board.cpp` and `Board.hpp`: These files contain the `Board` class, which manages the game board.
- `Player.cpp` and `Player.hpp`: These files contain the `Player` class, which represents a player.

## How to Run

To run the game, you need to have SFML library installed on your machine. Once you have SFML installed, you can compile and run the game using your preferred C++ compiler.
....
```
