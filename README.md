# GraphicsEngine
GraphicsEngine is a very basic graphics framework currently based on OpenGL backend (in development). Primary focused on automatize all the graphics backend including shaders, vertex attributes, uniforms and so on.

# What can the engine do?
- Read all shader data and configure the object's graphics information automatically.
- Creation of new objects and use them in an easy way (just inherit from Object. Set up the object in ctor and override Update() method).
- Creation of materials and load meshes for the objects (by now only can load .msh files)
- Creation of lights and cameras (only PhongLighting and one camera by now).
- Lighting data and camera data is sent to GPU via UniformBlockBuffers and updated every frame in CPU side.

# What's next?
- Refactor Vertex data (now handled by simple Vertex structure)
- Automatize push uniforms to GPU (cache the variables and update in CPU side automatically)
- Improve Transforms
- Add support to other file extension and improve the loading process

Once achieve the goals presented the main idea is to introduce more advance lighting and GUI using imGUI.