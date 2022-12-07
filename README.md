# LanaEngine


# About:
Lanna engine is a 3D Game Engine developed during the Game Engines classes. We are making to make an Engine that can be used to develop all kinds of games.


# Features:
- Street is automatically loaded at the start.
- FBX model loading
- PNG texture loading
- Inspector: displays information about the components of the selected GameObject.
- Transform: Shows position, rotation, and scale for the selected GameObject.
- Mesh: information about the loaded mesh. 
- Texture: display texture size and path.
- Drag&drop of FBX files.
- Drag&drop of DDS/PNG files.
- Each GameObject has 3 display components: Transform, Mesh, and Texture.
- Game objects can be picked from the world using the mouse.
- Start / Pause / Stop the simulation.
- Custom file format.
- Modify a Game Object: translate, rotate and scale, delete, reparent, create empty, select any imported mesh, select any imported
 texture and create children, camera can be modified.
- Models, meshes, and textures are saved to our own format.
- The editor has 2 windows one with the scene(editor view) and another captured from a
game object with a camera component(main game camera), each one has its own
framebuffer and the user can visualize both at the same time.
- Resource Management:
- Assets window shows all user assets.
- Import new files. 



# Editor Windows:
- Console: the window LOG the process from ASSIMP and the external libraries' initialization process.
- Configuration includes:
- A graph for the frames per second.
- All variables on each module.
- Information output of memory consumption, hardware detection, and software
versions.
- Time, delta time, frames.

# Link to GitHub repository:
https://github.com/avocadolau/LannaEngine

# Authors:
- [Laura Isidro](https://github.com/avocadolau)

- [Anna Metreveli](https://github.com/aNnAm2606)

# Camera Controls:
- Right click + WASD
- Mouse wheel to zoom in and out.
- ALT + Left click to orbit the object.
- “F” to focus the camera around the geometry.
- Hold SHIFT to duplicate movement speed.

# Dependencies:
Visual Studio 2019 or more
Open the Scripts folder and then select your Visual Studio version at GenerateProjectsX.bat Create a Assets folder at the Editor folder

- Note: the project only supports Windows

MIT License
Copyright (c) 2022 avocadolau & aNnA2606
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
