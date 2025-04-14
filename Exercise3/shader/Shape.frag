#version 410 core
/* Update your vertex shader so that...
 *      ...it emits the color for phong illumination
 *      ...it emits the color from the vertex shader in case you do gouraud shading there
 */

in vec3 objectColor;
in vec3 normal;
in vec3 worldPos;

/* TODO fill these structs with values from outside the shader similar
 *      to your matrix variables
 */

uniform float ambient;
uniform float diffuse;
uniform float specular;
uniform float shiny;

uniform vec4 lightPosition;
uniform vec4 lightColour;


flat in vec4 flat_color;


// END TODO

uniform bool gouraudShading;

// Ouput data
out vec3 color;

void main()
{
    // Output color = color specified in the vertex shader,
    // interpolated between all 3 surrounding vertices
    color = objectColor;
    vec3 lig = normalize(lightPosition.xyz-worldPos);
    vec3 eye = normalize(-worldPos);
    vec3 ref = normalize(reflect(-lig,normal));
    if(!gouraudShading)
    {
        // TODO add there code for phong lighting
        color += ambient * vec3(lightColour) * objectColor;
        float diff = max(0.0,dot(normal,lig));
        color += diffuse * diff * vec3(lightColour) * objectColor;
        float spec = max(0.0, dot(ref,eye));
        color += specular * pow(spec,shiny) * objectColor * vec3(lightColour);
        // END TODO
    }
}

