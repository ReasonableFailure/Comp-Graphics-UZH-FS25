#version 410 core

/* TODO update your vertex shader so that...
 *      ...it has texture samplers declared
 *      ...it outputs a diffuse texture as diffuse color
 *      ...it uses a light map to modify the specular highlights
 */



/* TODO Add the required input data */
in vec3 objectColor;
in vec2 v_texture;

flat in vec4 flat_colour;
// END TODO

/* TODO declare texture samplers here */
uniform sampler2D colourTexture;

// END TODO

/* TODO fill these structs with values from outside the shader similar
 *      to your matric variables
 */

// TODO END

out vec3 color;

void main()
{
	// color = vec3(vec4(objectColor,1) * texture(colourTexture, v_texture)); //I'm sure casting vectors of different lengths to and fro cannot backfire. ever.
	color = objectColor * vec3(texture(colourTexture,v_texture));
	// color = vec3(flat_colour);
	/* TODO add the source code to do phong shading but with the values of the color, normal and specular texture.
	 *      Remember that you can also use the color output for debugging of the
	 *      texture maps and texture coordinates in case that you face troubles.
	 */

	// TODO END
}

