#version 410 core

/* Update your vertex shader so that...
 *      ...it emits all necessary information to the fragment shader for phong illumination
 *      ...it emits the color in case you do gouraud shading
 */

uniform settingsBlock{
    bool lightingSwitch;
    bool ambientSwitch;
    bool diffuseSwitch;
    bool specularSwitch;
} settings;

uniform materialBlock{
    float ambient;
    float diffuse;
    float specular;
    float shiny;
} material;

uniform lightBlock{
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
flat out vec4 flat_color;

// matrices that stay constant for the whole mesh.
uniform mat4 modelMatrix;
uniform mat4 mvpMatrix;

uniform bool gouraudShading;

// TODO Additional variables

// END TODO

void main()
{
    normal = mat3(transpose(inverse(modelMatrix))) * vNormal;
    vec3 nor = mat3(transpose(inverse(modelMatrix)))*normalize(vNormal);
    vec3 lig = normalize(light.lightPosition.xyz-vPosition);
    vec3 eye = normalize(-vPosition);
    vec3 ref = normalize(reflect(-lig,nor));

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
       if(settings.ambientSwitch)
       {
        objectColor += material.ambient * vec3(light.lightColour)*vColor;
       }
       if(settings.diffuseSwitch)
       {
        float diff = max(dot(-lig,nor),0.0);
        objectColor += material.diffuse * diff * vec3(light.lightColour) *vColor;
       }
       if(settings.specularSwitch)
       {
        float spec = max(dot(ref,eye), 0.0);
        objectColor += material.specular * pow(spec,material.shiny) * vec3(light.lightColour) * vColor;
       }
        // END TODO
    }
    flat_color = vec4(vColor,1.0);
}

