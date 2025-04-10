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

in vec3 objectColor;
in vec3 normal;
in vec3 worldPos;
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
    vec3 licht = normalize(light.lightPosition.xyz-worldPos);
    vec3 betrachter = normalize(-worldPos);
    vec3 r = normalize(reflect(-licht,normal));
    if(!gouraudShading)
    {
        // TODO add there code for phong lighting
        if(settings.ambientSwitch)
        {
            color += material.ambient * light.lightColour * objectColor;
        }
        if(settings.diffuseSwitch)
        {
            float diff = max(0.0,dot(normal,licht));
            color += material.diffuse * diff * light.lightColour * objectColor;
        }
        if(settings.specularSwitch)
        {
            float spec = max(0.0, dot(r,betrachter));
            color += material.specular * pow(spec,material.shiny) * objectColor * light.lightColour;
        }
        // END TODO
    }
}

