## Lighting - Exercise 3 (4 + 1 points)

The aim of this exercise is to familiarize yourself with two different lighting techniques (Gouraud and Phong). Further you will dive deeper into shader programming.

### Subject / Goals:

Apply the Gouraud and Phong lighting model using ambient, diffuse, and specular terms to the objects (cube, torus and torus knot) in the scene.

### Tasks:

Implement Gouraud and Phong Lighting. For this, you have to make sure that the light information is accessible in the shader.
Further, adapt the shaders accordingly.
Note that the shader program should work for both lighting methods with the ```gouraudShading``` uniform controlling which one should be applied.

For each of the two methods submit a screenshot each of the:

- ... ambient term alone  
- ... diffuse term alone  
- ... specular term alone  
- ... all terms combined  

E.g. eight screenshots in total.

Note the TODOs in the code, the exercise can be solved by adding code only there.

Files with TODOs:  
- `GLExample.cpp`  
- `Shape.vert`  
- `Shape.frag`  

### How to submit

Once your code compiles and works, create a ```.zip``` file with the source code (please include only the source files in the ```src/``` and ```shader/``` folder) and the requested screenshots. Upload the zip-file to OLAT.

### Learning Targets:

- You know how to apply basic Phong lighting to a scene in the shader  
- You know the difference between Gouraud shading and Phong shading  
- You know how shading models and lighting models differ  
- You know how to set uniforms to a shader  

### Tips

- The setup for the exercise is the same as for previous ones  
- The color output can be helpful to debug your code (e.g. set color values according to variables you are interested in)  
- Checkout [learnopengl.com](https://learnopengl.com/) for tutorials, especially the ones linked below  
- The UI offers you checkboxes to hide individual objects, render normals and pause the animation  

### Bonus Task (1 additional point)

Implement a spotlight (e.g. a light that only lights up a spot) instead of the point light in the exercise.  
The spotlight should be **animated** and the user should be able to **activate it via the already existing checkbox** in the UI.  
Add screenshots of your implementation and make sure to briefly explain how your implementation works.

> Hint: The spotlight direction is animated in the code and available as `spotLightDirection` in `GLExample.cpp`.

### Optional Exploration: Add a UI Toggle for Static vs Animated Light (Not Graded)

Implement a UI checkbox that allows switching between an animated light source and a static light source positioned on the right side of the scene.
By default (when 'Toggle Light Position' is unchecked), the light moves back and forth along the x-axis, creating dynamic lighting changes.
When the checkbox “Toggle Light Position” is enabled, the light becomes fixed at position (3.0, 1.5, -1.0).

> Hint: You can use the variable animation for the dynamic light position and switch to a fixed position when toggled.


### Links

- [Basic Lighting on learnopengl.com](https://learnopengl.com/Lighting/Basic-Lighting)
- [Shaders on learnopengl.com](https://learnopengl.com/Getting-started/Shaders)