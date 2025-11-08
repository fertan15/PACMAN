# 🎮 Pac-Man Console Game

![Gameplay Screenshot 1](https://github.com/user-attachments/assets/2ea55f4a-55da-4c00-a759-ba4a05768ca8)
![Gameplay Screenshot 2](https://github.com/user-attachments/assets/f8e3c8cc-ca54-4696-b34f-18e45aa2ff2f)

A recreation of the classic **Pac-Man arcade game**, developed using **pure C++**.  
This game runs entirely in the **Windows Console**, leveraging ASCII graphics and the **Windows Console API** for real-time rendering and input.

---

## 📝 Introduction

The **Pac-Man Console Game** is designed as a simple yet engaging project to strengthen programming fundamentals through game development.  
It combines essential C++ concepts such as loops, conditionals, arrays, functions, file handling, and basic AI.

### Core Mechanics
- Navigate the maze to eat pellets.
- Avoid ghosts — unless you’re powered up!
- Collect high scores, stored in a persistent leaderboard.

---

## 🕹️ Gameplay

- **Controls:** Use **W, A, S, D** keys to move Pac-Man.
- **Ghosts:** Four ghosts roam the maze. Colliding with one ends the game (unless powered up).
- **Power Pellets:** Found in maze corners; they turn ghosts blue and make them edible (+1000 points each).
- **Side Tunnels:** Warp between the left and right sides of the maze.
- **Stages:**
  - **Stage 1:** Random ghost AI (Easy)
  - **Stage 2:** Chase/Flee AI (Hell Mode)
- **Game End:** Win by eating all pellets or lose when caught by a ghost.

---

## ✨ Features

✅ **Classic Pac-Man Gameplay** – Authentic maze and pellet mechanics  
✅ **Two Difficulty Stages** – Random vs Chase/Flee AI  
✅ **Power Pellets** – Temporarily reverse the hunter/prey dynamic  
✅ **Scoring System**
  - +100 per regular pellet  
  - +1000 per ghost eaten  
  - +5000 bonus on completing Stage 1  
✅ **Persistent Leaderboard** – Saves top scores to `leaderboard.txt`  
✅ **Interactive Menu** – Start game, view leaderboard, or exit  
✅ **ASCII Graphics** – Rendered with ANSI colors and characters  

---

## ⚙️ Technical Details

### Code Structure

| Function | Description |
|-----------|-------------|
| `main()` | Entry point; handles menu navigation |
| `menu()` | Displays and manages the main menu |
| `play()` | Core game loop, loads both stages |
| `printMap()` | Draws the maze in ASCII |
| `move_pacman()` | Handles player input and movement (including tunnels) |
| `move_ghost()` | Random ghost logic (Stage 1) |
| `move_ghost_hard()` | Chase/Flee ghost logic (Stage 2) |
| `isCollide()` | Detects Pac-Man vs Ghost collision |
| `cek_pacman()` | Updates score and handles power-up activation |
| `upload_score()` / `view_leaderboard()` | Handles score saving and viewing (File I/O) |
| `gotoxy()` | Utility for cursor positioning in the console |


---

## 🛠️ How to Compile and Run

### 🧩 Prerequisites
- **Operating System:** Windows  
- **Compiler:** Any C++11-compatible compiler (e.g. MinGW-w64 g++, Visual Studio)  
- **Library:** `winmm.lib` (for `Beep` function and Windows Console APIs)

### ⚙️ Steps (Using MinGW/g++)
1. **Save the file** as `pacman_game.cpp`
2. **Open Command Prompt** in the file directory
3. **Compile the code:**
   ```bash
   g++ pacman_game.cpp -o pacman.exe -lwinmm
```

Run the game:

./pacman.exe

🎯 Learning Outcomes

By completing this project, you’ll gain practical experience in:

C++ syntax and structure (loops, arrays, conditionals, structs)

Modular programming and function decomposition

File handling (fstream) for persistent data

Real-time input handling (_kbhit, _getch)

Console rendering using windows.h and gotoxy

Basic AI with simple FSM (Finite State Machine) behavior

📄 License

This project is open-source and free to use for educational or personal purposes.
Feel free to modify and expand it!

💡 Author’s Note

This project was made as a fun and educational way to explore classic game design using only C++ — proving that great gameplay doesn’t need fancy graphics!
