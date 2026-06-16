# Memory Matching Game in C++

An interactive, terminal-based Memory Matching Game implemented in C++ using Object-Oriented Programming (OOP) design. This project is structured specifically to showcase foundational coding techniques and core **Data Structures and Algorithms (DSA)** concepts for academic evaluation.

---

## How to Compile and Run

To compile and run this program, you will need a C++ compiler supporting the C++17 standard (such as `g++`).

### Compilation Command:
```bash
g++ -std=c++17 main.cpp Game.cpp Board.cpp Player.cpp ScoreManager.cpp -o memory_game
```

### Run Command:
```bash
./memory_game
```

---

## Data Structures and Algorithms (DSA) Concepts Showcased

1. **Dynamic Grid Structures (2D Vectors)**:
   - Represented using a nested vector `std::vector<std::vector<Card>>`. This allows dynamic configuration of grid sizes (4x4, 8x8, 16x16) at runtime without hardcoded dimensions or static sizing penalties, demonstrating safe heap memory allocation.

2. **Shuffle and Randomization Algorithms**:
   - Card values are randomly distributed using standard algorithms (`std::shuffle` from `<algorithm>`).
   - Relies on system-clock seed generation (`std::chrono::system_clock::now().time_since_epoch().count()`) to feed the random number engine (`std::default_random_engine`), demonstrating the implementation of pseudo-randomization routines.

3. **Sorting & Leaderboards (Comparative Vectors)**:
   - High scores are managed inside a dynamic collection sorted using custom comparator lambdas.
     ```cpp
     std::sort(scores.begin(), scores.end(), [](const ScoreRecord& a, const ScoreRecord& b) {
         if (a.score != b.score) return a.score > b.score;
         if (a.moves != b.moves) return a.moves < b.moves;
         return a.timeTaken < b.timeTaken;
     });
     ```
   - Demonstrates insertion sorting, ranking lists, and collection resizing.

4. **Multiplayer State Coordination**:
   - Manages an array of players (`std::vector<Player>`) and active index tracking (`activePlayerIdx`) to coordinate alternating turns and statistics (moves, score, matches) independently, illustrating state-machine algorithms.

5. **File Serialization and I/O Handling**:
   - Uses `std::ifstream` and `std::ofstream` to serialize records with a custom string parsing technique (using `std::stringstream` and delimiter `'|'`), showcasing file handling and stream state evaluation.

6. **Robust Input Validation & User Interaction**:
   - Clears input buffers on erroneous inputs (`std::cin.clear()` and `std::cin.ignore()`) to prevent infinite terminal loops, showing safe validation controls.

---

## Sample Terminal Output (Academic Report Ready)

### 1. Welcome Screen
```text
=========================================================
||                                                     ||
||             WELCOME TO MEMORY MATCHING GAME         ||
||                                                     ||
=========================================================
  A C++ project illustrating basic Data Structures and
  Algorithms: Vector representation, Shuffling, and File IO.
=========================================================

=== MAIN MENU ===
1. Start New Game
2. View Instructions
3. View High Scores
4. Exit
Enter choice: 1
```

### 2. Game Mode & Player Selection (Two-Player)
```text
Select Game Mode:
1. Single-Player
2. Two-Player
Enter choice: 2

Enter Player 1 name: Alice
Enter Player 2 name: Bob

Choose Difficulty:
1. Easy (4x4 board, 8 pairs)
2. Medium (8x8 board, 32 pairs)
3. Hard (16x16 board, 128 pairs)
Enter choice: 1

Generating a random board...
```

### 3. Gameplay Turns & Board View
```text
     1   2   3   4 
     -----------------
  1 |   *|   *|   *|   *|
     -----------------
  2 |   *|   *|   *|   *|
     -----------------
  3 |   *|   *|   *|   *|
     -----------------
  4 |   *|   *|   *|   *|
     -----------------

===  [Turn: Alice]  ===
Enter Row and Column for card 1: 1 2
```

```text
     1   2   3   4 
     -----------------
  1 |   *|   5|   *|   *|
     -----------------
  2 |   *|   *|   *|   *|
     -----------------
  3 |   *|   *|   *|   *|
     -----------------
  4 |   *|   *|   *|   *|
     -----------------

===  [Turn: Alice]  ===
Enter Row and Column for card 2: 3 1
```

If matching cards are chosen:
```text
     1   2   3   4 
     -----------------
  1 |   *|   5|   *|   *|
     -----------------
  2 |   *|   *|   *|   *|
     -----------------
  3 |   5|   *|   *|   *|
     -----------------
  4 |   *|   *|   *|   *|
     -----------------

Match found! Card 5 matches. Alice gets another turn!
Press Enter to continue...
```

If mismatch happens:
```text
     1   2   3   4 
     -----------------
  1 |   *|   5|   *|   *|
     -----------------
  2 |   *|   *|   *|   *|
     -----------------
  3 |   2|   *|   *|   *|
     -----------------
  4 |   *|   *|   *|   *|
     -----------------

No match! Card 1 was: 5, Card 2 was: 2.
Press Enter to continue...
(Turn passes to Bob)
```

### 4. Game Over & Results (Two-Player Winner Announcement)
```text
=========================================================
                    GAME OVER RESULTS                    
=========================================================
Difficulty:  Easy
Time Taken:  76.5 seconds
---------------------------------------------------------
Player Name    Moves     Matches   Score
---------------------------------------------------------
Alice          9         5         197
Bob            7         3         167
---------------------------------------------------------
Winner: Alice 🎉
=========================================================

Scores have been saved to the high scores list!

Press Enter to return to the Main Menu...
```
