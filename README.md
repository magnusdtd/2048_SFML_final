# 2048_SFML_final

**Student:** Đàm Tiến Đạt  
**ID:** 23120118  
**Class:** 23CTT2  
This project is part of the Programming Techniques course at HCMUS.

## Game Features

- **Friendly Graphics:** Tiles have differentiated colors based on their values. Newly generated tiles display "New".
- **Multiple Board Sizes:** Supports board sizes ranging from 4x4 to 10x10.
- **Score Tracking:** High scores are stored and updated continuously in a binary file.
- **Player Registration:** Players can register with a username and password for leaderboard display and future logins.
- **Game State Persistence:** Players can save and load their game state to continue playing later.
- **Top 20 Leaderboard:** Displays the top 20 high scores.
- **Undo/Redo Functionality:** Allows players to revert or repeat their moves.
- **Background Music and Sound Effects:** Enhances the gameplay experience with engaging audio.

## How to Play

### Controls

- **Arrow keys:** Move the tiles.
- **E:** Exit the game.
- **C:** Continue the game.
- **Y/N:** Save or not save the game when prompted.
- **U:** Undo a move.
- **R:** Redo a move.
- **X button:** Clickable only in the main menu, top20list, and settings.

### Objectives

- Combine two tiles of the same value to merge them into one with their total value.
- Aim to create a tile with the value of **2048**.
- The game ends when no more moves are possible.

### Player Names

- Should only contain A-Z, a-z, 0-9. No special characters or spaces are allowed.

### Background Music Controls

- Add any `.wav` file to the `music` folder to play it in-game.
- **/**: Toggle music on/off.
- **<** and **>**: Navigate through tracks.
- **-** and **+**: Adjust volume.

## Installation and Setup

Follow the guide at [SFML Setup](https://www.sfml-dev.org/tutorials/2.5/start-vc.php) and read below for additional instructions:

1. Clone the repository.
2. Open the project in Visual Studio.
3. Configure the SFML include and lib directories in the project properties:
   - For All Configurations:
     - **C++ -> General -> Additional Include Directories:** Add `$(SolutionDir)External\SFML\include`
     - **Linker -> General -> Additional Library Directories:** Add `$(SolutionDir)External\SFML\lib`
   - For Debug Configuration:
     - **Linker -> Input -> Additional Dependencies:** Add the following:
       - `sfml-graphics-d.lib`
       - `sfml-window-d.lib`
       - `sfml-audio-d.lib`
       - `sfml-network-d.lib`
       - `sfml-system-d.lib`
   - For Release Configuration:
     - **Linker -> Input -> Additional Dependencies:** Add the following:
       - `sfml-graphics.lib`
       - `sfml-window.lib`
       - `sfml-audio.lib`
       - `sfml-network.lib`
       - `sfml-system.lib`
4. Add music to the `music` folder in the project directory.
5. Build and run the project.
6. Enjoy the game!

# Evaluation Table

![EvaluationTable.png](https://github.com/magnusdtd/2048_SFML_final/blob/master/2048_SFML/EvaluationTable.png)
