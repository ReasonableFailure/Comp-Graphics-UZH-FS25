#version 410 core

/* Update your vertex shader so that...
 *      ...it emits all necessary information to the fragment shader for phong illumination
 *      ...it emits the color in case you do gouraud shading
 */

layout(std140) uniform settingsBlock{
    bool wire;
    bool lightingSwitch;
    bool ambientSwitch;
    bool diffuseSwitch;
    bool specularSwitch;
} settings;

layout(std140) uniform materialBlock{
    float ambient;
    float diffuse;
    float specular;
    float shiny;
} material;

layout(std140) uniform lightBlock{
    vec4 lightPosition;
    vec4 lightColour;
} light;

// Input vertex data
layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vColor;
layout(location = 2) in vec3 vNormal;

// Output data will be interpolated for each fragment.
// Tip: Try to use the flat modifier to make color associations of a fragment visible for debugging.
out vec3 objectColor;
out vec3 normal;
out vec3 worldPos;

// matrices that stay constant for the whole mesh.
uniform mat4 modelMatrix;
uniform mat4 mvpMatrix;

uniform bool gouraudShading;

// TODO Additional variables

// END TODO

void main()
{
    normal = mat3(transpose(inverse(modelMatrix))) * vNormal;

    // Output position of the vertex, in clip space : MVP * vPosition
    gl_Position = mvpMatrix * vec4(vPosition, 1);

    // The color of each vertex will be interpolated
    // to produce the color of each fragment
    // ... uncomment this for color
    objectColor = vColor;

    // ... uncomment this for color according to normals
    // objectColor = vNormal;

    worldPos = vec3(modelMatrix * vec4(vPosition, 1));

    if(gouraudShading)
    {
        // TODO add there code for gouraud shading
       
        // END TODO
    }
}

