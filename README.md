# LanaEngine

# About

Lanna engine is a 3D Game Engine developed during the Game Engines classes. We are making to make an Engine that can be used to develop all kinds of games.

# Features

- Baker_house is automatically loaded at the start.
- FBX model loading
- PNG texture loading
- Inspector: displays information about the components of the selected GameObject.
- Transform: Shows position, rotation and scale for the selected GameObject.
- Mesh: information about the loaded mesh.
- Texture: display texture size and path.
- Drag&drop of FBX files.
- Drag&drop of DDS/PNG files.
- Each GameObject has 3 display components: Transform, Mesh and Texture.
- There is a cofnfiguration panel to see the engine's configuration.
- Assets panel icons can be resized

# Editor Windows

- Console: the window LOG the process from ASSIMP and the external libraries initialization process.
- Configuration includes:
- A graph for the frames per second.
- All variables on each module.
- Information output of memory consumption, hardware detection and software
versions.

# Link to GitHub repository

<https://github.com/avocadolau/LannaEngine>

# Authors

- [Laura Isidro](https://github.com/avocadolau)

- [Anna Metreveli](https://github.com/aNnAm2606)

# Camera Controls

- ALT + Right click + WASD
- Mouse wheel to zoom in and out.
- ALT + Left click to orbit the object.
- “F” to focus the camera around the geometry.
- Hold SHIFT to duplicate movement speed.
- In camera inspector the default velocity values can be changed

# How to use

- To create Entities you can use the primitive's menu or do it from the asset panel with drag and drop on scene panel.
- You can only add one component of each type in the inspector.
- In the material component you can add textures from the asset panel.

# Dependencies

Visual Studio 2019 or more
Open the Scripts folder and then select your Visual Studio version at GenerateProjectsX.bat Create a Assets folder at the Editor folder

- Note: the project only supports Windows

MIT License
Copyright (c) 2022 avocadolau & aNnA2606
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
