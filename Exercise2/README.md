## Exercise 2: Transformations

### Subject / Goals:

Understand transformations and how to apply them to objects. In addition, we get to know normals and experiment with them.

### Tasks (3 points):

- Apply rotation, translation, and scalings for a shape object (see 'Additional Information' below).
- Animate the cube to spin around the axis (0, 1, 0).
- Animate the cube to scale, increasing and decreasing its size.
- Create and transform 4 torus so that each torus is positioned on one side of the cube with a little distance.
- Animate the toruses so that they keep their positions and size correlated to the cube, however they should rotate around the axis from their center to the center of the torus.
- Show the normals for the torus objects as a MultiLine object.
- Show the toruses with colors according to normals.
- Calculate the normal matrix, apply it to the normals of the torus, and compare the color output.
- Apply the normal matrix of the toruses also to manipulate the line object.

The video "task_possible_solution.mp4" shows one possible solution for this task. Note that your solution can differ depending on the scaling and offset between toruses and cube that you chose.

### Bonus Task (+1 point):

Right now, four toruses are arranged around the cube. Make the number of toruses arranged in a circle around the cube customizable by a variable in the code. The video "bonus_task_possible_solution.mp4" shows how such a solution would look like for 10 toruses.

### How to Submit:

Create a **.zip** file with the source code (please include only the source files, the **src/** and **shader/** folders), and upload it to OLAT with a screenshot of the rendering window working on your computer.

### Learning Targets:

- Apply a transformation to a model matrix.
- Draw lines-based objects.
- Apply a normal matrix to normals, and see the difference between right and wrong normals.

### Additional Information:

The starting point of this exercise is two objects (torus and cube) located at the same position. Implement the corresponding methods in the Shape class.

Look at the shaders (vertex and fragment shaders) for the objects' coloring.

Some screenshots and videos of the initial state and as references to the exercise tasks are in the **doc/** folder.
