# LearnOpenGL

![](https://github.com/Sayama3/LearnOpenGL/actions/workflows/cmake.yml/badge.svg)

An OpenGL Renderer I'm making. The second one as the architecture of the first wasn't to my liking.

## Requirement

To run the project, you must have OpenGL 4.3+ and C++ 20+.

## Run Build

To run a build, you can directly run one of the pre-build release _(In the GitHub action.
Soon to be released on the GitHub Releases section)_.

To correctly run the build, you must have the following architecture :

```text
resources/
├─ models/
│  ├─ SurvivalGuitarBackpack/
│  │  ├─ textures/
│  │  │  ├─ Scene_-_Root_baseColor.jpeg
│  │  │  ├─ Scene_-_Root_metallicRoughness.png
│  │  │  ├─ Scene_-_Root_normal.png
│  │  ├─ scene.bin
│  │  ├─ scene.gltf
├─ shaders/
│  ├─ container.frag
│  ├─ container.vert
│  ├─ lightsource.frag
│  ├─ lightsource.vert
├─ textures/
│  ├─ container.jpg
│  ├─ container2.png
│  ├─ container2_specular.png
OpenGL.exe
```

## Inputs

To run the demo, you have to use `WASDQE`.

To rotate the camera you have to use the `Mouse`

To enable/disable the cursor/input you can press `Left Ctrl`.

To enable/disable the flashlight you can press `F`.

To quit de demo you can press `Escape`.


## Demo
Here is an example of the current state of the project.

![](https://raw.githubusercontent.com/Sayama3/LearnOpenGL/main/README/gifs/Demo_LearnOpenGL_18062023_01.gif)