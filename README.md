# N-Body Gravitational Simulator

A real-time gravitational n-body simulator built from scratch in C++ and OpenGL. Every body exerts a gravitational force on every other body each timestep, producing emergent orbital dynamics ranging from stable choreographies to chaotic scattering.

Physics are computed in double precision using Velocity Verlet integration, a symplectic integrator that conserves energy over long timescales — making it well suited for stable orbit simulation. The simulator tracks total system energy and drift in real time, providing a live measure of numerical accuracy.

Figure 8 orbit:
<img width="1280" height="720" alt="figure 8" src="https://github.com/user-attachments/assets/4bc34982-7f57-4cd7-8486-1fa2be4c2140" />



---

## Features

- Velocity Verlet integration with double precision physics
- Real-time energy conservation tracking with drift percentage display
- Six preset configurations including documented periodic orbits
- Interactive control panel built with Dear ImGui
- Per-body position, velocity, and mass editing in real time
- Add bodies to the simulation at runtime
- Pause, reset, and adjustable simulation speed
- Colored trails per body with axis reference lines
- Orbit camera with mouse controls

---

## Presets

**Default** — a simple starting configuration for free exploration

**Figure-8 Choreography** — three equal masses tracing a stable figure-eight path.

**Lagrange Triangle** — three equal masses at the vertices of an equilateral triangle, rotating about their shared center of mass.

**Broucke Orbit** — a periodic three-body orbit from the Broucke-Hadjidemetriou-Henon family of solutions, characterized by two bodies oscillating along an axis while a third orbits around them.

**3D Orbit** — a three-dimensional periodic orbit demonstrating out-of-plane gravitational dynamics.

**Pentagon Orbit** — five bodies locked in a periodic pentagonal choreography.

---

## Technical Details

**Language:** C++17

**Rendering:** OpenGL 3.3 Core Profile, GLFW, GLAD

**Math:** GLM (all physics computed in double precision, cast to float for GPU upload)

**UI:** Dear ImGui

**Integration:** Velocity Verlet — a symplectic integrator that splits the velocity update into two half-kicks around the force computation. This preserves the phase-space structure of the Hamiltonian system, preventing the systematic energy drift that affects non-symplectic methods like RK4 over long simulations.

**Force model:** Softened Newtonian gravity computed for every unique body pair each timestep. Force magnitude follows F = G * m1 * m2 / (r^2 + epsilon^2), where epsilon is a softening parameter that prevents numerical singularities at close range.

**Energy tracking:** Total mechanical energy (KE + PE) is computed each frame and compared against the initial value to produce a drift percentage. On stable presets like the figure-8, drift remains at or near 0% indefinitely.

---

## Build Instructions

### Prerequisites

- Windows
- Visual Studio 2022
- vcpkg

### Installing dependencies

From your vcpkg directory, run:

```
.\vcpkg install glfw3:x64-windows
.\vcpkg install glad:x64-windows
.\vcpkg install glm:x64-windows
.\vcpkg install imgui[glfw-binding,opengl3-binding]:x64-windows
.\vcpkg integrate install
```

### Building

1. Clone the repository
2. Open the solution file in Visual Studio 2022
3. Set configuration to Debug or Release, x64
4. Build and run

---

## Controls

**Left mouse drag** — rotate camera

**Right mouse drag** — pan camera

**Scroll wheel** — zoom

**Pause checkbox** — pause and resume simulation

**Speed slider** — control simulation speed without affecting timestep accuracy

**Reset button** — reload current preset

**Body headers** — expand to edit position, velocity, and mass of individual bodies in real time

**Add Body** — insert a new body into the simulation at runtime

---

## Demos

3D orbit and camera controls:
<img width="800" height="450" alt="3D and camera controls" src="https://github.com/user-attachments/assets/a41076a6-936a-46fa-a5cf-7a7adb09d1df" />

Brouche orbit and add body feature

<img width="1280" height="720" alt="brouche and add body" src="https://github.com/user-attachments/assets/854af6a7-18df-4693-bb03-cccf4118def8" />

Lagrange orbit

<img width="1280" height="720" alt="lagrange" src="https://github.com/user-attachments/assets/3fa29187-808d-430d-8a4c-38ca6452e592" />

Pentagon orbit and adjust speed slider

<img width="1280" height="720" alt="pentagon and speed slider" src="https://github.com/user-attachments/assets/4ab421d3-569e-4586-b169-7d7e2ff4b8a3" />


