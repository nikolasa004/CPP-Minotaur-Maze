# C++ Minotaur Maze

A console-based maze game I made for my **Object-Oriented Programming 2** university course in December 2024. It combines procedural maze generation, a wandering (or pursuing) Minotaur, temporary item effects, and a few rather questionable decisions you can make while trying to escape.

What I am most pleased with is not the ASCII presentation, but the way I separated **maze generation into its own C++ static library**, with an abstract interface that makes it possible to implement other generation algorithms later. I also ended up adding a lot of small gameplay details beyond the original assignment, mainly because I wanted the result to feel like an actual little game rather than just a generated maze.

**[Watch the gameplay and features showcase on YouTube](https://youtu.be/Md7ivSq5eqg)**

## How the project started

The assignment was based on the Labyrinth of Knossos: generate a maze, let a robot navigate it, and place a Minotaur and several special items inside. The player could move using the keyboard, while the Minotaur was supposed to move **randomly**. Picking up an item would activate one of four temporary effects, and the game would save the final maze state to a file.

I had to research maze generation myself, and settled on **randomized depth-first search (DFS) with backtracking**. Rather than putting that implementation directly into the game, I decided to build a separate generation library. I wanted the game to depend on a general maze-generator interface, not on one particular algorithm.

Once the required parts worked, I kept experimenting. A purely random Minotaur was not especially threatening, so I gave it a harder mode. I added optional rooms, a score and leaderboard, a solution preview, illustrations for the items, and a collection of tiny interactions that are sometimes useful and sometimes just meant to catch the player off guard.

The original assignment and my additions are described in more detail in the **[project report (Serbian, DOC)](docs/Izvestaj.doc)**.

## Original requirements vs. my additions

| The assignment | What I added |
| --- | --- |
| Generate a maze with an entrance and an exit | Optional rooms and an extensible generation-library architecture |
| Control a robot using keyboard commands | Extra interactions, contextual messages, and ASCII artwork |
| Include a randomly moving Minotaur | A harder mode where the Minotaur tries to move toward the player |
| Add Sword, Shield, Hammer, and Fog of War effects | Rules for stacking certain effects, head injuries, and unusual escape attempts |
| Save the final state of a game | Scoring, a persistent Top 10 leaderboard, and an optional solution-path display |

The goal was never to turn the coursework into a large game. I just wanted to see how much personality and extra logic I could add while keeping the underlying implementation organized.

## Procedural maze generation

The maze is generated using **randomized DFS / recursive backtracking**. Starting from a cell, the algorithm chooses among unvisited neighbors, carves a passage, and backtracks when it reaches a dead end. The result is a maze that can be traversed from its entrance to its exit.

The program accepts the **maze height, width, and number of items** as command-line arguments. You can also choose whether rooms should be added. Rooms remove some internal walls, making the layout more open and changing the way you navigate it.

These two screenshots show **81 × 81** mazes - much larger than the ones used for the gameplay video.

| 81 × 81 maze **with rooms** | 81 × 81 maze **without rooms** |
| :---: | :---: |
| ![A large procedurally generated 81 by 81 ASCII maze with open rooms](docs/images/Screenshot%202026-10-24%20192621.png) | ![A large procedurally generated 81 by 81 ASCII maze without rooms](docs/images/Screenshot%202026-10-24%20192640.png) |

### A reusable generation library

This was the part I spent the most time thinking about from a software-design perspective.

The generation code lives in a **separate Visual Studio static-library project**, rather than being mixed into the game loop:

```text
MazeGenerator                  Abstract base class
    │
    └── DFSAlgorithm           Randomized DFS implementation

Maze game
    └── Maze                   Accepts a MazeGenerator interface
```

`MazeGenerator` contains the shared maze data and operations for placing the entrance, exit, player, Minotaur, and items; optionally adding rooms; and finding a route between the entrance and exit. It declares a **pure virtual `generateMaze()` method**.

`DFSAlgorithm` inherits from it and provides the actual generation algorithm. The game receives the generated data through the common interface. In principle, another algorithm - such as Prim's or Kruskal's - could be implemented as another derived class without rewriting the game's maze-management logic. Only DFS is implemented in this version; it is not a runtime plugin system.

The generator source code is included under `Project - Maze/LibrariesCode/`, while the game itself is under `Project - Maze/MazeProject/`.

## Gameplay and difficulty

The player is represented by a robot in an ASCII maze. You move one step at a time, try to reach the exit, collect useful items, and avoid the Minotaur - unless you happen to find a sword.

There are two enemy behaviors:

- **Normal mode:** the Minotaur moves randomly through available passages, as required by the assignment.
- **Hard mode:** the Minotaur favors available moves in the direction of the player, falling back to other possible moves when needed. This is a simple pursuit heuristic, **not** a full shortest-path search.

The difficulty also depends quite a bit on the maze layout and the number of items. A maze full of pickups can be surprisingly forgiving; the same maze with very few pickups can become difficult even when you know where the exit is.

### What is shown in the video?

In the [gameplay showcase](https://youtu.be/Md7ivSq5eqg), I used **21 × 21 mazes**, with **rooms enabled** and **Hard Mode** selected. That size was large enough to explore but still practical for a video.

I initially played with **20 items** scattered around the maze, which made useful abilities much easier to find. Some of the earlier attempts ended in victories thanks to fortunate Minotaur positions, useful pickups, and a bit of luck. Later, I reduced the count to **5 items**. With fewer opportunities to defend myself, the Minotaur eventually cornered me and I lost. That contrast is a good demonstration of how much the settings change the game.

## Items and abilities

There are four possible item effects. Each lasts for a limited number of turns, and the game displays a small ASCII illustration when an item is picked up.

| Item | Effect |
| --- | --- |
| **Sword** | Allows you to kill the Minotaur if you encounter it while the effect is active. |
| **Shield** | Protects you when the Minotaur attacks; the protection is consumed when it saves you. |
| **Hammer** | Lets you destroy a wall, including - perhaps unwisely - one of the outer walls. |
| **Fog of War** | Restricts visibility to a small **3 × 3** area around the player. Unlike the other pickups, this one is not necessarily helpful. |

I also added handling for holding or combining effects: the player can have up to **two active pickups from the Sword, Shield, and Hammer group**, including two of the same type. This can lead to some amusing messages, such as the game commenting on dual-wielded swords or hammers.

### Breaking walls with the Hammer

This screenshot shows the Hammer being collected, activated, and then used to remove a wall. Its effects are not limited to ordinary interior walls - and that becomes important when you try to escape through the boundary of the maze.

![Hammer pickup and the player destroying an ASCII maze wall](docs/images/Screenshot%202026-10-24%20192900.png)

### Fog of War

Fog of War hides most of the map and shows only the nearby area while it remains active. I liked the idea of a supposedly useful pickup that could actually make the situation worse.

![Fog of War pickup progressively restricting visibility to the area around the player](docs/images/Screenshot%202026-10-24%20193006.png)

### Shield - collecting it and actually using it

| Picking up the Shield | The Shield saves the player |
| :---: | :---: |
| ![ASCII shield illustration displayed after collecting the Shield item](docs/images/Screenshot%202026-10-24%20193112.png) | ![The Minotaur attacks the player but consumes the active Shield instead](docs/images/Screenshot%202026-10-24%20194034.png) |

### Sword - fighting back

The Sword changes the encounter from certain danger into an opportunity. If you reach the Minotaur with the effect active, you can kill it and then continue searching for a way out.

![ASCII sword illustration followed by the player killing the Minotaur](docs/images/Screenshot%202026-10-24%20193435.png)

## The little extras I couldn't resist adding

I had the most fun with the small situations that were not necessary for the original assignment.

**Running into a wall can knock you unconscious.** Instead of always ignoring an invalid move, the game can make the robot lose **1–4 turns**, during which the Minotaur continues moving. That is a particularly bad time to make a mistake in Hard Mode.

![The player hits a wall and loses several turns after being knocked unconscious](docs/images/Screenshot%202026-10-24%20193147.png)

There is also a **1% chance that the Minotaur changes its mind** when it would otherwise eat you. This is intentionally rare, but I thought it would make for a memorable surprise if anyone ever encountered it.

The game has different messages depending on who runs into whom, what item is active, and how you decide to leave the maze. I added these partly for humor and partly because I wanted the choices to feel as though they had consequences.

### A hole in the wall is not necessarily a victory

One of my favorite additions involves the Hammer. You can use it to break through the **outer wall** and leave the maze without finding the actual exit. But if the Minotaur is still alive, it can escape too - and the game treats that as **a loss**. If you have already killed the Minotaur, escaping this way counts as a win.

The **alternative escape defeat** is shown alongside the other endings below.

## Winning, losing, and keeping score

Reaching the proper exit wins the game **even if the Minotaur is still alive**. Killing the Minotaur first is optional, but it improves the result. On the other hand, walking straight into it without a Sword - or being caught without a Shield - can end your run immediately.

| Defeat: headbutting the Minotaur | Victory: killed the Minotaur and escaped |
| :---: | :---: |
| ![Defeat screen with a Minotaur illustration after the player walks into it](docs/images/Screenshot%202026-10-24%20193302.png) | ![Victory screen after killing the Minotaur, including the player's score and solution path](docs/images/Screenshot%202026-10-24%20193534.png) |
| **Victory through the normal exit** | **The alternative escape goes wrong** |
| ![Victory message after reaching the normal maze exit without killing the Minotaur](docs/images/Screenshot%202026-10-24%20194459.png) | ![Defeat after leaving through a demolished wall without killing the Minotaur](docs/images/Screenshot%202026-10-24%20193742.png) |

At the end of a completed run, `ScoreRecorder` calculates a score using the **maze area, number of items, moves, items collected and used, elapsed time, whether the Minotaur was killed, and whether the game was won**. Killing the Minotaur and winning the game both increase the score significantly.

The final maze state and score breakdown are written to a **timestamped text file**. I also created a persistent **Top 10 leaderboard**. If you earn a qualifying score, you can enter your name and have the result saved.

After a game finishes, you can optionally display the **path from the entrance to the exit**. I especially wanted this for large mazes, where it is easy to wonder how close you actually came to solving them.

## A little about the code

Besides the generation library, I tried to keep the game's responsibilities separated instead of putting everything in one file:

- **`Maze`** - holds the current maze, handles movement, encounters, enemy behavior, item interactions, and victory/defeat conditions.
- **`ItemEffect`** - common abstract interface for item messages and their remaining duration; `Sword`, `Shield`, `Hammer`, and `FogOfWarEffect` provide the specific effects.
- **`ScoreRecorder`** - tracks the parameters of a run and calculates its final score.
- **`Leaderboard`** - reads, updates, and stores the Top 10 scores.
- **`FileManager`** - creates folders and writes the saved results to text files.
- **`MazeProject.cpp`** - the entry point, argument handling, setup questions, and main game loop.

The whole application is text-based. The maze is represented with a two-dimensional character grid, and the interface uses keyboard input and ASCII output. This let me focus more on the algorithms, object-oriented structure, and game rules than on rendering.

### Testing and performance

The original report includes manual tests for input validation, maze generation, room and item placement, player/enemy interactions, end-game conditions, saving results, and updating the leaderboard. It also includes generation-time measurements for different maze sizes and item counts.

For example, these are **historical measurements from my December 2024 report**, not new benchmarks:

| Maze and items | Recorded generation time |
| --- | ---: |
| 15 × 15, 3 items | 0.0004 s |
| 60 × 60, 3 items | 0.004 s |
| 120 × 120, 3 items | 0.015 s |
| 240 × 240, 3 items | 0.07 s |
| 240 × 240, 20,000 requested items | 0.9 s |

The report discusses how generation time increases with the size of the maze and especially with the number of items. These timings are simply a record of the experiments I ran at the time.

## Running the project

The code was developed in **Visual Studio**, with one solution for the static library and another for the game. It has **not** been converted into a single modern build configuration, so a little manual setup may be needed on another computer.

1. Install Visual Studio with **Desktop development with C++**.
2. Clone or download the repository.
3. Open `Project - Maze/LibrariesCode/MazeGenerator/MazeGenerator.sln` and build the **MazeGenerator** static library for the platform/configuration you intend to use.
4. Place the produced `MazeGenerator.lib` in `Project - Maze/Libraries/lib/` (create the `lib` directory if needed).
5. Open `Project - Maze/MazeProject/MazeProject.sln`. If Visual Studio cannot resolve a header or library, update the project's **Include Directories** and **Library Directories** to point to the repository's `Libraries/include/` and `Libraries/lib/` directories. One configuration in the original project also contains a machine-specific include path.
6. Build the game using a compatible platform and configuration.
7. Set the command-line arguments in **Project Properties → Debugging → Command Arguments**, for example:

   ```text
   21 21 20
   ```

   These represent the **maze rows, maze columns, and number of items**. Dimensions must be at least 15 and the item count at least 3. Invalid or missing arguments fall back to a 21 × 21 maze with 3 items.
8. Run the console application. Choose Normal/Hard Mode and whether to include rooms.

The controls are `w` (up), `a` (left), `s` (down), and `d` (right). Uppercase `Q` quits. Use a monospaced terminal font, especially for the larger mazes and ASCII illustrations.

**Working directory:** the program uses relative paths (`../../Results` and `../../Leaderboard`) for saved files. When running from Visual Studio, keep the working directory set to the game project directory (`Project - Maze/MazeProject/MazeProject/`) for those paths to resolve as intended.

## Repository structure

```text
CPP-Minotaur-Maze/
├── Project - Maze/
│   ├── Libraries/
│   │   └── include/                 # Public generator headers
│   ├── LibrariesCode/
│   │   └── MazeGenerator/           # Static-library solution and source
│   │       ├── MazeGenerator.sln
│   │       └── MazeGenerator/
│   │           ├── MazeGenerator.h / .cpp
│   │           └── DFSAlgorithm.h / .cpp
│   ├── MazeProject/
│   │   ├── MazeProject.sln
│   │   └── MazeProject/
│   │       ├── MazeProject.cpp      # Main program
│   │       ├── Maze.h / .cpp
│   │       ├── ItemEffect.h
│   │       ├── Sword, Shield, Hammer, FogOfWarEffect
│   │       ├── ScoreRecorder.h / .cpp
│   │       ├── Leaderboard.h / .cpp
│   │       └── FileManager.h / .cpp
│   ├── Results/                      # Example saved runs
│   └── Leaderboard/                  # Example leaderboard data
├── docs/
│   ├── Izvestaj.doc                  # Original university report (Serbian)
│   └── images/                       # Screenshots
├── .gitignore
└── README.md
```

## Final thoughts

This is an earlier university project, and I have intentionally kept it close to the way I wrote it. The Minotaur's Hard Mode is not advanced pathfinding, the console interface is basic, some interactions are deliberately silly, and there are opportunities to improve input handling and the build setup.

Still, I am happy with how much I managed to fit into it: a maze-generation library designed around abstraction, a complete little game on top of it, optional difficulty and layouts, items that can change the outcome of a run, and a score system that records what happened. What started as a maze assignment turned into something I enjoyed experimenting with well beyond the minimum requirements.
