﻿# River Raid:
This project is an application of some Computer Graphics concepts in which you control
a helicopter that needs to leave the screen's boundaries.  
This repository is a Visual Studio project that requires the installation of `glew` and `glfw`, but it can also be
compiled without VS by linking the appropriate libraries.

# Project Structure:  
All relevant `.cpp` and `.h` files are in the `src/` directory.
```
└─── src
    ├─── graphics/  # OpenGL and transformation-related code
    ├─── math/      # Small implementation of vectors and matrices of fixed size
    ├─── misc/      # Miscellaneous functions and definitions
    ├─── misc/      # Miscellaneous functions and definitions
    ├─── main.cpp   # Main application
    └─── object.cpp # Creates the application's SceneObjects

```
## graphics/
- *Primitive:* Struct containing basic information about an OpenGL primitive. Includes vertices, type of primitive and color.
- *Shader:* Class abstraction of a GLSL shader. Construct it with vertex and fragment shader code string, and optionally name it.
- *Renderer:* Class abstraction of OpenGL's VAOs, VBOs and `draw` calls. It is responsible for drawing the scene objects relative to their hierarchical parents.
- *SceneObject:*  Class that unifies a collection of primitives with a single transformation matrix. Can have children which are transformed in relation to the parent.
- *Transform:* Struct containing geometric transformation info like translation, scale and rotation. Can be converted into a Transform matrix using a Matrix3 constructor.
- *PhysicsBody:* Struct containing simple kinematic properties like linear and angular velocity.

## math/
- *vectors:* Defines Vector2, Vector3 and Vector4 structs along with some common operations.
- *matrix:* Defines the struct Matrix3 along with common transformation operations like rotation, scale and translation. Can be constructed from a Transform struct.

# Hierarchical structure:
SceneObjects can be nested within each other, creating a hierarchical structure.
The main implication of this decision is that child objects are transformed in relation to their parents: this means that an object's vertices will first
be transformed by their transform matrix, then by their parent's, then by their grandparent's and so on. This allows for the creation of more complex objects
that can have semantic behavior like a helicopter's propeller rotating along its own axis as well
as following the helicopter around (the same applies for scale and rotation).

# Main loop and Scene:
The main program structure is as follows
```
- Initialize GLFW and OpenGL context
- Creates a SceneObject called scene to which all root-level SceneObjects will be appended
- Calls the appropriate functions to generate each object in the scene and appends them to the scene
- Creates a Renderer object passing the vertex and fragment shader code
- Uploads the scene object to the GPU (through the Renderer instance)
- In the main loop:
    - Calls GLFW-related functions
    - Calls scene->update to update all SceneObjects that have kinematic properties (like velocity)
    - Calls renderer->drawObject(scene) to calculate the objects' global transforms and make all OpenGL draw calls
```