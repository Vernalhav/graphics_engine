# Graphics Engine:
This project is an application of a few 3D Computer Graphics concepts in an attempt to create a small game engine-like 
API. To test this API, we've created an application in which you navigate a Minecraft-inspired 3D environment.  
This repository is a Visual Studio project that requires the installation of `glew`, `glfw` and `glm`, but it can also be 
compiled without VS by linking the appropriate libraries.

# Project Structure:  
All relevant `.cpp` and `.h` files are in the `src/` directory.
```
├─── assets/            # 3D models, materials and textures 
└─── src/
    ├─── application/   # Application-specific code and Components
    ├─── engine/        # Scene objects, input reading and kinematic-related code
    ├─── graphics/      # OpenGL and transformation-related code
    ├─── misc/          # Miscellaneous functions and definitions
    ├─── external/      # Source code from external libs (like stb_image)
    └─── main.cpp       # Main application
```
## engine/
- **SceneObject:** Class that unifies a collection of Components with a single transformation matrix. Can have children which are transformed in relation to the parent.
- **Component (in SceneObject.h):** Base class of all Components. Extend this class to add custom behaviour to SceneObjects. Has static member deltaTime.
- **Transform:** Struct containing geometric transformation info like translation, scale and rotation. Can be converted into a Transform matrix using a glm::mat3 constructor.
- **PhysicsBody:** Component containing simple kinematic properties like linear and angular velocity.
- **Scene:** Scene object that contains the main camera, renderer and all SceneObjects.  
- **Window:** Window system abstraction.  
- **Input:** Helper Input-related functions for the current window.

## graphics/
- **Primitive:** Struct containing basic information about an OpenGL primitive. Includes vertices, type of primitive and color.
- **Shader:** Class abstraction of a GLSL shader. Construct it with vertex and fragment shader code string, and optionally name it.
- **Renderer:** Class abstraction of OpenGL's VAOs, VBOs and `draw` calls. It is responsible for drawing the scene objects relative to their hierarchical parents.

# Hierarchical structure:
SceneObjects can be nested within each other, creating a hierarchical structure.
The main implication of this decision is that child objects are transformed in relation to their parents: this means that an object's vertices will first
be transformed by their transform matrix, then by their parent's, then by their grandparent's and so on. This allows for the creation of more complex objects
that can have semantic behavior like a helicopter's propeller rotating along its own axis as well
as following the helicopter around (the same applies for scale and rotation).

# Components:
Components are a way to add custom behaviour to a SceneObject. To create a new Component, create a class that inherits from Component and
add a constructor that receives at least the parent SceneObject pointer (which should be delegated to the Component constructor).
Component subclasses can implement the following functions:
- `start():` Will be called once before the first frame;  
- `update():` Will be called once every frame;

A pointer to the component's SceneObject is available through the `sceneObject` member.  

You can add a component to an object by using
```object->addComponent<ComponentType>(<args>)```
where ComponentType is the name of a Component's subclass and <args> are the parameters to its constructor **excluding the SceneObject reference**.
The SceneObject's reference will be passed automatically by the `addComponent` function.  

You can get a pointer to a component attatched to a SceneObject by using  
```object->getComponent<ComponentType>()```


# Main loop and Scene:
The main program structure is as follows
```
- Initialize GLFW window and OpenGL context
- Creates a SceneObject called scene to which all root-level SceneObjects will be appended
- Calls the appropriate functions to generate each object in the scene and appends them to the scene
- Creates a Renderer object passing the vertex and fragment shader code
- Uploads the scene object to the GPU (through the Renderer instance)
- Calls scene->start to initialize all Components
- In the main loop:
    - Calls GLFW-related functions
    - Calls scene->update to update all SceneObjects that have Components
    - Calls renderer->drawObject(scene) to calculate the objects' global transforms and make all OpenGL draw calls
- Frees memory and terminates GLFW
```


# Improvements:  
- Split Component and SceneObject files  
- Use smart pointers instead of standard ones  
- Add override tag to all engine Components' update methods
