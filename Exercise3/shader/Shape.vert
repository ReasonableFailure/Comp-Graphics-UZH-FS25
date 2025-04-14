#version 410 core

/* Update your vertex shader so that...
 *      ...it emits all necessary information to the fragment shader for phong illumination
 *      ...it emits the color in case you do gouraud shading
 */

uniform float ambient;
uniform float diffuse;
uniform float specular;
uniform float shiny;

uniform vec4 lightPosition;
uniform vec4 lightColour;

// Input vertex data
layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vColor;
layout(location = 2) in vec3 vNormal;

// Output data will be interpolated for each fragment.
// Tip: Try to use the flat modifier to make color associations of a fragment visible for debugging.
out vec3 objectColor;
out vec3 normal;
out vec3 worldPos;
flat out vec4 flat_color;

// matrices that stay constant for the whole mesh.
uniform mat4 modelMatrix;
uniform mat4 mvpMatrix;

uniform bool gouraudShading;

// TODO Additional variables

// END TODO

void main()
{
    worldPos = vec3(modelMatrix * vec4(vPosition, 1));
    normal = mat3(transpose(inverse(modelMatrix))) * vNormal;
    vec3 nor = mat3(transpose(inverse(modelMatrix)))*normalize(vNormal);
    vec3 lig = normalize(lightPosition.xyz-worldPos);
    vec3 eye = normalize(-worldPos);
    vec3 ref = normalize(reflect(-lig,nor));

    // Output position of the vertex, in clip space : MVP * vPosition
    gl_Position = mvpMatrix * vec4(vPosition, 1);

    // The color of each vertex will be interpolated
    // to produce the color of each fragment
    // ... uncomment this for color
    objectColor = vColor;

    // ... uncomment this for color according to normals
    // objectColor = vNormal;
    if(gouraudShading)
    {
        // TODO add there code for gouraud shading
        objectColor = ambient * vec3(lightColour) * objectColor;
        float diff = max(0.0,dot(nor,lig));
        objectColor += diffuse * diff * vec3(lightColour) * objectColor;
        float spec = max(0.0, dot(ref,eye));
        objectColor += specular * pow(spec,shiny) * objectColor * vec3(lightColour);
        // END TODO
    }
    flat_color = vec4(vColor,1.0);
}

