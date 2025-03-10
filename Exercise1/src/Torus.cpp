#include "Torus.h"
#include <math.h>       // for M_PI
#include <glm/glm.hpp>  // for glm::vec3, etc.
#include <glm/gtc/constants.hpp>

namespace cgCourse
{
    Torus::Torus(float majorRadius, float minorRadius,int majorSeg, int minorSeg, float off, float twist) : R(majorRadius),
          r(minorRadius),
          numSegments(majorSeg),
          numTubeSegments(minorSeg),
          offset(off),
          twistFactor(twist)
    {
        // 1) Generate torus geometry
        generateMesh();

        // 2) Offset vertices along normal
        applyOffset();
    }

    void Torus::generateMesh()
    {
        // Clear old data
        positions.clear();
        normals.clear();
        colors.clear();
        faces.clear();
        const float PHI = 2* M_PI;
        const float THETA = 2*M_PI;
        for(int i = 0; i < this->numSegments; ++i){
            for(int j = 0; j <this->numTubeSegments,++j){
                float phi = i * PHI/numSegments;
                float theta =  j * THETA/numTubeSegments;
                float x = this-> R * cos(phi) + this->r * cos(phi) * cos(theta);
                float y = this-> R * sin(phi) + this->r * sin(phi) * cos(theta);
                float z = this->r * sin(theta);
                glm::vec3 point = glm::vec3(x,y,z);
                glm::vec3 point_color = glm::vec3(abs(cos(thetaWarp)), abs(sin(phi)), 0.5f);
                positions.push_back(point);
                colors.push_back(point_color)
            }
        }
        for(int i = 0; i < this->numSegments; ++i){
            for(int j = 0; j < this->numTubeSegments; ++j){
                int iplus1 = 0;
                int jplus1 = 0;
                if(this->numSegments-1 > i){
                    iplus1 = i+1;
                }
                if(this->numTubeSegments-1 > j){
                    jplus1 = j+1;
                }
                glm::uvec3 tri1 = glm::uvec3()
                faces.push_back
            }
        }
        
        // **TODO**: Implement parametric torus with a warp
        // Use angles: theta in [0..2π), phi in [0..2π).
        // Example of warping:
        // float thetaWarp = theta + twistFactor * sin(phi);
        
        
        // Loop over i in [0..numSegments)
        //   float theta = ...
        // Loop over j in [0..numTubeSegments)
        //   float phi = ...
        // Then compute (x, y, z)

        // Also store normals and a color. Example color:
        // glm::vec3 color = glm::vec3(abs(cos(thetaWarp)), abs(sin(phi)), 0.5f);
        
        // **TODO**: Build triangle faces
        // Each cell has two triangles:
        //   (i, j), (i+1, j), (i, j+1)
        //   (i, j+1), (i+1, j), (i+1, j+1)
    }
    int Torus::indexOfVertex()

    void Torus::applyOffset()
    {
        // **TODO**: For each vertex, add: positions[i] += offset * normals[i];
    }

    void Torus::draw()
    {
        glBindVertexArray(vaoID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);

        // Each face is a uvec3 => 3 indices per face
        glDrawElements(GL_TRIANGLES,
                       GLsizei(faces.size() * 3),
                       GL_UNSIGNED_INT,
                       nullptr);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
}
