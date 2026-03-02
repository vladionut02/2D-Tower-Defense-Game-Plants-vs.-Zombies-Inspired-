# 2D-Tower-Defense-Game-Plants-vs.-Zombies-Inspired-

This project is a 2D tower defense game inspired by *Plants vs. Zombies*, built using the OpenGL-based GFX Framework.

The game implements a lane-based defense system where the player collects resources and strategically places units on a grid to defend against incoming enemies.

It was developed as part of the Computer Graphics coursework at Politehnica University of Bucharest.

---

## Game Description

The game is structured around three main components:

• A resource system (stars)  
• A unit placement system (diamonds)  
• An enemy spawning system (hexagons)  

Stars spawn periodically at random positions. The player can click on them to collect resources.

Using those resources, the player can drag and place different types of units on a 3x3 grid. Units are placed via a simple drag-and-drop mechanic.

Enemies spawn randomly on one of three horizontal lanes and move toward the defensive grid.

---

## Technical Details

- Implemented in C++ using the GFX Framework (OpenGL)
- Orthographic 2D camera (1280x720 resolution)
- Custom procedural mesh generation (squares, diamonds, hexagons, rectangles)
- Mouse-based input handling
- Axis-Aligned Bounding Box (AABB) collision detection for star selection
- Basic resource tracking and spawn timing logic

Mouse coordinates are converted to scene space using:

    y = 720 - mouseY

---

## Project Structure

src
    main.cpp
    lab_m1
        Tema1
            Tema1.cpp
            Tema1.h
            object2D.cpp
            object2D.h
            transform2D.h

assets
    models
        meshes
            star.obj

---

## Build & Run

The project uses CMake.

Windows:
- Generate the project with CMake
- Open build/GFXFramework.sln
- Build and run
- The scene m1::Tema1 launches by default

Linux / macOS:

    mkdir -p build
    cd build
    cmake ..
    cmake --build . -j
    ./GFXFramework

If dependencies are missing, check the scripts in the tools/ directory.

---

## Possible Improvements

Future extensions could include:
- Enemy health and combat interactions
- Projectile mechanics
- Animations
- Win/Lose conditions
- Difficulty scaling

---

## Author

Vlad Vârzaru
