#version 410 core

/* TODO update your vertex shader so that...
 *      ...it emits all necessary information to the fragment shader texturing
 *
 */

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vColor;
layout(location = 2) in vec3 vNormal;
layout(location = 3) in vec2 vTexCoords;
layout(location = 4) in vec3 vTangent;

out vec3 objectColor;
// TODO Add the output data required in the fragment shader
out vec2 v_texture;
flat out vec4 flat_colour;
// TODO END

// matrices that stay constant for the whole mesh.
uniform mat4 modelMatrix;
uniform mat4 mvpMatrix;

void main()
{
	gl_Position = mvpMatrix * vec4(vPosition, 1);
	objectColor = vColor;

	/* TODO: set texture coordinates for fragment shader here here and additionally required output*/
	v_texture = vTexCoords;
	// End TODO
	flat_colour = vec4(0,vTexCoords,1);
}

