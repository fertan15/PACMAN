# 🎮 Pac-Man Console Game  

<img width="1099" height="662" alt="image" src="https://github.com/user-attachments/assets/2ea55f4a-55da-4c00-a759-ba4a05768ca8" />
<img width="1099" height="662" alt="image" src="https://github.com/user-attachments/assets/f8e3c8cc-ca54-4696-b34f-18e45aa2ff2f" />


A recreation of the classic **Pac-Man arcade game**, developed in **C++** as part of a Programming Fundamentals project.  
This game runs entirely in the **Windows console**, using ASCII graphics and the Windows Console API for rendering.  

The project demonstrates fundamental programming concepts, including structured programming, file handling, basic AI, and interactive gameplay mechanics. Players can relive the retro experience of guiding Pac-Man through a maze, eating pellets, avoiding ghosts, and chasing high scores.  

---

## 📝 Introduction  

The **Pac-Man Console Game** is designed as a beginner-friendly project to strengthen understanding of programming fundamentals through game development. It combines essential concepts such as loops, conditionals, arrays, functions, file handling, and simple AI into a fun, interactive application.  

The game faithfully recreates the core mechanics of Pac-Man:  
- Navigate the maze to eat pellets.  
- Avoid the ghosts unless powered up by a special pellet.  
- Score points for each pellet and ghost eaten.  
- Compete for the top spot on the **persistent leaderboard**.  

This project highlights the integration of **game logic**, **user interaction**, and **file-based data persistence**, making it a comprehensive example of applied programming fundamentals.  

---

## 🕹️ Gameplay  

- The player controls Pac-Man using the **W, A, S, D keys** to move up, left, down, and right.  
- Four ghosts roam the maze with random movement patterns. If Pac-Man collides with a ghost, the game ends.  
- Special **power pellets** are placed in the maze corners. Eating one makes ghosts vulnerable (turning them blue), allowing Pac-Man to eat them for bonus points.  
- **Side tunnels** allow Pac-Man and ghosts to teleport between the left and right sides of the maze, just like in the original arcade version.  
- The game ends either when all pellets are eaten (**win**) or when Pac-Man is caught by a ghost (**loss**).  

---

## ✨ Features  

- **Classic Pac-Man Gameplay**: Authentic maze, pellet-eating, ghost-chasing mechanics.  
- **Player Controls**: Smooth navigation with `W`, `A`, `S`, `D` keys.  
- **Ghost AI**: Random movement logic with potential for expansion (includes a commented “Hell Mode” ghost-chasing AI).  
- **Power Pellets**: Temporarily reverse roles—Pac-Man hunts the ghosts!  
- **Scoring System**:  
  - `+100 points` per regular pellet.  
  - `+1000 points` per ghost eaten.  
- **Persistent Leaderboard**: Stores scores in `leaderboard.txt` and displays the **Top 5 high scores**.  
- **Interactive Menu**: Start the game, view leaderboard, or exit.  
- **ASCII Graphics**: Characters and walls drawn with symbols; colored output using the Windows Console API.  

---

## ⚙️ Technical Details  

### Code Structure  

The project is modularized into several core functions:  
- **`main()`**: Game entry point; handles menu navigation.  
- **`menu()`**: Renders and manages the main menu.  
- **`play()`**: Core game loop for a single session.  
- **`printMap()`**: Renders the maze using ASCII graphics.  
- **`move_pacman()`**: Handles player input and Pac-Man’s movement.  
- **`move_ghost()`**: Implements simple random AI for ghosts.  
- **`move_ghost_hard()`**: (Optional) More advanced AI for aggressive ghost chasing.  
- **`isCollide()`**: Detects collisions between Pac-Man and ghosts.  
- **`isWin()`**: Checks if all pellets have been collected.  
- **`cek_pacman()`**: Updates score and applies power-pellet effects.  
- **`upload_score()` / `view_leaderboard()`**: Save scores to file and display rankings.  
- **`gotoxy()`**: Utility for cursor positioning in the console.  

---

## 🛠️ How to Compile and Run  

### Prerequisites  
- **Operating System**: Windows  
- **Compiler**: C++11-compatible compiler (e.g., MinGW-w64 `g++`)  
- **Library**: `winmm.lib` (for Windows console handling)  

### Steps Using Visual Studio IDE  
1. **Create Project**: Start a new *Console App* project.  
2. **Add Code**: Copy/paste or import the `.cpp` source file.  
3. **Link Library**:  
   - Go to **Project Properties** → **Linker** → **Input**.  
   - Add `winmm.lib` under **Additional Dependencies**.  
4. **Run**: Build and start the project (`Ctrl + F5`).  

### Alternative: Clone and Run  
```bash
git clone https://github.com/fertan15/PACMAN
cd pacman-console-game
g++ pacman.cpp -o pacman.exe -lwinmm
./pacman.exe
```

## 🎯 Learning Outcomes

By completing this project, students will gain hands-on experience with:
- Core C++ syntax (loops, conditionals, arrays).
- Functions & modular programming.
- Structs for character representation.
- File handling for saving and retrieving leaderboard scores.
- Random number generation for ghost AI.
- Real-time input handling (_kbhit, _getch).
- Console rendering techniques.
