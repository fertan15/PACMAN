
---

# Pac-Man Console Game

A classic Pac-Man game recreation developed in C++ that runs in the Windows console. This project brings the arcade favorite to life with familiar gameplay mechanics, including navigating a maze, eating pellets, avoiding ghosts, and chasing high scores.

##  Gameplay
The player controls Pac-Man through a maze, with the objective of eating all the pellets on the screen. Four ghosts roam the maze, trying to catch Pac-Man. If a ghost touches Pac-Man, the game is over.

There are special "power pellets" located in the corners of the maze. When Pac-Man eats one of these, the ghosts temporarily turn blue and become vulnerable. Pac-Man can then eat the ghosts for extra points, and they will respawn in their starting box.

The game also features the classic side tunnels, allowing Pac-Man and the ghosts to teleport from one side of the maze to the other.

## Features

- **Classic Pac-Man Gameplay**: Experience the traditional Pac-Man maze and objectives.
- **Player Controls**: Move Pac-Man using the W, A, S, and D keys.
- **Ghost AI**: Ghosts move randomly around the maze, providing a constant challenge. An unimplemented "Hell Mode" in the code suggests a more advanced chasing AI.
- **Power Pellets**: Turn the tables on the ghosts by eating power pellets to make them vulnerable.
- **Scoring System**:
    - `100 points` for each regular pellet.
    - `1000 points` for eating a ghost.
- **Persistent Leaderboard**: Your score is saved to a `leaderboard.txt` file. You can view the top 5 high scores from the main menu.
- **Interactive Menu**: A simple and intuitive menu to start the game, view the leaderboard, or exit.
- **Console Graphics**: The game uses ASCII characters and Windows Console API for colors and cursor positioning to render the game board and characters.

## How to Compile and Run

This project is designed for a Windows environment and requires a C++ compiler that supports the C++11 standard or newer (for features like lambda functions). A popular choice is MinGW (g++).

### Prerequisites
- A C++ compiler (like g++ from MinGW-w64).
- Windows Operating System.

### Compilation Steps
Of course, here is a simpler guide.

---

## How to Compile and Run

### Using an IDE (like Visual Studio)

1.  **Create Project**: Create a new "Console App" project in your IDE.
2.  **Add Code**: Copy and paste your code into the main `.cpp` file created by the IDE (or add your existing file to the project).
3.  **Link Library**: This is the most important step.
    *   Go to your project's **Properties**.
    *   Find the **Linker** -> **Input** section.
    *   In **Additional Dependencies**, add `winmm.lib`.
4.  **Clone Repository**: or instead of doing step 1,2,3 you can just clone this repository and open it in your code editor.
5.  **Run**: Press **Ctrl+F5** or click the "Start Without Debugging" button to compile and run the game.


## Controls

-   **W**: Move Up
-   **S**: Move Down
-   **A**: Move Left
-   **D**: Move Right
-   **Enter**: Select option in the menu

## Code Structure

The code is organized into several key functions:

-   `main()`: The main game loop which handles menu navigation and calls the play function.
-   `play()`: Contains the primary logic for a single game session, including initializing characters, handling movement, and checking for win/loss conditions.
-   `menu()`: Displays the main menu and handles user navigation.
-   `printMap()`: Renders the game board to the console using ASCII characters.
-   `move_pacman()`: Handles player input and updates Pac-Man's position.
-   `move_ghost()`: Implements a simple random movement AI for the ghosts.
-   `move_ghost_hard()`: (Commented out) An alternative, more aggressive AI where ghosts chase Pac-Man.
-   `isCollide()`: Checks for collisions between Pac-Man and ghosts.
-   `isWin()`: Checks if all pellets have been eaten.
-   `cek_pacman()`: Manages scoring and power-pellet effects when Pac-Man moves to a new tile.
-   `upload_score()` / `view_leaderboard()`: Functions to save player scores to `leaderboard.txt` and display them.
-   `gotoxy()`: A utility function to control the cursor position in the Windows console.



make the compile tutorial in vscode or ide
