# 2048 Game (C Console Application)

## 📌 Overview

This project is a console-based implementation of the classic **2048 puzzle game**, developed in **C**. It demonstrates core programming concepts including arrays, pointers, file handling, and structured game logic.

The player combines tiles with the same number to reach the **2048 tile**, while the game tracks moves, score, and player history.

---

## 🎮 Features

* 4×4 grid-based gameplay
* Movement using **arrow keys**
* Tile merging logic following standard 2048 rules
* Random tile generation after each move
* Game-over detection:

  * No empty cells
  * No possible merges
* Persistent storage of game results
* Top 3 player leaderboard
* Individual player game history (search feature)
* Console cursor control for cleaner UI

---

## 🧠 Core Game Logic

The game continues if at least one condition is satisfied:

* At least one empty cell exists (`0`)
* At least one valid merge is possible (adjacent equal tiles)

Otherwise, the game terminates.

---

## ⚙️ Technologies Used

* **Language:** C
* **Compiler:** GCC (MinGW recommended for Windows)
* **Libraries Used:**

  * `<stdio.h>` – input/output operations
  * `<stdlib.h>` – memory and random functions
  * `<time.h>` – random seed generation
  * `<string.h>` – string handling
  * `<conio.h>` – keyboard input handling (`_getch`)
  * `<windows.h>` – console cursor manipulation

---

## 🛠️ How to Compile

```bash
gcc 2048.c -o game.exe
```

---

## ▶️ How to Run

```bash
./game.exe
```

---

## 🎯 Controls

| Key           | Action     |
| ------------- | ---------- |
| ↑ Arrow       | Move Up    |
| ↓ Arrow       | Move Down  |
| ← Arrow       | Move Left  |
| → Arrow       | Move Right |
| Any other key | End Game   |

---

## 📂 File Structure

```
2048 Game/
│
├── 2048.c            # Main source code
├── 2048_Game.txt     # Stores player results (auto-generated)
└── README.md         # Project documentation
```

---

## 💾 Data Storage Format

Game results are stored in:

```
2048_Game.txt
```

Each entry follows:

```
PlayerName,Score,Moves
```

Example:

```
Umar,1280,45
```

---

## 🧪 Functional Modules

* `gamePlay()` → Controls game loop and input handling
* `pressedLeft/Right/Up/Down()` → Handles movement + merging logic
* `isGameContinue()` → Checks if game can continue
* `showTopThreePlayes()` → Displays leaderboard
* `gameInsights()` → Displays player-specific history

---

## ⚠️ Limitations

* Windows-only (due to `windows.h` and `conio.h`)
* No graphical interface (console-based UI)
* No input validation for menu options
* No undo or save-state functionality
* Fixed grid size (4×4)

---

## 🚀 Future Improvements

* Implement graphical interface (SDL2 / Raylib)
* Add undo functionality
* Improve input validation and error handling
* Add dynamic grid sizes (e.g., 5×5, 6×6)
* Introduce animations for tile movement
* Optimize movement and merge logic to reduce redundancy

---

## 👨‍💻 Author

**Umar Afzal**
BS Computer Science Student

---
