# 2D-Tower-Defense-Game-Plants-vs.-Zombies-Inspired-

A 2D tower-defense style game built using the **GFX Framework (OpenGL-based)**, inspired by the mechanics of *Plants vs. Zombies*.

The project implements a lane-based defense system where the player collects resources and strategically places units to defend against incoming enemies.

> Developed as part of the Computer Graphics coursework at Politehnica University of Bucharest.

---

## 🎮 Game Overview

This project is a **Plants vs. Zombies–style 2D game**, featuring:

- Resource generation and collection system  
- Drag-and-drop unit placement  
- Lane-based enemy spawning  
- Real-time interaction using mouse input  
- Custom 2D mesh generation (no external sprites)

The default launched scene is `m1::Tema1`.

---

## 🧠 Core Mechanics

### ⭐ Resource System
- Stars spawn periodically at random positions.
- Clicking a star collects it and increases the resource counter.
- Resources are displayed in a currency-style UI in the top-right corner.

### 💎 Unit Placement
- Four different unit types (diamonds) are available in the top “shop” area.
- Units can be dragged and placed on a 3x3 grid.
- Placement is validated per grid cell.

### ⬡ Enemy System
- Hexagon-shaped enemies spawn randomly on one of three lanes.
- Each enemy receives a random color.
- Enemies move horizontally toward the defensive grid.

---

## 🏗 Technical Implementation

### Graphics & Rendering
- OpenGL-based rendering via GFX Framework
- Orthographic 2D camera (1280x720 resolution)
- Custom procedural mesh generation:
  - Squares
  - Diamonds
  - Hexagons
  - Rectangles

### Input Handling
- Mouse-based interaction:
  - Star collection via click
  - Drag-and-drop unit placement
- Coordinate transformation:
  ```cpp
  y = 720 - mouseY;
