#version 410 core

/* Update your vertex shader so that...
 *      ...it emits all necessary information to the fragment shader for phong illumination
 *      ...it emits the color in case you do gouraud shading
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
uniform bool bonusTask;

// TODO Additional variables

// END TODO

void main()
{
    worldPos = vec3(modelMatrix * vec4(vPosition, 1));
    normal = mat3(transpose(inverse(modelMatrix))) * vNormal;
    vec3 nor = mat3(transpose(inverse(modelMatrix)))*normalize(vNormal);
    vec3 lig = normalize(vec3(light.lightPosition - vec4(worldPos,1.0)));
    vec3 eye = normalize(-worldPos);
    vec3 ref = normalize(reflect(-lig,nor));
    float theta = dot(vec4(lig,1.0), normalize(-light.lightDirection));

    // Output position of the vertex, in clip space : MVP * vPosition
    gl_Position = mvpMatrix * vec4(vPosition, 1);

    // The color of each vertex will be interpolated
    // to produce the color of each fragment
    // ... uncomment this for color
    objectColor = vColor;

    // ... uncomment this for color according to normals
    // objectColor = vNormal;

    if(bonusTask){
        if(theta > light.cutOff){
            if(gouraudShading){
                objectColor = vec3(0.0,0.0,0.0);
                if(settings.ambientSwitch!=0)
                {
                    objectColor += material.ambient * vec3(light.lightColour) * vColor;
                }
                if(settings.diffuseSwitch!=0)
                {
                    float diff = max(dot(lig,nor), 0.0);
                    objectColor += material.diffuse * diff * vec3(light.lightColour) * vColor;
                }
                if(settings.specularSwitch!=0)
                {
                    float spec = max(dot(ref,eye), 0.0);
                    objectColor += material.specular * pow(spec,material.shiny) * vec3(light.lightColour) * vColor;
                }
            }
        } else {
            objectColor = material.ambient * vec3(light.lightColour) * vColor;
        }
    } else {
        if(gouraudShading){
            objectColor = vec3(0.0,0.0,0.0);
            if(settings.ambientSwitch!=0)
            {
                objectColor += material.ambient * vec3(light.lightColour) * vColor;
            }
            if(settings.diffuseSwitch!=0)
            {
                float diff = max(dot(lig,nor), 0.0);
                objectColor += material.diffuse * diff * vec3(light.lightColour) * vColor;
            }
            if(settings.specularSwitch!=0)
            {
                float spec = max(dot(ref,eye), 0.0);
                objectColor += material.specular * pow(spec,material.shiny) * vec3(light.lightColour) * vColor;
            }
        }
    }
    flat_color=vec4(1.0,0.0,0.0,1.0);
}

