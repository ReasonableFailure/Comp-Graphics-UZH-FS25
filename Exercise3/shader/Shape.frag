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
    int lightingSwitch;
    int ambientSwitch;
    int diffuseSwitch;
    int specularSwitch;
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
    vec4 lightDirection;
    float cutOff;
} light;

flat in vec4 flat_color;


// END TODO

uniform bool gouraudShading;
uniform bool bonusTask;

// Ouput data
out vec3 color;

void main()
{
    // Output color = color specified in the vertex shader,
    // interpolated between all 3 surrounding vertices
    // color = objectColor;
    // vec3 licht = normalize(light.lightPosition.xyz-worldPos);
    // vec3 betrachter = normalize(-worldPos);
    // vec3 ref = normalize(reflect(-licht,normal));
    // if(!gouraudShading)
    // {
    //     color = vec3(0.0,0.0,0.0);
    //     // TODO add there code for phong lighting
    //     if(settings.ambientSwitch!=0)
    //     {
    //         color += material.ambient * vec3(light.lightColour) * objectColor;
    //     }
    //     if(settings.diffuseSwitch!=0)
    //     {
    //         float diff = max(0.0,dot(normal,licht));
    //         color += material.diffuse * diff * vec3(light.lightColour) * objectColor;
    //     }
    //     if(settings.specularSwitch!=0)
    //     {
    //         float spec = max(0.0, dot(ref,betrachter));
    //         color += material.specular * pow(spec,material.shiny) * objectColor * vec3(light.lightColour);
    //     }
    //     // END TODO
    // }
    // normal = mat3(transpose(inverse(modelMatrix))) * vNormal;
    // vec3 nor = mat3(transpose(inverse(modelMatrix)))*normalize(vNormal);
    color = objectColor;
    vec3 lig = normalize(vec3(light.lightPosition - vec4(worldPos,1.0)));
    vec3 eye = normalize(-worldPos);
    vec3 ref = normalize(reflect(-lig,normal));
    float theta = dot(vec4(lig,1.0), normalize(-light.lightDirection));
    if(bonusTask){
        if(theta > light.cutOff){
            if(!gouraudShading){
                color = vec3(0.0,0.0,0.0);
                if(settings.ambientSwitch!=0)
                {
                    color += material.ambient * vec3(light.lightColour) * objectColor;
                }
                if(settings.diffuseSwitch!=0)
                {
                    float diff = max(dot(lig,normal), 0.0);
                    color += material.diffuse * diff * vec3(light.lightColour) * objectColor;
                }
                if(settings.specularSwitch!=0)
                {
                    float spec = max(dot(ref,eye), 0.0);
                    color += material.specular * pow(spec,material.shiny) * vec3(light.lightColour) * objectColor;
                }
            }
        } else {
            color = material.ambient * vec3(light.lightColour) * objectColor;
        }
    } else {
        if(!gouraudShading){
            color = vec3(0.0,0.0,0.0);
            if(settings.ambientSwitch!=0)
            {
                color += material.ambient * vec3(light.lightColour) * objectColor;
            }
            if(settings.diffuseSwitch!=0)
            {
                float diff = max(dot(lig,normal), 0.0);
                color += material.diffuse * diff * vec3(light.lightColour) * objectColor;
            }
            if(settings.specularSwitch!=0)
            {
                float spec = max(dot(ref,eye), 0.0);
                color += material.specular * pow(spec,material.shiny) * vec3(light.lightColour) * objectColor;
            }
        }
    }
}

