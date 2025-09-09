# Boxy: a shooter game made with OpenGL and C++
After finishing the first section of [LearnOpenGL](https://learnopengl.com/), I decided to get some hands-on experience and coded this game.

It's a simple shooter where you (the green box) have to shoot and eliminate the enemies (the red boxes).

### About the code
When deciding how to structure my code, I was inspired by the [Cell game engine by Joey DeVries](https://github.com/JoeyDeVries/Cell) and the [OpenGL snake game by Oleg Artene](https://github.com/01e9/snake-game-opengl) (which are pretty good repos to be used as learning resources) and separated the concerns into classes/entities such as `Scene`, `Drawable`, `Object`, `BoundingBox`, `CollisionManager`, utility namespaces, shape structs etc.

### How is collision implemented?
Collision is implemented using the well-known "self-adaptive" [Axis Aligned Bounding Boxes (AABB)](https://developer.mozilla.org/en-US/docs/Games/Techniques/3D_collision_detection),
which change their shape when the object rotates according to the updated minimum and maximum x, y and z coordinate values of the vertices to simplify collision calculation.

### Building the project
Build the project using [CMake](https://cmake.org/). This project has GLFW, GLM and GLAD as dependencies, so you will need to have the headers for each of these libraries
in an `include` directory on your machine as well as the GLFW `.lib` file in a `lib` directory. Run the following commands from the project root:

```
mkdir build
cd build
cmake -DINCLUDE_DIR=<path\to\your\include_dir> -DLIB_DIR=<path\to\your\lib_dir> ..
cmake --build .
cd ..
```

### Running the game
After building, run the executable located in the project's root with `./Boxy`.