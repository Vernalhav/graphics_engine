# Graphics Engine:
This project is an application of a few 3D Computer Graphics concepts in an attempt to create a small game engine-like 
API. To test this API, we've created an application in which you navigate a Minecraft-inspired 3D environment.  
This repository is a Visual Studio project that requires the installation of `glew`, `glfw` and `glm`, but it can also be 
compiled without VS by linking the appropriate libraries.

## Application Controls:
- WASD: move camera along the XZ plane  
- Space/Ctrl: fly upwards or downwards  
- Shift: change movement speed  
- P: toggle polygon mode between fill and wireframe  
- Mouse Scroll: change camera's field of view  

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
## Engine
- **SceneObject:** Class that unifies a collection of Components with a single transformation matrix. Can have children which are transformed in relation to the parent.
- **Component (in SceneObject.h):** Base class of all Components. Extend this class to add custom behaviour to SceneObjects. Has static member deltaTime.
- **Transform:** Struct containing geometric transformation info like translation, scale and rotation. Can be converted into a Transform matrix using a glm::mat3 constructor.
- **Scene:** Scene object that contains the main camera, renderer and all SceneObjects.  
- **Window:** Window system abstraction.  
- **Input:** Helper Input-related functions for the current window.
- **\*Listener:** Interfaces that allow subscription to input events like mouse clicks and key presses.

## Engine Components
- **Camera:** Component that implements a perspective camera abstraction.  
- **Renderable:** Component that makes an object be used by the Renderer during Scene draw.
- **PhysicsBody:** Component containing simple kinematic properties like linear and angular velocity.


## Graphics
- **Vertex:** Struct containing vertex attributes.
- **Texture:** Struct containing texture image and rendering properties.
- **Material:** Struct containing a material's texture and other properties.
- **RenderData:** Struct containing all data and OpenGL buffers required to render a Renderable object.
- **Shader:** Class abstraction of a GLSL fragment and vertex shader.
- **Renderer:** Class abstraction of OpenGL's VAOs, VBOs and `draw` calls.

# Hierarchical structure:
SceneObjects can be nested within each other, creating a hierarchical structure.
The main implication of this decision is that child objects are transformed in relation to their parents: this means that an object's vertices will first
be transformed by their transform matrix, then by their parent's, then by their grandparent's and so on. This allows for the creation of more complex objects
that can have semantic behavior like a helicopter's propeller rotating along its own axis as well as following the helicopter around (the same applies for scale and rotation).

# Components:
Components are a way to add custom behaviour to a SceneObject. To create a new Component, create a class that inherits from Component and
add a constructor that receives at least the parent SceneObject pointer (which should always be delegated to the Component constructor).
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


# Improvements:  
- Split Component and SceneObject files  
- Use smart pointers instead of standard ones  
- Add override tag to all engine Components' update methods  
- Create Components directory in `engine/` and move all engine-side Components to it  
- Use same OpenGL Element buffer for all submesh indices  
- Add camera adjust on window resize (maybe create WindowResizeListener interface?)  
- Implement ResourceManager  
- Delegate RenderData creation to Renderable/ResourceManager  
- Update vertex shader to allow for textureless objects (such as solid colors)
